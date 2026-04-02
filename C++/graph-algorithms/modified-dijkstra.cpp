#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/*
    EJEMPLO DE ENTRADA Y SALIDA: --------------

    1 2 
    4 4 
    2 10 
    3 4 
    1 2 3 18 
    1 4 8 25 
    1 3 3 10 
    2 3 5 10 
    2 4 4 20 
    3 4 2 18 
    1

    1 2 4 2 3 
    16
*/

/*
    PARES DE ENTEROS S K.
    S: santuario de entrega.
    K: peso mágico en unidades del fragmento a entregar.

    4-TUPLAS A B T M.
    A, B indica la existencia de un sendero que une A con B (santuarios).
    T: tiempo para recorrer el sendero.
    M: estabilidad máxima (peso permitido) del tramo en cuestión.

    I: santuario de partida (inicio).
*/

struct PendingDeliveries {
    int S = -1;
    int K = -1;
};

struct RouteData {
    int A = -1;
    int B = -1;
    int T = -1;
    int M = -1;
};

struct Edge { // arista.
    int to;
    int time;
    int max_stability;
};

struct DijkstraResult {
    int distance;
    vector<int> path;
};

class Assembler {
private:
    vector<PendingDeliveries> pendingDeliveries; // rutas pendientes a cubrir en orden específico.
    vector<RouteData> routeData; // lo utilizaremos para armar el grafo (senderos existentes entre santuarios).
    int I = -1; // santuario de inicio (ID).

    // representa una matriz de adyacencia de manera simplificada
    // el entero representa el santuario de origen.
    // el vector la lista de caminos que parten de dicho santuario.
    unordered_map<int, vector<Edge>> adjList;

    void captureData() {
        string line;

        // leemos la entrada estándar línea por línea.
        while (getline(std::cin, line)) {
            if (line.empty()) continue;

            stringstream ss(line); // utilizamos stringstream para simplificar la lógica de captura de datos.
            vector<int> valuesAtLine;
            int n;

            while (ss >> n) {valuesAtLine.push_back(n);}

            if (valuesAtLine.size() == 1) {
                I = n;
                return;
            }

            switch (valuesAtLine.size()) {
            case 2: {
                int S = valuesAtLine[0];
                int K = valuesAtLine[1];
                pendingDeliveries.push_back({S, K});
                break;
            }

            case 4: {
                int A = valuesAtLine[0];
                int B = valuesAtLine[1];
                int T = valuesAtLine[2];
                int M = valuesAtLine[3];
                routeData.push_back({A, B, T, M});
                break;
            }

            default: break;
            }
        }
    }

    void buildGraph() {
        for (const auto& route : routeData) {

            // extraemos los valores conservando los nombres de variables originales.
            int A = route.A;
            int B = route.B; // santuario a conectar.
            int T = route.T; // tiempo (costo).
            int M = route.M; // estabilidad máxima (condición extra).

            // establecemos las conexiones (aristas del grafo).
            adjList[A].push_back({B, T, M});
            adjList[B].push_back({A, T, M}); // conexión bidireccional.
        }
    }

    public: 
    Assembler() {
        captureData();
        buildGraph();
    }

    // getters ----------------------------------------------------------------
    const unordered_map<int, vector<Edge>>& getGraph() const {return adjList;}
    int getStartNode() {return I;}

    // lo necesitamos para el orden específico.
    const vector<PendingDeliveries>& getPendingDeliveries() const { return pendingDeliveries; }
};

