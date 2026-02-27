#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 21

void crea_tablero();
char matriz[MAX][MAX];

void crea_tablero(){
    for(int i = 0; i < MAX; i++ ){
        for(int j = 0; j < MAX; j++){
                matriz[i][j] = '#';
        }
    }
}
/*primero crear un string que guarde las posibles movidas arriba, abajo, izquierda, derecha, luego seleccionar la movida al azar,
antes de mover marcar la celda como visitada antes de mover, while la celda actual tiene lugar para moverse ()*/
void imprimir_maze(){
        for(int i = 0; i < MAX; i++ ){
            for(int j = 0; j < MAX; j++){
                printf("%c ",matriz[i][j]);
            }
            printf("\n");
        }
}

void generar_maze(int x, int y){

    matriz[x][y] = '.';
    int movimientos[] = {0,1,2,3}; //0 - Norte, 1 - Sur, 2 - Este, 3 - Oeste
    for (int i = 0; i < 4; i++){
        int r = rand() % 4;
        int aux = movimientos[r];
        movimientos[r] = movimientos[i];
        movimientos[i] = aux;
    }

    for(int i = 0; i < 4; i++){
        int x_sim = x;
        int y_sim = y;
        int x_pared = x;
        int y_pared = y;

        if(movimientos[i] == 0){
            x_sim = x - 2;
            x_pared = x - 1;
        }
        else if(movimientos[i] == 1){
            x_sim = x + 2;
            x_pared = x + 1;
        }
        else if(movimientos[i] == 2){
            y_sim = y + 2;
            y_pared = y + 1;
        }
        else if(movimientos[i] == 3){
            y_sim = y - 2;
            y_pared = y - 1;
        }
   

    if (x_sim > 0 && x_sim < MAX - 1 && y_sim > 0 && y_sim < MAX-1 && matriz[x_sim][y_sim]=='#'){
        matriz[x_pared][y_pared] = '.';
        generar_maze(x_sim, y_sim);
       }
   
    }
}

int main(){
    srand(time(NULL)); //Se usa para la funcion rand(), "semilla" que da un punto de partida distinto cada vez que se ejecuta el codigo
    crea_tablero();
    generar_maze(1,1);
    matriz[0][1] = 'E';
    matriz[MAX-1][MAX-2] = 'S';
    imprimir_maze();
   

return 0;
}