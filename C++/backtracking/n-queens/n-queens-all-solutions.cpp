#include <iostream>
using namespace std;

/*
    N-QUEENS: FULL STATE-SPACE EXPLORATION
    
    Esta implementación es una variante de 'n-queens-naive.cpp' diseñada para 
    realizar una búsqueda exhaustiva en el árbol de espacio de estados.
    
    Diferencia clave: Se ha eliminado la propagación del control booleano, 
    obligando al algoritmo a ejecutar el proceso de 'backtrack' (retroceso) 
    incluso tras encontrar una solución. Esto permite agotar todas las ramas 
    de ejecución y contabilizar el total de configuraciones válidas posibles.
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
            cout << "| ";
            for (int j = 0; j < N; j++) {
                cout << board[i][j] << " ";
            }
            cout <<"|\n";
        }
        cout << "\n";
    }

    void n_queens_algorithm(int X = 0, int q_placed = 0) {
        if (q_placed == N) {
            printBoard();
            return;
        } 
        
        for (int currentY = 0; currentY < N; currentY++) {
      
            if (board[X][currentY] == '_') {
                board[X][currentY] = 'Q';
                queenPositions[q_placed].x = X;
                queenPositions[q_placed].y = currentY;

                markThreats(X, currentY);
                n_queens_algorithm(X + 1, q_placed + 1);

                // backtrack --------------------------------------------
                board[X][currentY] = '_';
                queenPositions[q_placed].x = -1;
                queenPositions[q_placed].y = -1;
                removeThreats();
            } 
        }
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

