#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void crea_tablero(int f, int c, char matriz[f][c]);
void imprimir_laberinto(int f, int c, char matriz[f][c]);
void generar_laberinto(int x, int y, int f, int c, char matriz[f][c]);
void resuelve_laberinto_bfs(int f, int c, char matriz[f][c]);
/*Si usas una función en main que está escrita abajo, el compilador se pierde.
El prototipo arriba le dice: "Oye, más adelante verás una función con este nombre
y estos parámetros, no te asustes".*/

typedef struct {
    int x;
    int y;
} Punto;

//Crea el laberinto y lo llena de paredes (#)
void crea_tablero(int f, int c, char matriz[f][c]){
    for(int i = 0; i < f; i++ ){
        for(int j = 0; j < c; j++){
                matriz[i][j] = '#';
        }
    }
}

//Imprime el laberinto
void imprimir_laberinto(int f, int c, char matriz[f][c]){
        for(int i = 0; i < f; i++ ){
            for(int j = 0; j < c; j++){
                printf("%c ",matriz[i][j]);
            }
            printf("\n");
        }
}

/*Generación de laberintos con DFS (Depth-First Search) recursivo y barajado aleatorio de direcciones.
Es backtracking "cavando" túneles*/
void generar_laberinto(int x, int y, int f, int c, char matriz[f][c]){
/* Se encarga de "escabar" los caminos, siendo "." lugar posible para moverse y
"#" las paredes del laberinto*/
    matriz[x][y] = ' '; //Se marca la celda recorrida
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
//Corrobora que este dentro del laberinto y que a donde se quiera mover sea una "pared" para "cavar"
    if (x_sim > 0 && x_sim < f - 1 && y_sim > 0 && y_sim < c-1 && matriz[x_sim][y_sim]=='#'){
        matriz[x_pared][y_pared] = ' ';
        printf("Voy a excavar en (%d, %d)\n", x_sim, y_sim);
        generar_laberinto(x_sim, y_sim, f, c, matriz);
        printf("Volvi a (%d, %d) y sigo buscando\n", x, y); //Donde vuelve al estado anterior
       }
    }
}

void resuelve_laberinto_bfs(int f, int c, char matriz[f][c]){
    Punto cola[f*c];
    int encontrado = 0;
    int inicio = 0;
    int fin = 0;
    int visitados[f][c];
    for(int i=0; i<f; i++){
        for(int j=0; j<c; j++){
            visitados[i][j] = 0;
        }
    }
    Punto padres[f][c];
    Punto p_inicio = {1,1};
    Punto p_salida = {f-1, c-2};
    cola[fin] = p_inicio;
    fin++;
    visitados[p_inicio.x][p_inicio.y] = 1;

    while (inicio < fin){
    // Sacamos el punto actual de la cola
        Punto actual = cola[inicio];
        inicio++;
    // ¿Es este punto el vecino de la salida?
    // Si llegamos a la salida, marcamos como encontrado y salimos del bucle
        if (actual.x == p_salida.x && actual.y == p_salida.y) {
            encontrado = 1;
            break;
        }
        // Direcciones: Norte, Sur, Este, Oeste
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        for (int i = 0; i < 4; i++) {
            int nx = actual.x + dx[i];
            int ny = actual.y + dy[i];

            // Verificamos:
            // 1. Que esté dentro de los límites
            // 2. Que sea un camino (' ' o 'S')
            // 3. Que no haya sido visitado
            if (nx >= 0 && nx < f && ny >= 0 && ny < c && (matriz[nx][ny] == ' ' || matriz[nx][ny] == 'S') && !visitados[nx][ny]) {
                visitados[nx][ny] = 1;
                padres[nx][ny] = actual; // Guardamos de dónde vinimos
                cola[fin].x = nx;
                cola[fin].y = ny;
                fin++;
            }
        }
    }
    if (encontrado) {
        // Empezamos desde el padre de la salida para no sobreescribir la 'S'
        Punto actual = padres[p_salida.x][p_salida.y];

        // Mientras no hayamos vuelto al punto de inicio (1,1)
        while (!(actual.x == p_inicio.x && actual.y == p_inicio.y)) {
            matriz[actual.x][actual.y] = '*'; // Marcamos el camino
            actual = padres[actual.x][actual.y]; // Saltamos al abuelo, bisabuelo...
        }
        // Opcional: marcar el inicio también con '*' si quieres que se vea conectado
        matriz[p_inicio.x][p_inicio.y] = '*';
    } else {
        printf("No se encontro una ruta de salida.\n");
    }
}

int main(){
    int filas, columnas;
    char resolver;
    srand(time(NULL));
/*srand(time(NULL)): rand() es un algoritmo matemático que genera números que parecen aleatorios.
Si no le das una "semilla" (seed) diferente cada vez, siempre generará la misma secuencia.
time(NULL) usa los segundos actuales del reloj del sistema para que la semilla siempre sea distinta.*/

    printf("Escribir la cantidad de filas de la matriz:\t");
    scanf("%d", &filas);
    printf("Escribir la cantidad de columnas de la matriz:\t");
    scanf("%d", &columnas);

//como el laberinto solo se puede generar con numeros impares, se hace esto, si es par se le resta 1, para ser impar
    if (filas % 2 == 0){
        filas--;
    }
    if (columnas % 2 == 0){
        columnas--;
    }

    char matriz[filas][columnas];
/*En C, cuando pasas un array a una función, no pasas una copia, pasas la dirección de memoria
del primer elemento. Es decir, trabajas sobre la matriz original. Es un puntero escondido*/
    crea_tablero(filas,columnas,matriz);
    generar_laberinto(1,1,filas,columnas,matriz);
    matriz[0][1] = 'E'; //Entrada al laberinto
    matriz[filas-1][columnas-2] = 'S'; //Salida del laberinto
    printf("\n--- LABERINTO GENERADO ---\n");
    imprimir_laberinto(filas,columnas,matriz);
    printf("Resolver el laberinto? (s/n):\t");
    scanf(" %c", &resolver);
    if (resolver == 's'){
        resuelve_laberinto_bfs(filas,columnas,matriz);
        printf("\n--- LABERINTO RESUELTO ---\n");
        imprimir_laberinto(filas, columnas, matriz);
    }
   return 0;
}
