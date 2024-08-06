#include <iostream>
#include <vector>
#include <algorithm>

///////////////////////////////////////////
// Kruskal's Algorithm w/ set operations //
///////////////////////////////////////////


using namespace std;

// 1. Edge 정의
class Edge {
public:
    int src, dst, weight;

    //src, dst, weight라는 세 개의 멤버 변수를 초기화
    Edge(int src, int dst, int weight) : src(src), dst(dst), weight(weight) {}

    /*혹은
    Edge(int src, int dst, int weight) {
        this->src = src;     // this->src는 멤버 변수, src는 매개변수
        this->dst = dst;     // this->dst는 멤버 변수, dst는 매개변수
        this->weight = weight; // this->weight는 멤버 변수, weight는 매개변수
    }
    */
};

//2. find-set
//v가 속한 집합의 대표 요소 찾기
// vertices 벡터는 각 정점의 부모 저장하는 배열
//v의 부모를 재귀적으로 찾아서 최종적 루트 노드 찾기. 그리고 찾은 루트노드를 v의 부모로 설정
int Find(vector<int>& vertices, int v) {
    if (v == vertices[v]) {
        return v;
    } else {
        return vertices[v] = Find(vertices, vertices[v]);
    }
}

// 3. Union 함수
void Union(vector<int>& vertices, int a, int b) {
    a = Find(vertices, a);
    b = Find(vertices, b);

    // b로 통합
    if (a != b) {
        vertices[a] = b;
    }
}


//랭크 기반병합: 트리의 높이를 최소화하기 위해 더 낮은 랭크의 트리를 더 높은 랭크의 트리에 병합
// void Union(vector<int>& parent, vector<int>& rank, int u, int v) {
//     int rootU = Find(parent, u);
//     int rootV = Find(parent, v);
//     if (rootU != rootV) {
//         if (rank[rootU] < rank[rootV]) {
//             parent[rootU] = rootV;
//         } else if (rank[rootU] > rank[rootV]) {
//             parent[rootV] = rootU;
//         } else {
//             parent[rootV] = rootU;
//             rank[rootU]++;
//         }
//     }
// }

vector<Edge> MSTKruskal(vector<int>& vertices, vector<Edge>& edges) {
    vector<Edge> mst;

    //edge를 가중치로 오름차순 정렬
    //a와 b를 받아서, a의 weight이 b의 weight보다 작으면 true임을 기준으로 edges의 처음부터 끝까지 오름차순 정렬
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });
    
    //랭크 활용시
    // vector<int> rank(vertices.size(), 0);

    // edge를 하나씩 확인하기
    for (const Edge& edge : edges) {
        int set1 = Find(vertices, edge.src);
        int set2 = Find(vertices, edge.dst);

        // 두 정점이 다른 집합에 속하면 MST에 추가하고 집합 병합
        if (set1 != set2) {
            mst.push_back(edge);
            Union(vertices, set1, set2);
        }
    }

    return mst;
}


int main() {
    int V = 9, E = 14;
    vector<int> vertices;
    vector<Edge> edges;
    
    for (int i=0; i<V; i++) {
        vertices.push_back(i);
    }
    /*혹은,
    vector<int> vertices(V);  
    for (int i = 0; i < V; i++) {
        vertices[i] = i;
    }
    */
    // 0 1 2 3 4 5 6 7 8

    edges.push_back(Edge(0, 1, 4));
    edges.push_back(Edge(0, 7, 8));
    edges.push_back(Edge(1, 2, 8));
    edges.push_back(Edge(1, 7, 11));
    edges.push_back(Edge(2, 3, 7));
    edges.push_back(Edge(2, 5, 4));
    edges.push_back(Edge(2, 8, 2));
    edges.push_back(Edge(3, 4, 9));
    edges.push_back(Edge(3, 5, 14));
    edges.push_back(Edge(4, 5, 10));
    edges.push_back(Edge(5, 6, 2));
    edges.push_back(Edge(6, 7, 1));
    edges.push_back(Edge(6, 8, 6));
    edges.push_back(Edge(7, 8, 7));

    vector<Edge> mst = MSTKruskal(vertices, edges);

    int totalWeight = 0;
    cout << "MST by Kruskal's Algorithm:" << endl;
    for (const Edge& edge : mst) {
        cout << "Edge: " << edge.src << " - " << edge.dst << ", Weight: " << edge.weight << endl;
        totalWeight += edge.weight;
    }

    cout << "Total Weight of MST: " << totalWeight << endl;

    return 0;
}