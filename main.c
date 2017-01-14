#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    return 0;
}

//Preenche o mapa com obst�culos
int PopulateMap (map16 m) {
    return 0;
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

    //DEBUGS
   printf("%d",AddPositionToRoute(routeHead,12,11));
   printf("%d",AddPositionToRoute(routeHead,12,11));
   printf("%d",sizeof(route));
    return 0;
}

