//TESTANDO

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Definição do tipo para as rotas.
typedef struct positionRegister route;
// Definição do "Mapa" padrão (16x16);
typedef struct mapType map16;

//registro do mapa
struct mapType {
    char grid[16][16]; //grid a ser preenchido com caracteres (plano cartesiano)
    int startingX, startingY; //posicao inicial X, Y;
    int goalX, goalY; //objetivo X, Y;
};

//Registro das rotas (lista encadeada).
struct positionRegister {
    int position[2];
    route* next;
};

//Printar o mapa, retorna a quantidade de obstáculos?
int PrintMap(map16 m) {
    int i = 0;
    for ( i = 0; i<16;i++){
        int p = 0;
		for ( p = 0; p<16;p++){
			printf("%d ", m.grid[i][p]);
		}
		printf("\n");
	}
    return 0;
}

//Preenche o mapa com obstáculos
map16 PopulateMap (map16 m, int qty) {
    //hardcode das coordenadas einiciais e finais.
    m.startingX = 5;
    m.startingY = 5;
    m.goalX = 15;
    m.goalY = 15;

    //preenche o mapa de 0 antes de aplicar os obstáculos
    int i = 0;
	for (i = 0; i<16;i++){
        int p = 0;
		for (p = 0; p<16;p++){
			m.grid[i][p] = 0;
		}
	}
	srand(time(NULL)); //gera a seed do rng
	for (i = 0; i < qty; i++){
		int x = rand()%17; //coordenada aleatoria x entre 0 e 16
		int y = rand()%17; //coordenada aleatoria y entre 0 e 16
		if (((x == m.startingX) && (y == m.startingY)) || ((x == m.goalX) && (y == m.goalY)) || (m.grid[x][y] == 1)) {
			i -= 1;
			continue;
		}
		else {
		m.grid[x][y] = 1; //ocupa a coordenada com um obstaculo
		}
	}
    return m; //retorna mapa preenchido
}

//Reservado para o Menu.
int menu() {
    return 0;
}

//Criar lista de rotas a partir de ponto inicial do mapa
route* CreateRoute(int x, int y, map16 m) {
    route* routeHead = (route*) malloc(sizeof(route));
    routeHead->position[0] = m.startingX;
    routeHead->position[1] = m.startingY;
    routeHead->next = NULL;
    return routeHead;
}

// Acrescenta uma posição a uma rota,
//DEBUG: retorna 0 se a lista era vazia e 1 se a lista já continha elementos
int AddPositionToRoute(route* r,int x, int y) {
    route* newPosition = (route*) malloc(sizeof(route));
    newPosition->position[0] = x;
    newPosition->position[1] = y;

    //checa se a lista está no ponto inicial e adiciona o primeiro elemento da lista, no final.
    if (r->next == NULL) {
        r->next = newPosition; //aponta para a nova posição criada.
        return 0; //lista vazia
    } else {
        //Caso a lista não esteja vazia, cria um ponteiro que varre a lista até achar prox NULL, ou seja, o final da lista.
        route* tmp;
        tmp = r->next;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = newPosition;
        return 1; //lista populada
    }
}

//Leitor de rotas (exibir a estrutura no console)
void PrintRoute(route* r) {
    printf("Impressao de rota: \n");
    int i = 0;
    route* sweep;
    if (r->next != NULL) {
        sweep = r->next;
        while (sweep->next != NULL) {
            printf("[%d,%d] \n",sweep->position[0],sweep->position[1]);
            sweep = sweep->next;
        }
        printf("[%d,%d] - FIM DA ROTA \n",sweep->position[0],sweep->position[1]);
    } else {
        printf("A rota especificada nao possui posicoes validas");
    }

}

//Compara o primeiro node diferente da rota.
int CompareRoutes(route* r1, route* r2) {
    return 0;
}

//Escrever rota no arquivo
void WriteRouteToFile() {

}

//Ler rota no arquivo
void ReadRouteInFile() {

}



//Funções de Pathfinding (por enquanto uma só!)
//idéia: compara posição atual com a posição do destino. (x,y). E tenta se mover naquela direção, 1 step por vez.
//utiliza as funções acima
int PlotRoute(route* r, map16 m) {

    //inicializa as coordenadas locais
    int currentPos[2] = {m.startingX,m.startingY};
    int goal[2] = {m.goalX,m.goalY};
    int distance[2] = {0,0};
    int movementVec[2] = {0,0};
    int normalizedDistanceOnX, normalizedDistanceOnY;


    while (currentPos != goal) {
        distance[0] = goal[0]-currentPos[0];
        distance[1] = goal[1]-currentPos[1];
        //Tentar checar as colisões antes de definir a direção ideal. Assim cortaria as possibilidades de movimento.
        //checa (x+1,y)
        if ((currentPos[0] < 16) && (currentPos[0] > 1)) {
            if ( m.grid[currentPos[0]+1][currentPos[1]] == 1) {
                distance[0] = -1; //redefine a prioridade de movimento do eixo x
            }
            if ( m.grid[currentPos[0]-1][currentPos[1]] == 1) {
                distance[0] = 1; //redefine a prioridade do eixo x
            }
        }
        //checa (x,y+1)
        if ((currentPos[1] < 16) && (currentPos[1] > 1)) {
            if ( m.grid[currentPos[0]][currentPos[1]+1] == 1) {
                distance[1] = -1; //redefine a prioridade de movimento do eixo x
            }
            if ( m.grid[currentPos[0]][currentPos[1]-1] == 1) {
                distance[1] = 1; //redefine a prioridade do eixo x
            }
        }
            //normalizar as distancias (se negativo)
            if (distance[0] < 0) {
                normalizedDistanceOnX = (distance[0]*(-1));
            }
            if (distance[1] < 0) {
                normalizedDistanceOnY =  (distance[1]*(-1));
            }


        //Pegar a maior distância, calcular a direcao ideal e mover
            if (normalizedDistanceOnX >= normalizedDistanceOnY) {
                currentPos[0] = (normalizedDistanceOnX/distance[0]); //direcao no X a ser percorrida
            } else {
                currentPos[1] = (normalizedDistanceOnY/distance[1]);
            }
        //Registrar o movimento na rota
            AddPositionToRoute(r,currentPos[0],currentPos[1]);
    }

    return 0;
}


//Loop Principal
int main()
{
    //Cria o cabeçário da rota.
    route* routeHead = (route*) malloc(sizeof(route));
    routeHead->next = NULL;

    //debugzinho
    map16 map = PopulateMap(map, 40);
    PrintMap(map);

    PlotRoute(routeHead,map);


    //PrintRoute(routeHead);

    //Cria o mapa


    return 0;
}


