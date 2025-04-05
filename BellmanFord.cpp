#include <iostream>
#include <climits>
#include <cstdlib>
#include <ctime>   
#include <fstream>

using namespace std;

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, edgeCount;
    Edge *edges;

    Graph(int V, int maxEdges) { 
        this->V = V; edgeCount = 0; edges = new Edge[maxEdges];
    }

    ~Graph() { 
        delete[] edges; 
    }

    void addEdge(int u, int v, int weight) {
        edges[edgeCount].src = u;
        edges[edgeCount].dest = v;
        edges[edgeCount].weight = weight;
        edgeCount++;

        edges[edgeCount].src = v;
        edges[edgeCount].dest = u;
        edges[edgeCount].weight = weight;
        edgeCount++;
    }
};

void bellmanFord(const Graph &graph, int src, int *dist) {
    fill(dist, dist + graph.V, INT_MAX);
    dist[src] = 0;

    for (int i = 1; i < graph.V; ++i) {
        for (int j = 0; j < graph.edgeCount; j++) {
            Edge edge = graph.edges[j];
            if (dist[edge.src] != INT_MAX && dist[edge.src] + edge.weight < dist[edge.dest]) {
                dist[edge.dest] = dist[edge.src] + edge.weight;
            }
        }
    }
}

int main() {
    srand(time(0));
    ofstream fout("BellmanFord.txt");
    int n = 1000;

    for (int V = 10; V <= 200; V += 10) {
        int maxEdges = V * (V - 1);
        clock_t totalTime = 0;  

        for (int j = 0; j < n; j++) {
            Graph graph(V, maxEdges);
            for (int i = 0; i < V; i++) {
                for (int j = i + 1; j < V; j++) {
                    graph.addEdge(i, j, rand() % 100 + 1);
                }
            }

            int *dist = new int[V];

            clock_t start = clock();
            bellmanFord(graph, 0, dist);
            clock_t end = clock();

            totalTime += (end - start);

            delete[] dist;
        }

        float avgTime = (float)totalTime / CLOCKS_PER_SEC / n * 1000;  
        fout << V << "," << avgTime << endl;

    }

    fout.close();
    return 0;
}
