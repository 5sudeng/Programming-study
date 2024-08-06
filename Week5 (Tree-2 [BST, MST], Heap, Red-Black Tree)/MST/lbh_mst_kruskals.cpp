#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Edge {
public:
    int src, dest, weight;
};

class Graph {
public:
    int V, E;
    vector<Edge> edges;

    Graph(int V, int E) {
        this->V = V;
        this->E = E;
    }

    void addEdge(int src, int dest, int weight) {
        Edge edge;
        edge.src = src;
        edge.dest = dest;
        edge.weight = weight;
        edges.push_back(edge);
    }

    int find(vector<int>& parent, int i) {
        if (parent[i] != i)
            parent[i] = find(parent, parent[i]);
        return parent[i];
    }

    void Union(vector<int>& parent, vector<int>& rank, int x, int y) {
        int rootX = find(parent, x);
        int rootY = find(parent, y);

        if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }

    static bool compareEdges(Edge a, Edge b) {
        return a.weight < b.weight;
    }

    void KruskalMST() {
        vector<Edge> result(V);
        int e = 0;
        int i = 0;

        sort(edges.begin(), edges.end(), compareEdges);

        vector<int> parent(V);
        vector<int> rank(V, 0);

        for (int v = 0; v < V; v++)
            parent[v] = v;

        while (e < V - 1 && i < edges.size()) {
            Edge nextEdge = edges[i++];
            int x = find(parent, nextEdge.src);
            int y = find(parent, nextEdge.dest);

            if (x != y) {
                result[e++] = nextEdge;
                Union(parent, rank, x, y);
            }
        }

        cout << "Following are the edges in the constructed MST\n";
        for (i = 0; i < e; i++)
            cout << result[i].src << " -- " << result[i].dest << " == " << result[i].weight << endl;
    }
};

int main() {
    int V = 4;
    int E = 5;
    Graph graph(V, E);

    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 6);
    graph.addEdge(0, 3, 5);
    graph.addEdge(1, 3, 15);
    graph.addEdge(2, 3, 4);

    graph.KruskalMST();

    return 0;
}