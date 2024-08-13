#include <iostream>
#include <vector>
#include <limits>
#include <tuple>
#include <queue>


using namespace std;

const int INF = numeric_limits<int>::max();



/* /
Johnson's Algorithm : (V^2logv + VE)
* sparse한 graph 인 경우(E = V), Dijkstra가  < Floyd-Warshall보다 더 빠르다. ( O(V^2 + VlogV)) -> O(V^2logV)
* new source s 를 추가 및 Bellmanford를 활용해서 reweighting, non-negative weights
* Dijkstra를 활용해서 all pair shsortest path run
*/


struct Edge{ // 사용자 정의 데이터 타입
    int u, v, w;
    // source : u 
    // target : v
    // weight : w
};



bool BellmanFord(int n, vector<Edge>& edges, vector<int>& h){
    h.assign(n+1, INF); // distance tracking용



    // tracking distance vector h call by reference
    for(int i = 0; i<n ; ++i){
        for (Edge& e: edges){
            //relaxation
            if (h[e.u] != INF && h[e.u] + e.w < h[e.v]){
                h[e.v] = h[e.u] + e.w;
            }
        }
    }

    //check negative cycle
    for (Edge& e: edges){
        if (h[e.u] != INF && h[e.u] + e.w < h[e.v]){
            return false;
        }

    }
    return true;
}


// single source shortest path
void dijkstra(int n, int src, vector<vector<pair<int, int>>>& adj, vector<int>& dist){
    dist.assign(n, INF); // 실제로 저장되는 simple path distance들

    dist[src] = 0;

    //min_heap : <cost, target>
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});


    while(!pq.empty()){
        auto [d, u] = pq.top();
        pq.pop();


        if(d!= dist[u]) continue; // 이미 본 것과 다르면. 


        for(auto [v, w] : adj[u]){ // O(E) = O(V^2)
            //relaxation
            if (dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v}); // heap : O(logV)
            }
        }
    }
}


void JohnsonsAlgorithm(int n, vector<Edge>& edges){
    vector<vector<int>> dist(n, vector<int>(n, INF)); // 최종 결과 all pair shortest distance matrix
    vector<vector<int>> pred(n, vector<int>(n, -1)); // predecessor matrix
    vector<vector<pair<int, int>>> adj(n); // adjacency matrix(2차원 vector)
    vector<int> h; // new source -> each vertex shortest path tracking



    // 초기화
    for (int i = 0; i<n; i++ ){
        dist[i][i] = 0;
        pred[i][i] = i;
    }


    // add new source s , w(s, v) = 0 for all v
    // 노드 개수는 총 n개여서 n-1 index까지밖에 없음. 그래서 새로운 노드의 인덱스가 n 임.
    for (int i= 0; i<n; i++){
        edges.push_back({n, i, 0});
    }


    // negative cycle check
    if (!BellmanFord(n, edges, h)){
        cout<<"negative cycle"<<endl;
    }
    // 이거 하면서 h : s-> for each vertex shortest path들을 구함.

    //re weighting
    /*
    w^(u, v) = w(u, v) + h(u) - h(v)
    h(u) = sigma(s, u) s--> u simple path shortest path distance*/

    for (Edge& e : edges){
        if (e.u !=n){
            // 아무것도 없는 adj에 넣기. 이때, 노드 n은 빼야함.(새롭게 추가한 노드)
            adj[e.u].emplace_back(e.v, e.w + h[e.u] - h[e.v]);
        }
    }


    // distance update by dijkstra
    for(int u =0; u <n; u++){ // for each vertex as source

        // 이때 쓰는 가중치는 reweight된 것들임. w^(u, v) = w(u, v) + h(u) - h(v)
        dijkstra(n, u, adj, dist[u]);

        // 다시 원래 가중치 값으로 돌려줘야 함. : w(u, v) = w^(u, v)+ h(v)- h(u)
        for (int v= 0; v<n; v++){ // for each vertex
            if(dist[u][v] < INF){
                dist[u][v] += h[v] - h[u];

                // u==v이거나 dist[u][v] ==0이면 u고 , 아닌 경우, 그대로 유지
                pred[u][v] = (u==v || dist[u][v] == 0) ? u: pred[u][v];
            }
        }
    }

    // Print result
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }

}



int main() {
    int n, m; // n : 도시 수, m : 도로 수 (edge)
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = {u - 1, v - 1, w};
    }

    JohnsonsAlgorithm(n, edges);

    return 0;
}