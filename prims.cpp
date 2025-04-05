#include <iostream>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;


int minCost(int minEdge[], bool checkVertex[], int V) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (!checkVertex[v] && minEdge[v] < min) {
            min = minEdge[v];
            min_index = v;
        }
    }
    return min_index;
}

void primMST(int** graph, int V) {
    int parent[V];
    int minEdge[V];
    bool checkVertex[V];

    for (int i = 0; i < V; i++) {
        minEdge[i] = INT_MAX;
        checkVertex[i] = false;
    }

    minEdge[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minCost(minEdge, checkVertex, V);
        checkVertex[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !checkVertex[v] && graph[u][v] < minEdge[v]) {
                parent[v] = u;
                minEdge[v] = graph[u][v];
            }
        }
    }
}

int main() {
    srand(time(0));
    ofstream fout1("primsAvgtime.txt");
    int n = 100;

    for (int V = 1000; V <= 10000; V += 1000) {
        float totalDuration = 0.0;

        for (int j = 0; j < n; j++) {
            int** graph = new int*[V];
            for (int i = 0; i < V; i++) {
                graph[i] = new int[V];
                for (int j = 0; j < V; j++) {
                    graph[i][j] = 0;
                }
            }

            for (int i = 0; i < V; i++) {
                for (int j = i + 1; j < V; j++) {
                    int weight = rand() % 100 + 1;
                    graph[i][j] = weight;
                    graph[j][i] = weight;
                }
            }

            clock_t start = clock();
            primMST(graph, V);
            clock_t stop = clock();
            double duration = (double)(stop - start) / CLOCKS_PER_SEC * 10e6;
            totalDuration += duration;

            for (int i = 0; i < V; i++) {
                delete[] graph[i];
            }
            delete[] graph;
        }

        fout1 << V << "," << (float)totalDuration / n << endl;
    }

    fout1.close();
    return 0;
}
