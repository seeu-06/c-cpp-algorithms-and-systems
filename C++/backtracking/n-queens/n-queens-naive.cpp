#include <iostream>
using namespace std;

/*
    N-QUEENS PROBLEM (PROBLEMA DE LAS N-REINAS)
    Colocar N reinas en un tablero de ajedrez de NxN, de forma que ninguna amenace a otra en la 
    misma fila, columna o diagonal. Se imprime la primera configuración valida.
    
    ** Esta implementación prioriza la claridad lógica y el aprendizaje del algoritmo de backtracking
       sobre la optimización en términos de tiempo o memoria.
*/

struct Coordinate {
    int x = -1;
    int y = -1;
};

class Chessboard {
    /*
        Representación del tablero:
        'Q' -> Reina
        'X' -> Casilla amenazada
        '_' -> Casilla vacía 
    */
    int N;
    char **board;
    Coordinate *queenPositions;

    public:
    Chessboard(int n) : N(n) {
        board = new char*[N];
        for (int i = 0; i < N; i++) {
            board[i] = new char[N];
            for (int j = 0; j < N; j++) board[i][j] = '_';
        }

        queenPositions = new Coordinate[N];
    }

    ~Chessboard() {
        for (int i = 0; i < N; i++) 
            delete[] board[i];
        
        delete[] board;
        delete[] queenPositions;
    }

    bool isInBounds(int X, int Y) {
        // x, y pertenece [0, N)
        return (X >= 0 && X < N) && (Y >= 0 && Y < N);
    }

    // marca las casillas amenazadas ('X') cuando es colocada una reina en el tablero.
    void markThreats(int currentX, int currentY) {
       // cada par (deltaX[i], deltaY[i]) representa un vector de movimiento.
       // orden: horizontal(izq), horizontal(der), vertical(arr), vertical(abj)
       //        diag. sup.(izq), diag. sup.(der), diag. inf.(izq), diag. inf.(der)
       int deltaX[] = {0,  0, -1, 1, -1, -1,  1, 1};
       int deltaY[] = {-1, 1,  0, 0, -1,  1, -1, 1};

       for (int i = 0; i < 8; i++) {
            int tempX = currentX + deltaX[i];
            int tempY = currentY + deltaY[i];

            while (isInBounds(tempX, tempY)) {
                board[tempX][tempY] = 'X';
                tempX += deltaX[i];
                tempY += deltaY[i];
            }
       }
    }

    // restaura el estado de todas las casillas amenazadas en el tablero y las recalcula
    // basándose en el historial de reinas activas.
    void removeThreats() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) 
                if (board[i][j] == 'X') board[i][j] = '_';
        }

        for (int k = 0; k < N; k++) {
            int tempX = queenPositions[k].x;
            int tempY = queenPositions[k].y;

            if (tempX >= 0 && tempY >= 0) markThreats(tempX, tempY);
        }
    }

    void printBoard() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool n_queens_algorithm(int X = 0, int q_placed = 0) {
        if (q_placed == N) {
            printBoard();
            return true;
        } 
        
        for (int currentY = 0; currentY < N; currentY++) {
      
            if (board[X][currentY] == '_') {
                board[X][currentY] = 'Q';
                queenPositions[q_placed].x = X;
                queenPositions[q_placed].y = currentY;

                markThreats(X, currentY);
                if (n_queens_algorithm(X + 1, q_placed + 1)) return true;

                // backtrack --------------------------------------------
                board[X][currentY] = '_';
                queenPositions[q_placed].x = -1;
                queenPositions[q_placed].y = -1;
                removeThreats();
            } 
        }
        return false;
    }
};

int main() {
    int n;  
    cout << "Enter the number of queens: \n";
    cin >> n;

    if (n <= 0) {
        cout << "The number must be greater than zero.\n";
        return -1;
    }

    Chessboard chessboard(n);
    chessboard.n_queens_algorithm();

    return 0;
}

