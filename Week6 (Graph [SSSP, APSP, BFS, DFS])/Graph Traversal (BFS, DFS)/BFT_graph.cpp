#include <iostream>
#include <vector>
#include <cstdlib>
#include <unordered_map>
#include <string>
#include <queue>

using namespace std;
class UndiGraph {
public:
    // Constructor to initialize the graph with vertices and edges
    UndiGraph(const vector<int>& V, const vector<pair<int, int>>& E) {
        this->V = V;
        for (const auto& v : V) {
            neighbors[v] = vector<int>();
        }
        for (const auto& edge : E) {
            neighbors[edge.first].push_back(edge.second);
            neighbors[edge.second].push_back(edge.first);
        }
    }


    /*
    만약 main함수가 이런식으로 주어진다면 undigraph만 undigraph + addedge로 쪼개면 됨!
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    */

    /*
    UndiGraph(const vector<int>& V) {
        this->V = V;
        for (const auto& v : V) {
            neighbors[v] = vector<int>();
        }
    }

    // Function to insert an edge
    void addEdge(int v, int w) {
        neighbors[v].push_back(w);
        neighbors[w].push_back(v); // For undirected graph
    }
    */



    // BFS function to traverse the graph starting from a root node
    void BFS(const int& root) {
        if (root == NULL) return;

        queue<int> q;
        unordered_map<int, bool> visited;

        for (const auto& v : V) {
            visited[v] = false;
        }

        q.push(root);
        visited[root] = true;

        while (!q.empty()) {
            int curNode = q.front();
            q.pop();
            cout << curNode << " ";

            for (const auto& neighbor : neighbors[curNode]) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }

        for (int k: V) {
            if (!visited[k]) {
                q.push(k);
                visited[k] = true;
                while (!q.empty()) {
                    int curNode = q.front();
                    q.pop();
                    cout << curNode << ' ';
                    for (int v : neighbors[curNode]) {
                        if (!visited[k]) {
                            q.push(v);
                            visited[v] = true;
                        }
                    }

                }
            }
        } 
    }

private:
    vector<int> V;
    unordered_map<int, vector<int>> neighbors; // Adjacency list representation
};

int main() {
    vector<int> vertices = {1,2,3,4,5,6,7,8};
    vector<pair<int, int>> edges = {{1,2}, {1,3}, {2, 8}, {3, 4}, {3, 5}, {4, 5}, {6, 7}, {6, 8}, {7, 8}};

    // Create the graph
    UndiGraph graph(vertices, edges);

    cout << "BFS starting from vertex 1:" << endl;
    graph.BFS(1);
    // 1 2 3 8 4 5 6 7

    return 0;
}






//혹은, 그래프 자체로 주어졌을 경우
//include queue하기
// #include <queue>

// void bfs_helper(const vector<vector<int>>& graph, int node, vector<bool>& visited) {
//     queue<int> q;
//     visited[node] = true;
//     q.push(node);

//     while (!q.empty()) {
//         int v = q.front();
//         q.pop();
//         cout << v << " ";

//         for (int i : graph[v]) {
//             if (!visited[i]) {
//                 visited[i] = true;
//                 q.push(i);
//             }
//         }
//     }
// }

// void bfs(const vector<vector<int>>& graph, int num_nodes, int start_node) {
//     vector<bool> visited(num_nodes + 1, false);
//     bfs_helper(graph, start_node, visited);

//     for (int node = 1; node <= num_nodes; ++node) {
//         if (!visited[node]) {
//             bfs_helper(graph, node, visited);
//         }
//     }
//     cout << endl;
// }


// //deque 직접 구현한 버전

// // vector<int> bfs_helper(const vector<vector<int>>& graph, int node, vector<bool>& visited) {
// //     Deque queue(graph.size());
// //     queue.add_rear(node);
// //     visited[node] = true;

// //     vector<int> result;

// //     while (!queue.is_empty()) {
// //         int v = queue.delete_front();
// //         result.push_back(v);
// //         cout << v << " ";

// //         for (int neighbor : graph[v]) {
// //             if (!visited[neighbor]) {
// //                 queue.add_rear(neighbor);
// //                 visited[neighbor] = true;
// //             }
// //         }
// //     }
// //     return result;
// // }

// // void bfs(const vector<vector<int>>& graph, int num_nodes, int start_node) {
// //     vector<bool> visited(num_nodes + 1, false);
// //     bfs_helper(graph, start_node, visited);

// //     for (int node = 1; node <= num_nodes; ++node) {
// //         if (!visited[node]) {
// //             bfs_helper(graph, node, visited);
// //         }
// //     }
// //     cout << endl;
// // }

// int main() {
//     vector<vector<int>> graph = {
//         {},
//         {2, 3},
//         {8},
//         {4, 5},
//         {5},
//         {},
//         {7, 8},
//         {8},
//         {}
//     };

//     cout<<"Graph size: "<<graph.size()<<endl;

//     vector<bool> visited(9, false);
//     cout << "BFS starting from vertex 1:\n";
//     bfs(graph, graph.size()-1, 1);
//     cout<<endl;
//     // bfs_deque(graph, 1, visited);

//     return 0;
// }
