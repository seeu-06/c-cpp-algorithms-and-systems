#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <list> // debe incluir implicitamente a <iterator>.
using namespace std;

/*
    N: Cantidad de estados que conforman la máquina.
    T: Cantidad de transiciones.

    O F L E D (5-tupla)
    O - F: Transición desde el estado O hacia el F
    leyendo L en la cadena, escribiendo E y realizando un desplazamiento D.
*/

struct TransitionRule {
    int nextState; // F
    char readSymbol; // L
    char writeSymbol; // E
    char direction; // D
};

// controlador de la cinta de la MT.
// permite gestionar los desplazamientos y simular la "cinta infinita".
class Tape { 
    list<char> cells;
    list<char>::iterator head; // representa el "cabezal" sobre la cinta.
    const char blank = '_';

    public:
    Tape(const vector<char>& initial_input) { 
        // aquí, copiamos la entrada a una lista enlazada para poder desplazarnos 
        // en la cinta infinitamente hacia la izquierda o a la derecha.
        for(char c : initial_input) cells.push_back(c);
        
        if(cells.empty()) cells.push_back(blank);
        head = cells.begin();
    }

    void moveLeft() {
        if (head == cells.begin()) {
            cells.push_front(blank);
            head = cells.begin();
        } else { --head; }
    }

    void moveRight() {
        auto next_it = next(head); // observamos qué hay después del cabezal;
        if (next_it == cells.end()) {
            cells.push_back(blank);
            head = prev(cells.end());
        } else { ++head; }
    }

    char read() { return *head; }
    void write(char symbol) { *head = symbol; }

    void printTape() {
        for (char c : cells) {
            if (c != blank) 
                cout << c;
        }
        cout << endl;
    }
};

class TuringMachine {
    Tape tape;
    unordered_map<int, vector<TransitionRule>> transition_function;
    int totalStates;
    int currentState;
    vector<char> input_symbols;

    public:
    // S es el número de estados. El resto se interpreta de la función de transición.
    // Tape (t) es la cinta con la entrada.
    TuringMachine(int S, const vector<char>& I, const unordered_map<int, vector<TransitionRule>>& tf, 
        int initial_state, const vector<char>& initial_entry) 
        
        : totalStates(S), input_symbols(I), transition_function(tf), currentState(initial_state), tape(initial_entry) 
        {}

    void run() {
        bool running = true;

        while (running) {
            // leemos el símbolo que apunta el cabezal en la cinta.
            char currentSymbol = tape.read();
            bool transitionFound = false;

            // buscamos si el estado actual tiene transiciones definidas.
            auto state = transition_function.find(currentState);
            if (state != transition_function.end()) {

                // recorremos las reglas de transición definidas para el estado.
                // find devolvió un objeto Pair con el estado (first) y las reglas de transición (second).
                for (const TransitionRule& rule : state->second) {
                    if (rule.readSymbol == currentSymbol) {

                        tape.write(rule.writeSymbol);
                        currentState = rule.nextState;

                        if (rule.direction == 'D') {
                            tape.moveRight();
                        } else if (rule.direction == 'I') {
                            tape.moveLeft();
                        } // para el símbolo 'S' no hay desplazamiento.

                        transitionFound = true;
                        break;
                    }
                }
            }
            // la máquina se detiene si no encuentra una transición definida (crash).
            if (!transitionFound) running = false;  
        }

        tape.printTape();
        // el estado único de aceptación, por definición, es el estado final (n-1).
        if (currentState == totalStates -1) cout << "Aceptada\n";
        else cout << "Rechazada\n";
    }
    
};

class Assembler {
    // utilizamos un vector (dinámico), para guardar todos los símbolos de la cinta.
    // en una MT, este conjunto lo conocemos como I.
    vector<char> I;

    // procesamos las reglas de transición de la MT.
    // el mapa almacena las transiciones definidas para cada estado.
    unordered_map<int, vector<TransitionRule>> transition_function;

    // cada nodo o "casilla", en conjunto, representa la cinta de la máquina.
    vector<char> entry;

    //
    int N;

    void captureData() {
        string line;
        char aux;
        int T;

        // capturamos la primera linea para obtener la cantidad de estados y transiciones.
        getline(std::cin, line);
        stringstream ss(line); // utilizamos stringstream para simplificar la lógica de captura de datos.
        ss >> N >> T;

        // capturamos la segunda linea para obtener los símbolos de entrada (conjunto I).
        getline(std::cin, line);
        stringstream ss_symbols(line);
        while(ss_symbols >> aux) { I.push_back(aux); }

        // a partir del número de transiciones indicadas (T), las procesamos y
        // almacenamos en un mapa que representará la función de transición.
        for (int i = 0; i < T; i++) {
            string transition;
            int state, F;
            char L, E, D;

            getline(std::cin, transition);
            stringstream ss(transition);
            ss >> state >> F >> L >> E >> D;

            transition_function[state].push_back({F, L, E, D});
        }

        // finalmente, procesamos la entrada (lo que estará sobre la "cinta" de la máquina).
        if(!getline(std::cin, line)) return;
        stringstream ss_entry(line);
        while(ss_entry >> aux) { entry.push_back(aux); }
    }

    public:
    Assembler() {
        captureData();
    }

    TuringMachine buildMachine() {
        return TuringMachine(N, I, transition_function, 0, entry);
    }
};

int main() {
    // captura y procesa los datos para preparar la máquina.
    Assembler assembler;
    TuringMachine TM = assembler.buildMachine();
    TM.run();

    return 0;
}