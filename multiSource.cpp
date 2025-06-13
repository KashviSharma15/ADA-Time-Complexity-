#include <iostream>
#include <fstream>
#include <climits>
#include <cstdlib>
#include <vector>
#include <queue>

using namespace std;

const int MAX_V = 510;

struct Edge {
    int to, weight;
};

struct Graph {
    int V;
    vector<Edge> adj[MAX_V];

    Graph(int vertices) : V(vertices) {}

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
    }
};

void multiSourceShortestPath(Graph &graph, const vector<int>& sources, vector<int>& dist) {
    fill(dist.begin(), dist.end(), INT_MAX);
    queue<int> q;
    for (int source : sources) {
        dist[source] = 0;
        q.push(source);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const Edge& e : graph.adj[u]) {
            if (dist[e.to] > dist[u] + e.weight) {
                dist[e.to] = dist[u] + e.weight;
                q.push(e.to);
            }
        }
    }
}

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;

    Graph graph(V);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter edges in format: from to weight (0-based indexing)\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cout << "Edge " << i + 1 << ": ";
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }

    vector<int> dist(V);
    vector<int> sources = {0}; 

    multiSourceShortestPath(graph, sources, dist);

    int shortest = dist[V - 1];
    if (shortest == INT_MAX) {
        cout << "No path from source to destination.\n";
    } else {
        cout << "Shortest path cost from vertex 0 to vertex " << V - 1 << " is: " << shortest << endl;
    }

    return 0;
}