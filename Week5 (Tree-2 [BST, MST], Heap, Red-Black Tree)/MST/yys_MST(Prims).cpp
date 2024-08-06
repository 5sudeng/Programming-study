#include <iostream> 
#include <queue>
#include <vector>

#include "functions.hpp"

using namespace std; 

int minDistance(vector<vector<int>>& points) {


    /*/
    prim's algorithm (Greedy algorithm) : O(ElogV)
    그래프의 형태 : 특정 점에서 모든 점들을 연결해서 가장 최소 거리들만 선택
    priority queue의 역할 : 
    */
    int num = points.size();

    int distance = 0;
    int count =0;
    //marked vector
    vector<bool> marked(num, 0); // 0~ n-1 all points

    //priority queue for ligth edge
    // priority_queue< 저장할 내용, 저장 방식, pq 작동 방식 :  max heap(default) or min heap>
    //여기서는 최소먼저니까 min heap
    //저장 내용 : <cost, vertex>
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> PQ;
    PQ.push({0, 0});// first node
    
    while(count < num ){// until all connected
  
        //get min
        int cost = PQ.top().first; // 여기서 cost순으로 나오게 된다.(greedy)
        int i = PQ.top().second;
        PQ.pop();
        //
        if (marked[i]){
            continue; // skip this. vertex
        }
        marked[i] = true;
        distance += cost;   
        ++count;
        //vertex i
        
        //현재 node에서 각 점에 대한 distance(cost) 계산
        for (int k =0; k < num; ++k){ // for other all vertecies 0~n-1 : 이미 들어간 것도 중복 될 가능성 있음.
            //distance for not visited
            if (!marked[k]){
                int d = (abs(points[i][0] - points[k][0]) + abs(points[i][1] - points[k][1]));
                PQ.push({d,k});
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