// adaptado de la estructura planteada para al algoritmo en 
// Rosen K. Matemática discreta y sus aplicaciones, 5ta ed.
DijkstraResult runDijkstra(const unordered_map<int, vector<Edge>>& G,
     int a, int z, int currentLoad ) {

    unordered_map<int, int> L;       // L(v): Distancia mínima desde 'a' hacia 'v'. (-1 = Infinito)
    unordered_map<int, int> parent;  // para rastrear el camino (quién descubrió a quién)
    unordered_set<int> S;            // S: Conjunto de vértices ya procesados

    // for i := 1 to n do L(vi) := infinito (-1)
    for (const auto& par : G) {
        L[par.first] = -1; 
    }
    
    // L(a) := 0
    L[a] = 0;

    // S := vacío (El vector ya nace vacío)

    // while z NO pertenece a S
    while (S.find(z) == S.end()) {
        
        // u := vértice con L(u) mínima entre los vértices que no están en S ---
        int u = -1;
        int min_L = -1;
        
        for (const auto& par : L) {
            int v = par.first;
            int dist = par.second;
            
            // si v no está en S y su distancia no es infinito (-1)
            if (S.find(v) == S.end() && dist != -1) {
                if (min_L == -1 || dist < min_L) {
                    min_L = dist;
                    u = v;
                }
            }
        }

        // si u sigue siendo -1, significa que los nodos restantes son inalcanzables.
        if (u == -1) break;

        // S := S U {u}
        S.insert(u);

        // for todos los vértices v que no están en S (es decir, los vecinos de u)
        // G.at(u) nos da el vector de aristas que salen de u
        for (const auto& edge : G.at(u)) {
            int v = edge.to;
            int w = edge.time;
            int M = edge.max_stability;

            // condición: 
            // si la carga actual supera la estabilidad del tramo, no podemos considerarlo.
            if (currentLoad > M) continue;

            if (S.find(v) == S.end()) {
                // if L(u) + w(u, v) < L(v)
                int nueva_distancia = L[u] + w;
                
                // si v es infinito (-1) o encontramos una ruta más corta
                if (L[v] == -1 || nueva_distancia < L[v]) {
                    L[v] = nueva_distancia; // L(v) := L(u) + w(u, v)
                    parent[v] = u;          // anotamos de dónde venimos para armar la ruta final
                }
            }
        }
    } 
    // el while termina cuando llegamos a 'z' (el último santuario a visitar).

    // RECONSTRUCCIÓN DEL CAMINO
    DijkstraResult result;
    result.distance = L[z]; // la longitud del camino más corto entre a y z (será -1 si no hay ruta)
    
    // si llegamos a z, rastreamos los pasos hacia atrás usando el mapa 'parent'
    if (result.distance != -1) {
        int actual = z;
        while (actual != a) {
            result.path.push_back(actual);
            actual = parent[actual];
        }
        result.path.push_back(a);
        
        // inversión manual para obtener el orden deseado.
        int n = result.path.size();
        for (int i = 0; i < n / 2; i++) {
            int temp = result.path[i];
            result.path[i] = result.path[n - 1 - i];
            result.path[n - 1 - i] = temp;
        }
    }

    return result;
}

int main() {
    // captura los datos y construye el grafo (santuarios conectados por senderos).
    Assembler assembler; 

    // extracción de los datos, evitando complejidad de punteros o copias profundas.
    const auto& graph = assembler.getGraph();
    int currentNode = assembler.getStartNode();
    const auto& pendingDeliveries = assembler.getPendingDeliveries();

    vector<int> fullPath;
    int totalTime = 0;

    // calculamos la carga inicial (suma de todos los K)
    int currentLoad = 0;
    for (int i = 0; i < pendingDeliveries.size(); i++) 
        currentLoad += pendingDeliveries[i].K;
    
    // recorrer las entregas por pasos.
    for (int i = 0; i < pendingDeliveries.size(); i++) {
        // ejecutamos Dijkstra pasándole la carga total actual
        DijkstraResult res = runDijkstra(graph, currentNode, pendingDeliveries[i].S, currentLoad); 

        // manejo de error si un santuario es inalcanzable por peso o distancia.
        if (res.distance == -1) return -1;

        totalTime += res.distance;

        // concatenamos el camino
        // si es la primera misión, incluimos el nodo inicial. 
        // en las siguientes, empezamos desde el segundo nodo para no duplicar el punto de entrega anterior.
        size_t startIdx = (i == 0) ? 0 : 1;
        for (size_t j = startIdx; j < res.path.size(); j++) 
            fullPath.push_back(res.path[j]);
    
        currentLoad -= pendingDeliveries[i].K;

        // el destino de esta entrega es el inicio de la siguiente
        currentNode = pendingDeliveries[i].S; 
    }

    // salida con la ruta específica y tiempo.
    for (size_t i = 0; i < fullPath.size(); i++) 
        cout << fullPath[i] << (i == fullPath.size() - 1 ? "" : " ");
    
    cout << endl << totalTime << endl;

    return 0;
}

