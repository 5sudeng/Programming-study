#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define INF INT_MAX

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    vector<Edge> edges;
};

void printPath(const vector<int>& parent, int vertex) {
    if (parent[vertex] == -1) {
        cout << vertex << " ";
        return;
    }
    printPath(parent, parent[vertex]);
    cout << vertex << " ";
}

bool BellmanFord(const Graph& graph, int vertices, int src, vector<int>& dist, vector<int>& parent) {
    dist.assign(vertices, INF);
    parent.assign(vertices, -1);
    dist[src] = 0;

    for (int i = 1; i <= vertices - 1; i++) {
        for (const Edge& edge : graph.edges) {
            int u = edge.src;
            int v = edge.dest;
            int weight = edge.weight;
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    for (const Edge& edge : graph.edges) {
        int u = edge.src;
        int v = edge.dest;
        int weight = edge.weight;
        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            cout << "Graph contains a negative weight cycle\n";
            return false;
        }
    }
    return true;
}

void Dijkstra(const vector<vector<int>>& graph, int src, vector<int>& dist, vector<int>& parent) {
    int V = graph.size();
    vector<bool> sptSet(V, false);
    dist.assign(V, INF);
    parent.assign(V, -1);
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = -1;

        for (int i = 0; i < V; i++) {
            if (!sptSet[i] && (u == -1 || dist[i] < dist[u]))
                u = i;
        }

        sptSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] != INF && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }
}

void Johnson(Graph& graph) {
    int V = graph.V;
    int new_vertex_count = V + 1;
    int original_edges_count = graph.edges.size();

    Graph newGraph = {new_vertex_count, original_edges_count + V, graph.edges};

    for (int i = 0; i < V; i++) {
        newGraph.edges.push_back({V, i, 0});
    }

    vector<int> dist(new_vertex_count), parent(new_vertex_count), h(V);

    if (!BellmanFord(newGraph, new_vertex_count, V, dist, parent)) {
        return;
    }

    for (int i = 0; i < V; i++) {
        h[i] = dist[i];
    }

    vector<vector<int>> reweightedGraph(V, vector<int>(V, INF));
    for (const Edge& edge : graph.edges) {
        int u = edge.src;
        int v = edge.dest;
        int weight = edge.weight + h[u] - h[v];
        reweightedGraph[u][v] = weight;
    }

    for (int u = 0; u < V; u++) {
        Dijkstra(reweightedGraph, u, dist, parent);
        cout << "\nShortest distances from vertex " << u << ":\n";
        for (int v = 0; v < V; v++) {
            if (dist[v] != INF) {
                // Reconstruct the original distance using the h-values
                dist[v] = dist[v] + h[v] - h[u];
                cout << "Distance to vertex " << v << " is " << dist[v] << endl;
                cout << "Path: ";
                printPath(parent, v);
                cout << endl;
            } else {
                cout << "No path to vertex " << v << endl;
            }
        }
    }
}

int main() {
    int V = 5;
    Graph graph = {V, 7, {
        {0, 1, -1},
        {0, 3, 2},
        {1, 2, 4},
        {1, 3, 3},
        {1, 4, 2},
        {2, 4, 1},
        {3, 4, 5}
    }};

    Johnson(graph);

    return 0;
}