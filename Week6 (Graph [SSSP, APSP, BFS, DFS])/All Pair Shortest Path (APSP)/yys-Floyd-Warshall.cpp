#include <iostream>
#include <vector>
#include <limits>



using namespace std;

const int INF = numeric_limits<int>::max();



void printPath(vector<vector<int>>& pred, int i, int j){
    // pred : 2차원 vector
    //pred[i][j] : i-> j로 가는 바로 직전 predecessor의 인덱스


    if (i =j){
        cout<<i+1 <<" " ;

    }
    else if(pred[i][j] == -1){
        cout<<"no path";

    }
    else{
        printPath(pred, i, pred[i][j]);
        cout<<j+1<< " ";
    }
    
}

// also dynamic programming : O(V^3)
void floydWarshall(int n, vector<vector<int>> & dist, vector<vector<int>>& pred){

    for (int k = 0; k<n; k++){ // d_ij^(k) : k번째 iteration을 통해 얻은 {1...k} intermediate set을 통해 얻은 weight of a shortest path i-> j
        for (int i =0; i<n ; i++){
            for (int j =0; j<n ; j++){

                if (dist[i][k] !=INF && dist[k][j] !=INF && dist[i][k] + dist[k][j] < dist[i][j]){
                    dist[i][j] = dist[i][k] + dist[k][j]; // dist 행렬은 intermediate set {1...k}을 확장해나가면서 만든다.
                    // dist[i][j] update 횟수 : k번
                    //dist[i][j] = : k-1번째의 d_ij
                    // dist[i][k] : k-1의 dist_ik

                    pred[i][j] = pred[k][j];
                }
                // 이게  else면 dist[i][j]는 그대로 유지된다.

            }
        }

    }
}



// 대각성분의 부호를 보고 음수 사이클 여부를 관찰함.
// 가능한 이유: 
// dist[i][k] + dist[k][j] < dist[i][j]
/* 
d[i][i]는 0으로 처음에 초기화를 했었는데, j =i인 경우
즉, dist[i][k] + dist[k][i] < dist[i][i]에 걸려서 dist[i][i]가 업데이트가 된다는 것은
다른 노드 k를 찍고 다시 i로 돌아오는 "사이클" 에서 더 작아지게 하는 음수 사이클이 있었다는 것..*/
bool hasNegativeCycle(int n, const vector<vector<int>>& dist) {
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) {
            return true;
        }
    }
    return false;
}


/* 
주어진 도시 네트워크에는 여러 도시와 그들 사이의 도로가 있습니다. 
각 도로는 두 도시를 연결하며, 해당 도로를 통과하는 데 필요한 비용(시간 또는 거리)이 주어집니다. 
당신은 이 네트워크에서 각 도시 쌍 사이의 최소 비용을 계산하고자 합니다.
*/

int main() {
    int n, m; // n : 도시 수, m : 도로 수 (edge)
    cin >> n >> m;


    //초기화
    vector<vector<int>> dist(n, vector<int>(n, INF));
    vector<vector<int>> pred(n, vector<int>(n, -1));
    
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        pred[i][i] = i;
    }

    //dist : 초기 weights, 있는 것을 제외하고 edge가 없는 경우는 INF로 
    //pred : -1로 초기하고, 자기 자신에게 가는 경로는 자기 자신을 가리키도록
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dist[u - 1][v - 1] = w;
        pred[u - 1][v - 1] = u - 1; // 
    }

    floydWarshall(n, dist, pred);


    // 결과 print out
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

    cout << "Paths:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                cout << "Path from " << i + 1 << " to " << j + 1 << ": ";
                if (dist[i][j] == INF) {
                    cout << "No path" << endl;
                } else {
                    printPath(pred, i, j);
                    cout << endl;
                }
            }
        }
    }

    return 0;
}
