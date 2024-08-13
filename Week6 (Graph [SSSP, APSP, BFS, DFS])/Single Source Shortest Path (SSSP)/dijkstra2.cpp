#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>

using namespace std;

class Graph {
    int V;
    bool neg = true;
    vector<vector<int>> *adj;
    vector<int> *dist;

public:
    // 초기화
    Graph(int V) {
        this->V = V;
        adj = new vector<vector<int>>[V+1];
        //source가 0이라면 adj = new vector<vector<int>>[V]
        dist = new vector<int>(V+1,INT_MAX);
        //source가 0이라면 dist = new vector<int>(V,INT_MAX);
    }

    // Edge 넣기
    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
    }

    void dijkstra(int source);
};


void Graph::dijkstra(int source) {
    // 초기화
    priority_queue<pair<int, int>> pq;  // Heap
    list<int> S;                        // 부분 집합
    std::list<int>::iterator it;        
    dist->at(source) = 0;               // root 거리 = 0

    pq.push({0,source});

    while(!pq.empty()){
        int u_d = -pq.top().first;  // node 거리 찾기
        int u = pq.top().second;  // node 찾기
        pq.pop();
        S.push_back(u);           // Heap에서 나오면 S에 넣기
        for(int i=0;i<adj[u].size();i++){
            int v = adj[u][i][0];
            int w = adj[u][i][1];
            it = find(S.begin(), S.end(), v);
            if(it == S.end()){   // Node가 S에 없을때만 relax 작동
                // relax
                if(dist->at(v) > dist->at(u)+w){
                    dist->at(v) = dist->at(u)+w;
                    pq.push({-w,v});
                }
            }
        }
    }

    for (int i = source; i < V+1; ++i) {   //source가 0이라면 i<V
        cout << "Node " << i << ": " << dist->at(i) << endl;

    }
}

int main() {
    int V = 5;
    Graph g(V);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 1, 8);
    g.addEdge(2, 4, 10);
    g.addEdge(3, 1, 2);
    g.addEdge(3, 4, 1);
    g.addEdge(3, 5, 7);
    g.addEdge(4, 2, 10);
    g.addEdge(4, 5, 9);
    g.addEdge(5, 3, 7);
    g.addEdge(5, 4, 9);

    int source = 1;
    g.dijkstra(source);

    return 0;
}
