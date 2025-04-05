#include <iostream>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

void addEdge(int** adj, int u, int v, int weight) {
    adj[u][v] = adj[v][u] = weight;
}

int findShortestEdge(int* dist, bool* visited, int V) {
    int minIndex = -1, minDistance = INT_MAX;
    for (int i = 0; i < V; i++) {
        if (!visited[i] && dist[i] < minDistance) {
            minDistance = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void dijkstra(int** adj, int V, int src, int& skipped) {
    int* dist = new int[V];
    bool* visited = new bool[V]();

    for (int i = 0; i < V; i++) dist[i] = INT_MAX;
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = findShortestEdge(dist, visited, V);
        if (u == -1) {
            skipped++;
            break;
        }
        visited[u] = true;
        for (int v = 0; v < V; v++) {
            if (!visited[v] && adj[u][v] != INT_MAX && dist[u] + adj[u][v] < dist[v]) {
                dist[v] = dist[u] + adj[u][v];
            }
        }
    }
    delete[] dist;
    delete[] visited;
}

int main() {
    srand(time(0));
    int skipped = 0;
    ofstream fout1("dijkstraTime.txt");
    const int n = 1000;

    for (int V = 100; V <= 1000; V += 100) {
        double totalDuration = 0.0;

        for (int j = 0; j < n; j++) {
            int** adj = new int*[V];
            for (int i = 0; i < V; i++) {
                adj[i] = new int[V];
                for (int j = 0; j < V; j++) {
                    adj[i][j] = (i == j) ? 0 : INT_MAX;
                }
            }

            for (int i = 0; i < V; i++) {
                for (int j = i + 1; j < V; j++) {
                    addEdge(adj, i, j, rand() % 1000 + 1);
                }
            }

            clock_t start = clock();
            dijkstra(adj, V, 0, skipped);
            totalDuration += (double)(clock() - start) / CLOCKS_PER_SEC * 1e6;

            for (int i = 0; i < V; i++) delete[] adj[i];
            delete[] adj;
        }
        fout1 << V << "," << totalDuration / n << endl;
    }

    fout1.close();
    return 0;
}
