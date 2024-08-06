#include <iostream> 
#include <queue>
#include <vector>
#include <tuple>

#include "functions.hpp"

using namespace std; 


// find-set(x)함수 : i를 포함하는 set을 찾는 것. -> 없다면 만들도록, 아니면 기존에 set에 union할지를 결정.
// cylce 방지용임. 대표가 같다는 것은 cycle이 생긴다는 것이니까 이를 방지하기 위함.
int find(vector<int>&parent, int i){
    //parent : 각 set의 대표를 알려주는 vector

    if (parent[i] !=i){
        parent[i] = find(parent, parent[i]); // i가 해당 set의 대표가 아니라면 해당 set의 대표를 따로 찾아라.
    }
    return parent[i]; // if parent[i] = i
}

void unionSets(vector<int>& parent, vector<int>& rank, int x, int y){ 
    //parent 즉 각 set의 정보를 업데이트하는데 필요한 함수. 
    // 트리 높이가 큰 것에 병합하게 하여, 트리의 높이를 최소를 유지한다.
    // 큰 쪽으로 root를 반영하는 것을 보면, 이미 큰 트리의 정보는 변경을 안하는 것.(find의 연산을 최소화 하려고.)

    int rootX = find(parent, x);
    int rootY = find(parent , y);

    if(rootX != rootY){
        if (rank[rootX]> rank[rootY]){
            parent[rootY] = rootX; // X로 병합.
        }
        else if (rank[rootX] < rank[rootY]){
            parent[rootX] = rootY;
        }
        else{
            parent[rootY] = rootX;
            rank[rootX] ++; // 크기가 같은 set 만났을 때, 확장.
        }
    }
}

int minDistance(vector<vector<int>>& points) {


    /* 
    Kuskal algorithm : O(ElogV)
    -> 모든 노드를 가진채로 set을 합쳐가면서 확장해나감.
    -> using sorted adjacency list
    -> edge 위주로 작은 것부터 하나씩 검토하면서 set에 확장해나가는데, 이미 같은 set인지 여부를 따져가면서. 
    -> Also Greedy algorithm
    -> sorting 후, 매번 포함되지 않은 edge 에 대해 samllest edge를 선택함.*/


    int num = points.size(); // 점의 개수

    // 모든 가능한 모든 edge를 검사할 것이기에 모두 만든다.
    //(cost, point1, point2)
    //edge-list인데, 완전 dense한 그래프임.
    vector<tuple<int,int, int>>edges; // {cost_ij, i, j}
    for (int i = 0; i <num; ++i){
        for (int j= i+1; j<num; ++j){ // make only upper triangle
            int cost = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
            edges.push_back({cost, i, j});
        }
    }
    sort(edges.begin(), edges.end()); //sorting edges(오름차순) // 원래는 adjacency list & priority queue를 사용하긴함.


    //union-find set up
    vector<int>parent(num); //  각 원소가 속한 집합으로 초기에는 자기 자신 -> find로 자기가 속한 집단의 대표를 찾는다.
    vector<int>rank(num, 0); // 트리의 높이를 추적, 트리의 높이를 기준으로 작은 트리를 더 큰 트리 아래에 병합, 결국 union set할때, 양쪽 중, 어디쪽으로 병합할지를 결정지어주는 역할.


    /*
    초기화 부분 : 
    1. parent : 모두 자기 자신. 일단 모든 set의 대표는 자기 자신
    2. distance =0
    3. 연결 edge 수 : 0 -> num-1까지 확장.
    */
    for (int i = 0; i<num; ++i){
        parent[i] = i;
    }

    int distance=0; 
    int edgesUsed = 0; // Tree니까 num-1까지임., 즉 set의 크기가 전체로 확장될때까지. 아니면 무한 반복 가능.(dense graph라서)


    //오름차순으로 edge반환해서 검사 -> greedy
    for(const auto& edge: edges){
        int cost = std::get<0>(edge); // tuple에서 성분 가져오기.
        int u = std::get<1>(edge);
        int v = std::get<2>(edge);


        if (find(parent, u) != find(parent,v)){
            unionSets(parent, rank, u, v);
            distance += cost;
            edgesUsed ++;
            if (edgesUsed == num-1){ // 이거 안하면 계속 함.(edge 수가 num-1이 아니라서.)
                break;
            }
        }
    }

    
    return distance;
}


int main() 
{ 
    vector<vector<int>> points;
    points.push_back(vector<int>({3,12}));
    points.push_back(vector<int>({-2,5}));
    points.push_back(vector<int>({-4,1}));

    cout << minDistance(points) << endl; 

    return 0; 
} 