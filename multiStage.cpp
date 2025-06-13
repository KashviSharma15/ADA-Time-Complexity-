#include <iostream>
#include <fstream>
#include <climits>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_V = 510;
const int MAX_EDGES = 500;
const int MAX_STAGES = 10;

struct Edge {
    int to, weight;
};

struct Graph {
    int V;
    Edge adj[MAX_V][MAX_EDGES];
    int edgeCount[MAX_V];

    Graph(int vertices) {
        V = vertices;
        for (int i = 0; i < V; i++) edgeCount[i] = 0;
    }

    void addEdge(int u, int v, int w) {
        if (edgeCount[u] < MAX_EDGES) {
            adj[u][edgeCount[u]].to = v;
            adj[u][edgeCount[u]].weight = w;
            edgeCount[u]++;
        }
    }
};

int multistageShortestPath(Graph &graph) {
    int dist[MAX_V];
    for (int i = 0; i < graph.V; i++) dist[i] = INT_MAX;
    dist[graph.V - 1] = 0;

    for (int i = graph.V - 2; i >= 0; i--) {
        for (int j = 0; j < graph.edgeCount[i]; j++) {
            int v = graph.adj[i][j].to;
            int w = graph.adj[i][j].weight;
            if (dist[v] != INT_MAX)
                dist[i] = min(dist[i], w + dist[v]);
        }
    }

    return dist[0];
}

int main() {
    srand(time(0));
    ofstream fout("MultiStage.txt");

    const int n = 10000;

    for (int stages = 3; stages <= 8; stages++) {
        for (int V = 10; V <= 200; V += 10) {
            if (stages > V) continue;

            double totalTime = 0;

            for (int t = 0; t < n; t++) {
                Graph graph(V);
                int stage[MAX_STAGES][MAX_V] = {0};
                int size[MAX_STAGES] = {0};

                stage[0][size[0]++] = 0;
                stage[stages - 1][size[stages - 1]++] = V - 1;

                int left = V - 2, id = 1;
                for (int s = 1; s < stages - 1; s++) {
                    int count = left / (stages - 2) + (s <= left % (stages - 2));
                    for (int i = 0; i < count; i++) stage[s][size[s]++] = id++;
                }

                for (int s = 0; s < stages - 1; s++) {
                    for (int i = 0; i < size[s]; i++) {
                        for (int j = 0; j < size[s + 1]; j++) {
                            int w = rand() % 100 + 1;
                            graph.addEdge(stage[s][i], stage[s + 1][j], w);
                        }
                    }
                }

                clock_t start = clock();
                multistageShortestPath(graph);
                clock_t end = clock();

                totalTime += (double)(end - start) / CLOCKS_PER_SEC * 1e6;
            }

            fout << V << "," << stages << " : " << totalTime / n << endl;
        }
        fout << endl;
    }

    fout.close();
    return 0;
}
