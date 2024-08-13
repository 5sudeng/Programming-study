// #include <iostream>
// #include <vector>
// #include <list>

// using namespace std;

// class Graph {
// public:
//     Graph(int vertices) {
//         V = vertices;
//         adj.resize(vertices);
//         visited.resize(vertices, false);
//     }

//     void addEdge(int v, int w) {
//         adj[v].push_back(w);
//         // adj[w].push_back(v); // For undirected graph
//     }

//     //만약 vertex, edge 따로준다면
//     /*
//     vector<int> vertices = {1, 2, 3, 4, 5, 6, 7, 8};
//     vector<pair<int, int>> edges = {
//         {1, 2}, {1, 3},
//         {2, 1}, {2, 8},
//         {3, 1}, {3, 4}, {3, 5},
//         {4, 3}, {4, 5},
//         {5, 3}, {5, 4},
//         {6, 7},
//         {7, 6},
//         {8, 2}
//     };
//     */ 
//     // Graph를 constructor 이렇게 바꾸기 
//     // Graph(const vector<int>& vertices, const vector<pair<int, int>>& edges) {
//     //     V = vertices.size();
//     //     adj.resize(V + 1); // Assuming vertices are 1-indexed
//     //     visited.resize(V + 1, false);

//     //     for (const auto& edge : edges) {
//     //         addEdge(edge.first, edge.second);
//     //     }
//     // }

//     void DFS(int v) {
//         fill(visited.begin(), visited.end(), false);
//         DFSUtil(v);
//         for (auto k = adj[v].begin(); k != adj[v].end(); ++k) {
//             if (!visited[*k]) {
//                 DFSUtil(*k);
//             }
//         }
//         for (int i = 1; i < V; ++i) {
//             if (!visited[i]) {
//                 DFSUtil(i);
//             }
//         }
//         cout << endl;
//     }

//     void DFSAll() {
//         fill(visited.begin(), visited.end(), false);
//         for (int i = 0; i < V; ++i) {
//             if (!visited[i]) {
//                 DFSUtil(i);
//             }
//         }
//         cout << endl;
//     }

// private:
//     int V; // Number of vertices
//     vector<list<int>> adj; // Adjacency lists
//     vector<bool> visited; // Visited vertices

//     void DFSUtil(int v) {
//         visited[v] = true;
//         cout << v << " ";

//         for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
//             if (!visited[*i]) {
//                 DFSUtil(*i);
//             }
//         }
//     }
// };

// int main() {
//     Graph graph(9);

//     // Add edges
//     graph.addEdge(1, 2);
//     graph.addEdge(1, 3);
//     graph.addEdge(2, 8);
//     graph.addEdge(3, 4);
//     graph.addEdge(3, 5);
//     graph.addEdge(4, 5);
//     graph.addEdge(6, 7);
//     graph.addEdge(6, 8);
//     graph.addEdge(7, 8);

//     cout << "DFS starting from vertex 1:" << endl;
//     graph.DFS(1);

//     cout << "DFS for all vertices:" << endl;
//     graph.DFSAll();

//     return 0;
// }



/////////// vector 형태 /////////////////
/////////// undirected, directed 모두 표현 가능 ////////
#include <iostream>
#include <vector>

using namespace std;


class Graph {
public:
    Graph(const vector<vector<int>>& graph) {
        adj = graph;
        V = graph.size();
        visited.resize(V, false);
    }

    void DFS(int v) {
        // 시작 정점에서 DFS 수행
        DFSUtil(v);

        // 방문되지 않은 다른 섬들 탐색
        for (int i = 1; i < V; ++i) { // 인덱스 1부터 시작
            if (!visited[i]) {
                DFSUtil(i);
            }
        }
        cout << endl;
    }

private:
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency lists
    vector<bool> visited; // Visited vertices

    void DFSUtil(int v) {
        visited[v] = true;
        cout << v << " ";

        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor);
            }
        }
    }
};



int main() {
    vector<vector<int>> graph = {
        {},
        {2, 3},
        {8},
        {4, 5},
        {5},
        {},
        {7},
        {},
        {}
    };

    //1 2 8 3 4 5 6 7

    cout << "Graph size: " << graph.size() << endl;

    Graph g(graph);
    cout << "DFS starting from vertex 1:\n";
    g.DFS(1);

    return 0;
}
