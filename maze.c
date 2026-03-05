//Librerias, caja de herrmientas
#include <stdio.h> //para printf y scanf
#include <stdlib.h> //para rand() y srand()
#include <time.h> //para time(NULL)

//Function prototype: Le avisan al compilador que estas funciones existen
void crea_tablero(int f, int c, char matriz_laberinto[f][c]);
void imprimir_laberinto(int f, int c, char matriz_laberinto[f][c]);
void generar_laberinto(int x, int y, int f, int c, char matriz_laberinto[f][c]);
void resuelve_laberinto_bfs(int f, int c, char matriz_laberinto[f][c]);

//Los arreglos (arrays) siempre se pasan por referencia (puntero implícito).

//Se define un tipo de dato que agrupa 2 enteros
//typedef simplemente es un alias
typedef struct {
    int x;
    int y;
} Punto;

//Crea el laberinto y lo llena de paredes (#)
void crea_tablero(int f, int c, char matriz_laberinto[f][c]){
    for(int i = 0; i < f; i++ ){
        for(int j = 0; j < c; j++){
                matriz_laberinto[i][j] = '#';
        }
    }
}

//Imprime el laberinto
void imprimir_laberinto(int f, int c, char matriz_laberinto[f][c]){
        for(int i = 0; i < f; i++ ){
            for(int j = 0; j < c; j++){
                printf("%c ",matriz_laberinto[i][j]);
            }
            printf("\n");
        }
}

//Generación de laberintos con DFS (Depth-First Search) recursivo, Backtracking, usa pila(Stack), LIFO.
//Recibe la posicion, las dimenciones del laberinto y el laberinto
//Backtracking funciona gracias a la recursión y al Stack
//Utilicé Backtracking mediante un DFS recursivo
void generar_laberinto(int x, int y, int f, int c, char matriz_laberinto[f][c]){
/*Se encarga de "escabar" los caminos, siendo " " lugar posible para moverse y
"#" las paredes del laberinto*/
//Se marca la celda recorrida
    matriz_laberinto[x][y] = ' '; 
//Se crea un vector con las podibles movidas: 0 - Norte, 1 - Sur, 2 - Este, 3 - Oeste
    int movimientos[] = {0,1,2,3};
/*Este for lo que hace es hacer valores random de las posibles movidas y meterlas dentro del vector,
esto sirve para que el movimiento sea mas aleatorio*/
//Fisher-Yates shuffle
    for (int i = 0; i < 4; i++){
        int r = rand() % 4; //guarda el indice aleatorio de entre 0 y 4, 
        int aux = movimientos[r];
        movimientos[r] = movimientos[i];
        movimientos[i] = aux;
    }

//Aqui se recorre el vector con los movimientos aleatorios
    for(int i = 0; i < 4; i++){
//Para cada dirección barajada, se calculan dos coordenadas: el destino y la pared entre medio.
        int x_sim = x; //Serian las celdas donde se quiere mover
        int y_sim = y;
        int x_pared = x;//Serian las celdas paredes
        int y_pared = y;
//Para cada dirección barajada, se calculan dos coordenadas: el destino y la pared entre medio.
/*Los saltos son **de 2 en 2** porque entre cada celda de camino siempre hay una pared. 
Si saltaras de 1 en 1, los pasillos se unirían y el laberinto no tendría estructura.*/
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
//Corrobora que este dentro del laberinto y que a donde se quiera mover sea una "pared"
    if (x_sim > 0 && x_sim < f - 1 && y_sim > 0 && y_sim < c-1 && matriz_laberinto[x_sim][y_sim]=='#'){
        matriz_laberinto[x_pared][y_pared] = ' '; // derriba la pared intermedia
        printf("Voy a excavar en (%d, %d)\n", x_sim, y_sim);
        generar_laberinto(x_sim, y_sim, f, c, matriz_laberinto);
        printf("Volvi a (%d, %d) y sigo buscando\n", x, y); //Donde vuelve al estado anterior
       }
    }
}

