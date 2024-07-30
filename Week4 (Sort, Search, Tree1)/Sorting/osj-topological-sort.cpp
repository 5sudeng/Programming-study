#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n;
// vector<int> inDegree(10);
// vector<vector<int>> a(10);
vector<int> inDegree(10);
vector<vector<int>> a(10);

void topologySort(){
    int result[11];
    queue<int> q;

    // 진입 차수가 0인 노드를 queue에 삽입
    for(int i=1; i<=n; i++){    // i가 각 노드임
        if(inDegree[i]==0){
            q.push(i);
        }
    }
    for(int i=1; i<=n; i++){    // while(q) 같은 역할임
        // n개를 모두 방문하기 전에 queue가 비면 사이클이 발생한 것 -> topological sort는 DAG에서만 성립
        if(q.empty()){
            cout<<"사이클이 발생함"<<endl;
            return;
        }
        int x = q.front();
        q.pop();
        result[i] = x;
        for(int i=0; i<a[x].size(); i++){
            int y = a[x][i];
            inDegree[y]--;
            if(inDegree[y]==0) q.push(y);
        }
    }
    for(int i=1; i<=n; i++){
        cout<<result[i]<<" ";
    }
}

int main(){
    // cout<<inDegree[0]<<endl;
    // cout<<inDegree[1]<<endl;

    // a[0].push_back(3);
    // cout<<a[0][0]<<endl;
    n = 7;
    a[1].push_back(2);
    inDegree[2]++;
    a[1].push_back(5);
    inDegree[5]++;
    a[2].push_back(3);
    inDegree[3]++;
    a[3].push_back(4);
    inDegree[4]++;
    a[4].push_back(6);
    inDegree[6]++;
    a[5].push_back(6);
    inDegree[6]++;
    a[6].push_back(7);
    inDegree[7]++;
    topologySort();

}