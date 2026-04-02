#include <iostream>
using namespace std;

/*
    N - REINAS
    Colocar n reinas en un tablero de ajedréz de n*n, de forma que ninguna ataque a la otra en la 
    misma fila, columna o diagonal. Se imprime la configuración de los tableros validos resultantes.
*/

class Chessboard {
    /*
        'Q' -> Reina
        'X' -> Casilla amenazada
        '_' -> Casilla vacia
    */
    char **board;
    int N;

    public:
    Chessboard(int n) {
        N = n;
        board = new char*[N];

        for (int i = 0; i < N; i++)
            board[i] = new char[N];
        
        for (int j = 0; j < N; j++) 
            for (int k = 0; k < N; k++) 
                board[j][k] = '_';
    }

    // --------------------------------------------------------------------------------------------------

    bool isInBounds(int row, int column) {
        // x, y pertenece [0, N)
        return (row >= 0 && row < N) && (column >=0 && column < N);
    }

    // modifica las casillas a partir de una posición dada, siguiendo el patrón de alcance de la reina.
    bool markThreats(int currentRow, int currentColumn) {
        bool continue_ = true;
        int tempR = currentRow;
        int tempC = currentColumn;

        // 1. Horizontal (izq, der)
        while(continue_) {
            tempC--;
            if (!isInBounds(tempR, tempC)) break;
            board[tempR][tempC] = 'X';
        }

        tempC = currentColumn;
        while(continue_) {
            tempC++;
            if (!isInBounds(tempR, tempC)) break;
            board[tempR][tempC] = 'X';
        }

        // 2. Vertical (arr, abj)
        tempC = currentColumn;
        while(continue_) {
            tempR++;
            if (!isInBounds(tempR, tempC)) break;
            board[tempR][tempC] = 'X';
        }

        tempR = currentRow;
        while(continue_) {
            tempR--;
            if (!isInBounds(tempR, tempC)) break;
            board[tempR][tempC] = 'X';
        }

        // 3. Diagonales

            // A. Diagonales superiores (izq, der)
            tempR = currentRow;
            tempC = currentColumn;
            while(continue_) {
                tempR--;
                tempC--;
                if (!isInBounds(tempR, tempC)) break;
                board[tempR][tempC] = 'X';
            }

            tempR = currentRow;
            tempC = currentColumn;
            while(continue_) {
                tempR--;
                tempC++;
                if (!isInBounds(tempR, tempC)) break;
                board[tempR][tempC] = 'X';
            }

            // B. Diagonales inferiores (izq, der)
            tempR = currentRow;
            tempC = currentColumn;
            while(continue_) {
                tempR++;
                tempC--;
                if (!isInBounds(tempR, tempC)) break;
                board[tempR][tempC] = 'X';
            }

            tempR = currentRow;
            tempC = currentColumn;
            while(continue_) {
                tempR++;
                tempC++;
                if (!isInBounds(tempR, tempC)) break;
                board[tempR][tempC] = 'X';
            }
    }

    void n_queens_algorithm(int row = 0, int column = 0, int q_placed = 0) {
        
        while(N < q_placed) {

            if (board[row][column] == '_') {
                board[row][column] = 'Q';
                markThreats(row, column);
                row++; // pasamos a la siguiente fila inmediatamente;
            }

            q_placed++;
            // if (DEBUG) print();
            n_queens_algorithm(row, column, q_placed);
        }
    }
};

/*
    pseudocódigo:

    si la casilla está libre:
    colocar reina
    establecer casillas amenazadas consultando límites del tablero

    si al momento de establecer una casilla amenazada se encuentra una reina -> volver atrás.

    repetir hasta que iterador = n (iterador: cantidad de reinas colocadas).
*/



int main() {
    int n;  
    cout << "Enter the number of queens\n";
    cin >> n;

    if (n <= 0) {
        cout << "The number must be greater than zero\n";
        return -1;
    }

    Chessboard  chessboard(n);
    chessboard.n_queens_algorithm();

    return 0;
}

