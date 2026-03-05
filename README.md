# The-dive---Challenge-2-
-Segundo challenge de The Dive-
#Generador y Resolutor de Laberintos en C#
Metodología de Generación del Laberinto: 
Para la creación del tablero se implementó un algoritmo de búsqueda en profundidad (DFS) de carácter recursivo. El proceso comienza con una matriz llena de caracteres de pared ('#'). El algoritmo selecciona una celda inicial y explora vecinos de forma aleatoria saltando dos posiciones para mantener la integridad de los pasillos. Para garantizar una aleatoriedad genuina en cada ejecución, se utiliza la función srand vinculada al reloj del sistema (time(NULL)). Cuando el algoritmo alcanza un punto donde no existen vecinos válidos sin visitar, el sistema realiza automáticamente un proceso de backtracking (vuelta atrás) gracias a la pila de llamadas de la recursión.

Algoritmo de Resolución (BFS)
La búsqueda de la salida se realiza mediante el algoritmo de búsqueda en anchura (BFS). A diferencia del DFS, este método utiliza una estructura de datos tipo cola (FIFO) para explorar el laberinto por niveles o capas. Cada vez que se descubre una celda de camino (' '), se registra la dirección de la celda de origen en una matriz de estructuras denominada padres. Al llegar a la salida, este registro permite reconstruir el camino exacto hacia atrás. La ventaja crítica de usar BFS en este contexto es su garantía de optimización: el primer camino que encuentra hacia la salida es, por definición, el camino más corto en términos de pasos totales.

Hallazgos del Análisis de Rendimiento:
Al realizar pruebas de estrés y medición de tiempos, se descubrieron varios factores clave sobre la ejecución en C:
-El uso de VLA limita el tamaño máximo del laberinto. En entornos con una pila restringida, laberintos de gran escala pueden provocar errores de desbordamiento (stack overflow).

-DFS (Generación): Al ser recursivo, cada paso hacia adelante crea un nuevo "marco de pila" (stack frame). Esto implica una carga constante para la CPU, que debe guardar registros y direcciones de retorno. En C, las llamadas a funciones tienen un costo pequeño, pero acumulado en miles de celdas, el DFS puede ser ligeramente más lento en el procesamiento puro que un ciclo simple.

-BFS (Resolución): Al ser iterativo y usar una cola manual, el BFS no sobrecarga la pila de llamadas. Sin embargo, requiere gestionar una estructura de datos externa. El acceso a esta memoria suele ser muy rápido, pero el mantenimiento de los índices inicio y fin añade operaciones aritméticas adicionales en cada iteración.

Consideraciones para Futuras Versiones:
-Sustituir los arreglos automáticos por memoria dinámica (malloc y free) para permitir la creación de laberintos masivos que superen los límites de la pila del sistema.
-Desarrollar una representación gráfica basada en caracteres extendidos o bibliotecas externas para mejorar la legibilidad del camino resuelto