#include <iostream>
#include <vector>
#include <queue>

//////////////////
// BFS w/ queue //
//////////////////


using namespace std;

// 1. Color 정의
enum Color { WHITE, GRAY, BLACK };

// 2. Vertex 정의
class Vertex {
public:
    Color color;
    int dist;
    int pi;
    vector<int> adj;

    Vertex() : color(WHITE), dist(INT_MAX), pi(-1) {}

    void initialize() {
        color = WHITE;
        dist = INT_MAX;
        pi = -1;
    }
};

// 3. Graph 정의
class Graph {
public:
    vector<Vertex> vertices;

    Graph(int numVertex) : vertices(numVertex) {}

    void BFS(int s) {
        for (int i=0; i<vertices.size(); i++) {
            if (i != s) {
                vertices[i].initialize();
            }
        }

        vertices[s].color = GRAY;
        vertices[s].dist = 0;
        vertices[s].pi = -1;

        queue<int> Q;
        Q.push(s);

        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();

            for (int v : vertices[u].adj) {
                if (vertices[v].color == WHITE) {
                    vertices[v].color = GRAY;
                    vertices[v].dist = vertices[u].dist + 1;
                    vertices[v].pi = u;
                    Q.push(v);
                }
            }

            vertices[u].color = BLACK;
        }
    }
};



int main() {
    // [#11] p.9 graph example
    int numVertex = 9;
    Graph graph(numVertex);

    graph.vertices[0].adj = {1, 2, 5};
    graph.vertices[1].adj = {0, 3, 4};
    graph.vertices[2].adj = {0, 3};
    graph.vertices[3].adj = {1, 2, 7};
    graph.vertices[4].adj = {1, 5, 7};
    graph.vertices[5].adj = {0, 4, 6, 8};
    graph.vertices[6].adj = {5, 7, 8};
    graph.vertices[7].adj = {3, 4, 6};
    graph.vertices[8].adj = {5, 6};

    graph.BFS(1);

    for (int i=0; i<numVertex; ++i) {
        cout << "Vertex " << i << ": Distance=" << graph.vertices[i].dist << ", Parent=" << graph.vertices[i].pi << endl;
    }

    return 0;
}