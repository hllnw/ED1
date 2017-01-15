//TESTANDO

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Defini��o do tipo para as rotas.
typedef struct positionRegister route;
// Defini��o do "Mapa" padr�o (16x16);
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

//Printar o mapa, retorna a quantidade de obst�culos?
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

//Preenche o mapa com obst�culos
map16 PopulateMap (map16 m, int qty) {
    //preenche o mapa de 0 antes de aplicar os obst�culos
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

// Acrescenta uma posi��o a uma rota,
//DEBUG: retorna 0 se a lista era vazia e 1 se a lista j� continha elementos
int AddPositionToRoute(route* r,int x, int y) {
    route* newPosition = (route*) malloc(sizeof(route));
    newPosition->position[0] = x;
    newPosition->position[1] = y;

    //checa se a lista est� no ponto inicial e adiciona o primeiro elemento da lista, no final.
    if (r->next == NULL) {
        r->next = newPosition; //aponta para a nova posi��o criada.
        return 0; //lista vazia
    } else {
        //Caso a lista n�o esteja vazia, cria um ponteiro que varre a lista at� achar prox NULL, ou seja, o final da lista.
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

//Fun��es de Pathfinding (por enquanto uma s�!)
//id�ia: compara posi��o atual com a posi��o do destino. (x,y). E tenta se mover naquela dire��o, 1 step por vez.
//utiliza as fun��es acima
int PlotRoute(route* r, map16 m) {

    return 0;
}


//Loop Principal
int main()
{
    //Cria o cabe��rio da rota.
    route* routeHead = (route*) malloc(sizeof(route));
    routeHead->next = NULL;

    //debugzinho
    AddPositionToRoute(routeHead,12,14);
    AddPositionToRoute(routeHead,13,2);
    AddPositionToRoute(routeHead,13,2);
    AddPositionToRoute(routeHead,13,2);
    PrintRoute(routeHead);

    //Cria o mapa
    map16 map = PopulateMap(map, 40);
    PrintMap(map);
    printf("\n");


    return 0;
}


