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
    m.startingX = 14;
    m.startingY = 14;
    m.goalX = 5;
    m.goalY = 5;

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
    newPosition->next = NULL;
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
    //int i = 0;
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
int WriteRouteToFile(route* r) {
    route *iterator = r;
    int data[2] = {0,0};
    //int count = 0;
    FILE *routeFile;
    routeFile = fopen("./routes/route.bin", "wb");
    if (!routeFile) {
        printf("\n Nao foi possivel inicializar o arquivo route.bin");
        return 0; //erro
    }
    while (iterator->next != NULL) {
        data[0] = iterator->position[0];
        data[1] = iterator->position[1];
        fwrite(data,1,sizeof(data),routeFile);
        iterator = iterator->next;
    }
    return 1;
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
    int direction[2];
    double norm[2];
    printf("Ponto inicial: [%d][%d]\n", currentPos[0], currentPos[1]);
    printf("Destino: [%d][%d]\n\n", goal[0], goal[1]);
    //int movementVec[2] = {0,0};
    //int normalizedDistanceOnX, normalizedDistanceOnY;
    //inclui o starting point na rota.
    AddPositionToRoute(r,currentPos[0],currentPos[1]);
    printf("Posicao Adicionada: [%d][%d] \n",currentPos[0],currentPos[1]);

    while ((currentPos[0] < 15) && (currentPos[0] > 0) && (currentPos[1] < 15) && (currentPos[1] > 0)) {
		direction[0] = 1;
		direction[1] = 1; //inicializa as direcoes positivas
        distance[0] = goal[0]-currentPos[0];
        distance[1] = goal[1]-currentPos[1];
        
        //Tentar checar as colisões antes de definir a direção ideal. Assim cortaria as possibilidades de movimento.        
        if (distance[0] < 0){
			direction[0] = -1; //inverte a direcao pra olhar caso o objetivo esteja a esquerda do current
		}
        if (distance[1] < 0){
			direction[1] = -1; //inverte a direcao pra olhar caso o objetivo esteja acima do current
		}
             
        if ( m.grid[currentPos[0]+direction[0]][currentPos[1]] == 1) {
                direction[0] *= -1; //inverte a direção no eixo x
            }
        if ( m.grid[currentPos[0]+direction[0]][currentPos[1]] == 1) {
                direction[0] = 0; //impossibilita o movimento em x
            }
        if ( m.grid[currentPos[0]][currentPos[1]+direction[1]] == 1) {
                direction[1] *= -1; //inverte a direção no eixo y
            }
        if ( m.grid[currentPos[0]][currentPos[1]+direction[1]] == 1) {
                direction[1] = 0; //impossibilita o movimento em y
            }
        norm[0] = sqrt(pow((distance[0]-direction[0]), 2) + pow((distance[1]), 2)); //possivel caminhada em x
        norm[1] = sqrt(pow((distance[0]), 2) + pow((distance[1]-direction[1]), 2)); //possivel caminhada em y
        printf("Direcao x: [%d]\n", direction[0]);
        printf("Direcao y: [%d]\n", direction[1]);
        printf("Norm x: [%f]\n", norm[0]);
        printf("Norm y: [%f]\n", norm[1]);
        if ((direction[0] != 0) && (direction[1] != 0)) {
				if ((norm[0] <= norm[1]) && (currentPos[0] != goal[0])) {
					currentPos[0] = currentPos[0] + direction[0]; //reduz a distancia em x
				}
				else if (currentPos[1] != goal[1]) {
					currentPos[1] = currentPos[1] + direction[1]; //reduz a distancia em y
				}
		}
		else if (direction[0] != 0) {
			currentPos[0] = currentPos[0] + direction[0]; //unica opcao é andar em x
		}
		else if (direction[1] != 0) {
			currentPos[1] = currentPos[1] + direction[1]; //unica opcao é andar em y
		}
		else {
			printf("Nao ha para onde ir! Posicao final: [%d][%d] \n", currentPos[0],currentPos[1]);
			break;
		}
        
        //Registrar o movimento na rota
            AddPositionToRoute(r,currentPos[0],currentPos[1]);
            printf("Posicao Adicionada: [%d][%d] \n",currentPos[0],currentPos[1]);
        if ((currentPos[0] == goal[0]) && (currentPos[1] == goal[1])){
			printf("Voce chegou ao destino!\n");
			break;
		}
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
    map16 map = PopulateMap(map, 10);
    PrintMap(map);


    PlotRoute(routeHead,map);


    //PrintRoute(routeHead);

    //Cria o mapa


    return 0;
}