//Resuelve el laberinto usando BFS(Breadth-First Search), usa cola(queue), FIFO
void resuelve_laberinto_bfs(int f, int c, char matriz_laberinto[f][c]){
/* Creamos un array de estructuras Punto (x,y) para usarlo como una cola (FIFO)
   El tamaño f*c asegura que quepan todas las celdas del laberinto si fuera necesario*/
    Punto cola[f*c];
// Variable bandera: 0 significa "buscando", 1 significa "salida encontrada"
    int encontrado = 0;
// Índice 'inicio' apunta al frente de la cola (el siguiente a procesar)
    int inicio = 0;
// Índice 'fin' apunta al final de la cola (donde meteremos nuevos puntos)
    int fin = 0;
// Matriz de enteros para marcar qué celdas ya se visitaron y no repetir camino
    int visitados[f][c];

//Se inicializa en 0 la matriz
for(int i=0; i<f; i++){
        for(int j=0; j<c; j++){
            visitados[i][j] = 0;
        }
    }
// Matriz de estructuras Punto(x,y) para guardar quién es el "padre" de cada celda descubierta
    Punto padres[f][c];
// Punto de inicio (donde el algoritmo comienza a caminar)
    Punto p_inicio = {1,1};
// Punto de salida (las coordenadas que queremos alcanzar)
    Punto p_salida = {f-1, c-2};
// Ponemos el primer punto (inicio) en la cola
    cola[fin] = p_inicio; 
// Aumentamos el contador del final de la cola
    fin++;
// Marcamos la celda de inicio como visitada en nuestra matriz de control
    visitados[p_inicio.x][p_inicio.y] = 1;

// El bucle principal: se ejecuta mientras haya puntos en la cola
/*visitados[nx][ny] = 1;      // se marca para no repetirlo
padres[nx][ny] = actual;    // se guarda de dónde vino
cola[fin].x = nx;
cola[fin].y = ny;
fin++;                      // se mete al final de la cola
```

---

## El proceso completo visualmente

Supón este laberinto simple, partiendo de `(1,1)`:
```
Proceso (1,1) → descubre (1,3) y (3,1) → los mete en cola
Proceso (1,3) → descubre (1,5) y (3,3) → los mete en cola
Proceso (3,1) → descubre (3,3)... ya visitado, lo ignora
...y así hasta llegar a 'S'*/
    while (inicio < fin){
// Sacamos el punto que está al frente de la cola
        Punto actual = cola[inicio];
// Movemos el índice de inicio al siguiente elemento
/*Punto actual = cola[inicio];
inicio++;
```

Se **saca** el punto del frente. Mover `inicio++` es equivalente a eliminarlo de la cola:
```
cola: [ (1,1), (1,3), (3,3), , , ]
                ↑              ↑
             inicio=1        fin=3 */
        inicio++;
    // ¿Es este punto el vecino de la salida?
    // Si llegamos a la salida, marcamos como encontrado y salimos del bucle
        if (actual.x == p_salida.x && actual.y == p_salida.y) {
            encontrado = 1;
            break;
        }
        // Vectores de dirección para movernos: Norte, Sur, Este, Oeste
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        // Revisamos los 4 vecinos posibles del punto actual
        for (int i = 0; i < 4; i++) {
            // Calculamos la coordenada del vecino (nx, ny)
            int nx = actual.x + dx[i];
            int ny = actual.y + dy[i];

            // Verificamos:
            if (nx >= 0 && nx < f && ny >= 0 && ny < c &&  // 1. Que esté dentro de los límites
                (matriz_laberinto[nx][ny] == ' ' || matriz_laberinto[nx][ny] == 'S') && // 2. Que sea un camino (' ' o 'S')
                visitados[nx][ny] == 0) { // 3. Que no haya sido visitado
            // Marcamos al vecino como visitado para que nadie más lo procese
                visitados[nx][ny] = 1;
            // Guardamos que llegamos a este vecino (nx, ny) desde el punto 'actual'
                padres[nx][ny] = actual; // Guardamos de dónde vinimos, el padre
            // Añadimos el vecino al final de la cola para analizarlo después
                cola[fin].x = nx;
                cola[fin].y = ny;
            // Incrementamos el índice del final de la cola
                fin++;
            }
        }
    }
    // Una vez terminado el bucle, revisamos si la bandera 'encontrado' está activa
    if (encontrado) {
        // Empezamos la reconstrucción desde el padre de la salida (el paso previo a la 'S')
        Punto actual = padres[p_salida.x][p_salida.y];

        // Vamos hacia atrás saltando de padre en padre hasta llegar al inicio (1, 1)
        while (actual.x != p_inicio.x || actual.y != p_inicio.y) { //OR
        /*padres[hijo.x][hijo.y] = padre;
```
Visualmente:
```
padres[3][3] = {1,3}
       ↑  ↑     ↑  ↑
    pos hijo   valor padre
Entonces cuando haces:
cactual = padres[actual.x][actual.y];
```

Estás diciendo: *"busca en la posición de actual, y devuélveme quién es su padre"*. Ese padre se convierte en el nuevo `actual`, y en la siguiente vuelta del while repites lo mismo, subiendo un nivel más.

Es como una cadena:
```
(3,5) → busco padres[3][5] → me da (3,3)
(3,3) → busco padres[3][3] → me da (1,3)
(1,3) → busco padres[1][3] → me da (1,1)
(1,1) → es el inicio → para*/
        // Marcamos la celda con un asterisco para visualizar el camino resuelto
            matriz_laberinto[actual.x][actual.y] = '*'; // Marcamos el camino
        // Retrocedemos: el nuevo 'actual' ahora es el padre del que acabamos de pintar
            actual = padres[actual.x][actual.y]; // Saltamos al abuelo, bisabuelo...
        }
        // Marcamos también el inicio con un asterisco para completar el recorrido visual
        matriz_laberinto[p_inicio.x][p_inicio.y] = '*';
    } else {
        // Si el bucle terminó y la bandera sigue en 0, no hay ruta posible
        printf("No se encontro salida.\n");
    }
}

