#include <iostream>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

struct Graph {
    int V;
    int** adj;

    Graph(int V) : V(V) {
        adj = new int*[V];
        for (int i = 0; i < V; i++) {
            adj[i] = new int[V];
            for (int j = 0; j < V; j++) {
                adj[i][j] = (i == j) ? 0 : INT_MAX;
            }
        }
    }

    void addEdge(int u, int v, int weight) {
        adj[u][v] = weight;
        adj[v][u] = weight;
    }

    ~Graph() {
        for (int i = 0; i < V; i++) {
            delete[] adj[i];
        }
        delete[] adj;
    }
};

void floydWarshall(Graph &graph) {
    for (int k = 0; k < graph.V; k++) {
        for (int i = 0; i < graph.V; i++) {
            for (int j = 0; j < graph.V; j++) {
                if (graph.adj[i][k] != INT_MAX && graph.adj[k][j] != INT_MAX) {
                    int newDist = graph.adj[i][k] + graph.adj[k][j];
                    if (graph.adj[i][j] > newDist) {
                        graph.adj[i][j] = newDist;
                    }
                }
            }
        }
    }
}

int main() {
    srand(time(0));
    ofstream fout("FloydWarshall.txt");
    int n = 1000; 
    for (int V = 10; V <= 200; V += 10) {
        clock_t totalTime = 0;

        for (int j = 0; j < n; j++) {  
            Graph graph(V);

            for (int i = 0; i < V; i++) {
                for (int j = i + 1; j < V; j++) {
                    graph.addEdge(i, j, rand() % 100 + 1);
                }
            }

            clock_t start = clock();
            floydWarshall(graph);
            clock_t end = clock();

            totalTime += (end - start);
        }

        float avgTime = (float)totalTime / CLOCKS_PER_SEC / n * 1000;  
        fout << V << "," << avgTime << endl;
    }

    fout.close();
    return 0;
}
