#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

class Edge {
    public:
    int src, dest, weight;
};

class Graph {
    public:
    int V, E;
    Edge* edges;
};

class DisjointSets {
    public:
    int* parent;
    int* rank;

    DisjointSets(int n) {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (rank[u] < rank[v])
            parent[u] = v;
        else if (rank[u] > rank[v])
            parent[v] = u;
        else {
            parent[v] = u;
            rank[u]++;
        }
    }

};

bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

void kruskalMST(Graph& graph) {
    Edge* result = new Edge[graph.V - 1];
    sort(graph.edges, graph.edges + graph.E, compareEdges);
    
    DisjointSets ds(graph.V);

    int e = 0, i = 0;
    while (e < graph.V - 1 && i < graph.E) {
        Edge nextEdge = graph.edges[i++];
        int uSet = ds.find(nextEdge.src);
        int vSet = ds.find(nextEdge.dest);

        if (uSet != vSet) {
            result[e++] = nextEdge;
            ds.merge(uSet, vSet);
        }
    }
    delete[] result;
}

int main() {
    srand(time(0));
    ofstream fout("kruskalsAvgtime.txt");
    int n = 100;

    for (int V = 1000; V <= 10000; V += 1000) {
        float totalDuration = 0.0;

        for (int j = 0; j < n; j++) {
            Graph graph;
            graph.V = V;
            graph.E = V * (V - 1) / 2;
            graph.edges = new Edge[graph.E];
            int index = 0;

            for (int i = 0; i < V; i++) {
                for (int j = i + 1; j < V; j++) {
                    int weight = rand() % 100 + 1;
                    graph.edges[index].src = i;
                    graph.edges[index].dest = j;
                    graph.edges[index].weight = weight;
                    index++;
                }
            }

            clock_t start = clock();
            kruskalMST(graph);
            clock_t end = clock();
            totalDuration += double(end - start) / CLOCKS_PER_SEC * 10e6;
            
            delete[] graph.edges;
        }
        fout << V << "," << totalDuration / n << endl;
    }
    fout.close();
    return 0;
}