int main(){
    int filas = 11; 
    int columnas = 11;
    char resolver;
    srand(time(NULL));
/*srand(time(NULL)): rand() es un algoritmo matemático que genera números que parecen aleatorios.
Si no le das una "semilla" (seed) diferente cada vez, siempre generará la misma secuencia.
time(NULL) usa los segundos actuales del reloj del sistema para que la semilla siempre sea distinta.
rand() no inventa un número de la nada. Utiliza una fórmula matemática (una ecuación) donde tomas un 
número inicial y le aplicas operaciones (multiplicaciones, sumas y restos)
Tú le das un número inicial (llamado Semilla o Seed).
La fórmula escupe un resultado.
Ese resultado se usa como entrada para generar el siguiente.*/
/*Los VLA (Variable Length Arrays) o "Arreglos de Longitud Variable" son una característica de C 
(introducida en el estándar C99) que te permite definir el tamaño de un array usando una 
variable en tiempo de ejecución, en lugar de un número fijo. Antes de los VLA, si querías un array, 
el tamaño tenía que ser una constante (como 100), o tenías que usar malloc.*/
/*El código es dinámico gracias al uso de VLA (Variable Length Arrays)*/
    
    printf("Escribir la cantidad de filas de la matriz:\t");
    scanf("%d", &filas); 
    //Son operadores fundamentales para manejar memoria directamente
    // "&" significa "dirección de". Estás pasándole a la función scanf un puntero a la variable filas
    // "*" se usa para declarar punteros y para desreferenciar (obtener el valor almacenado en dicha dirección)
    printf("Escribir la cantidad de columnas de la matriz:\t");
    scanf("%d", &columnas);

//como el laberinto solo se puede generar con numeros impares, se hace esto, si es par se le resta 1, para ser impar
    if (filas % 2 == 0){
        filas--;
    }
    if (columnas % 2 == 0){
        columnas--;
    }
//Se declara la matriz que sera el laberinto
    char matriz_laberinto[filas][columnas];
/*En C, cuando pasas un array a una función, no pasas una copia, pasas la dirección de memoria
del primer elemento. Es decir, trabajas sobre la matriz original. Es un puntero implícito */
    crea_tablero(filas,columnas,matriz_laberinto);
    generar_laberinto(1,1,filas,columnas,matriz_laberinto);
    matriz_laberinto[0][1] = 'E'; //Entrada al laberinto
    matriz_laberinto[filas-1][columnas-2] = 'S'; //Salida del laberinto
    printf("\n    LABERINTO GENERADO    \n");
    imprimir_laberinto(filas,columnas,matriz_laberinto);
    printf("Resolver el laberinto? (s/n):\t");
    scanf(" %c", &resolver);
    if (resolver == 's'){
        resuelve_laberinto_bfs(filas,columnas,matriz_laberinto);
        printf("\n    LABERINTO RESUELTO    \n");
        imprimir_laberinto(filas, columnas, matriz_laberinto);
    }
   return 0;
}