#include <iostream>
using namespace std;

/*
    N-QUEENS: BITWISE & BIT-MASKING

    Exploración del árbol de espacio de estados optimizada mediante el enmascaramiento 
    de bits con enteros sin signo, logrando la evaluación de casillas seguras en tiempo 
    O(1) por fila.

    El algoritmo prescinde por completo de la representación de un tablero bidimensional 
    (matriz). En su lugar, este se modela utilizando operaciones lógicas a nivel de bits
    (bitwise operations) sobre variables de tipo 'unsigned int'.

        *Bitwise Operations: Las operaciones se desarrollan en la Unidad Lógico 
        Aritmética (ALU) del procesador para realizar cálculos directos, eliminando la 
        necesidad de iterar sobre estructuras de datos y acceder continuamente a memoria.

        *Bit-masking: Consiste en utilizar una secuencia de bits (máscara) para aislar,
        extraer o modificar un subconjunto específico de bits dentro de otra variable. 
        En este contexto, un bit en estado '1' representa una casilla amenazada o una
        ocupación, mientras que un '0' representa una casilla libre.

    REPRESENTACIÓN DEL ESTADO DEL TABLERO ------------------------------------------------

    Dado que el algoritmo avanza estrictamente fila por fila hacia abajo, solo necesitamos 
    conocer cómo los ataques de las reinas colocadas en las filas superiores se proyectan 
    hacia la fila actual. 
    
    Esto se logra mediante el seguimiento de tres máscaras independientes:

        *Máscara C: Representa los ataques verticales. Un bit encendido indica que una reina 
        se encuentra en esa misma columna en alguna fila superior. El ataque cae 
        perpendicularmente, por lo que su posición no varía al descender.
        
        *Máscara L: Representa las diagonales de ataque que se propagan de derecha a izquierda.
        Al descender una fila, la trayectoria de la amenaza se desplaza exactamente una casilla
        hacia la izquierda (<< 1) en cada llamada recursiva.

        *Máscara R: Representa las diagonales de ataque que se propagan de izquierda a derecha. 
        Al descender una fila, la trayectoria de la amenaza se desplaza exactamente una casilla 
        hacia la derecha (>> 1) en cada llamada recursiva.

    DEDUCCIÓN DE FÓRMULAS Y OPERACIONES LÓGICAS ------------------------------------------------
    COMPORTAMIENTO DEL ALGORITMO

    La eficiencia del algoritmo radica en cómo estas máscaras interactúan matemáticamente sin 
    necesidad de condicionales complejos.

        A. Filtro de límite (DONE_MASK): Para que el algoritmo no esté atado a una arquitectura
        subyacente y se restrinja estrictamente a un tablero NxN, se define una máscara límite.

        DONE_MASK = (1 << N) -1

        * Desplazar el bit 1 en N posiciones hacia la izquierda y restar la unidad enciende exac-
        tamente los N primeros bits de la secuencia. Actúa como un filtro para anular cualquier 
        cálculo que exceda el tamaño lógico del tablero.

        B. Cálculo de casillas seguras:

        safe = ~threats & DONE_MASK
        threats = (C | L | R)

        Para 'threats', la operación lógica OR (|) superpone las tres máscaras. El resultado es
        un mapa completo donde los bits '1' representan las amenazas en la fila actual. La 
        operación NOT (~) invierte la secuencia, ahora los bits '1' representan las casillas 
        matemáticamente seguras. 

        La operación AND (&) con el filtro elimina los falsos positivos, aquellos bits invertidos
        fuera del límite N, dando como resultado una secuencia pura donde cada bit '1' es un 
        movimiento válido.

        C. Aislamiento del bit menos significativo

        q_position = safe & -safe

        En lugar de iterar linealmente para buscar el primer 1 disponible, se utiliza aritmética de 
        complemento a dos. El valor -safe invierte todos los bits de safe y le suma 1. Al aplicar un
        AND lógico entre el valor original y su negativo, todos los bits se anulan excepto el bit 
        encendido más a la derecha (el acarreo). Esto permite extraer la posición exacta para colocar
        la nueva reina en tiempo O(1).

        D. Propagación del estado (llamada recursiva)

        Una vez aislada la posición de la reina (q_position), se actualizan las amenazas paramétrica-
        mente para la siguiente profundidad de la recursión:

        *C | q_position: La columna actual se bloquea indefinidamente hacia abajo.

        *(L | q_position) << 1: Se añade la nueva reina a las amenazas diagonales izquierdas y se aplica
        un desplazamiento a la izquierda (shift left).

        *(R | q_position) >> 1: Se añade la nueva reina a las amenazas diagonales derechas y se aplica
        un desplazamiento a la derecha (shift right).

        Al finalizar el procesamiento de un estado, se "gasta" el bit de la casilla segura mediante la 
        sustracción 'safe -= q_position', forzando al ciclo a calcular la siguiente configuración válida.
*/

unsigned int DONE_MASK = 0; // máscara límite.

void n_queens_optimized(unsigned int C, unsigned int L, 
    unsigned int R, unsigned int q_placed) {

    // caso base: Si C alcanza el límite -> se han colocado las N reinas.
    if (C == DONE_MASK) {
        //printBoard();
        return;
    }

    // se calculan las casillas amenazadas mediante operaciones lógicas
    // para aplicar una máscara y determinar las posiciones libres.
    unsigned int threats = C | L | R; 
    unsigned int safe = ~threats & DONE_MASK;

    while (safe > 0) {
        // se aisla el bit más a la derecha que está libre.
        unsigned int q_position = safe & -safe;

        n_queens_optimized(
            C | q_position, 
            (L | q_position) << 1,
            (R | q_position) >> 1,
            q_placed + 1
            );

        // backtrack: se apaga el bit
        safe -= q_position;
    }
}

int main() {
    int N = 0;
    cout << "Enter the number of queens:\n";
    cin >> N;

    if (N <= 0) {
        cout << "The number must be greater than zero.\n";
        return -1;
    }

    DONE_MASK = (1 << N) - 1;
    n_queens_optimized(0, 0, 0, 0);

    return 0;
}

