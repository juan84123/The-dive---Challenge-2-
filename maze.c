#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Crea el laberinto y lo llena de paredes (#)
void crea_tablero(int l, int c, char matriz[l][c]){
    for(int i = 0; i < l; i++ ){
        for(int j = 0; j < c; j++){
                matriz[i][j] = '#';
        }
    }
}
//Imprime el laberinto
void imprimir_maze(int l, int c, char matriz[l][c]){
        for(int i = 0; i < l; i++ ){
            for(int j = 0; j < c; j++){
                printf("%c ",matriz[i][j]);
            }
            printf("\n");
        }
}

void generar_maze(int x, int y, int l, int c, char matriz[l][c]){
/* Se encarga de "escabar" los caminos, siendo "." lugar posible para moverse y
"#" las paredes del laberinto*/
    matriz[x][y] = '.'; //Se marca la celda recorrida
//0 - Norte, 1 - Sur, 2 - Este, 3 - Oeste
    int movimientos[] = {0,1,2,3};
/*Este for lo que hace es hacer valores random de las posibles movidas y meterlas dentro del vector,
esto sirve para que el movimiento sea mas aleatorio*/
    for (int i = 0; i < 4; i++){
        int r = rand() % 4;
        int aux = movimientos[r];
        movimientos[r] = movimientos[i];
        movimientos[i] = aux;
    }

//Aqui se recorre el vector con los movimientos aleatorios
    for(int i = 0; i < 4; i++){
//Serian las celdas donde se quiere mover
        int x_sim = x;
        int y_sim = y;
//Serian las celdas paredes
        int x_pared = x;
        int y_pared = y;
//Los saltos o pasos se hacen de 2 en 2 de manera a que se puedan generar 
        if(movimientos[i] == 0){ //0 - Norte
            x_sim = x - 2;
            x_pared = x - 1;
        }
        else if(movimientos[i] == 1){ //1 - Sur
            x_sim = x + 2;
            x_pared = x + 1;
        }
        else if(movimientos[i] == 2){ //2 - Este
            y_sim = y + 2;
            y_pared = y + 1;
        }
        else if(movimientos[i] == 3){ //3 - Oeste
            y_sim = y - 2;
            y_pared = y - 1;
        }

    if (x_sim > 0 && x_sim < l - 1 && y_sim > 0 && y_sim < c-1 && matriz[x_sim][y_sim]=='#'){
        matriz[x_pared][y_pared] = '.';
        printf("Voy a excavar en (%d, %d)\n", x_sim, y_sim);
        generar_maze(x_sim, y_sim, l, c, matriz);
        printf("Volví a (%d, %d) y sigo buscando\n", x, y); // Aquí es donde "recuerda"
       }
    }
}

int main(){
/*Se usa para la funcion rand(), "semilla" que da un punto de partida
distinto cada vez que se ejecuta el codigo*/
    srand(time(NULL));
    int lineas, columnas;

    printf("Escribir la cantidad de lineas de la matriz:\t");
    scanf("%d", &lineas);
    printf("Escribir la cantidad de columnas de la matriz:\t");
    scanf("%d", &columnas);
    char matriz[lineas][columnas];

    crea_tablero(lineas,columnas,matriz);
    generar_maze(1,1,lineas,columnas,matriz);
    matriz[0][1] = 'E'; //Entrada al laberinto
    matriz[lineas-1][columnas-2] = 'S'; //Salida del laberinto
    imprimir_maze(lineas,columnas,matriz);
   return 0;
}
