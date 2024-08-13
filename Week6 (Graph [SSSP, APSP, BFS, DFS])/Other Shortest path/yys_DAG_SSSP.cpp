#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <climits>
#include<stack>

using namespace std;


//topological order : lambda함수로 정의
void topologicalSortUtil(int v, vector<bool>& visited, stack<int>& Stack, const vector<vector<pair<int, int>>>& graph) {
    //argument : call by reference

    visited[v] = true;
    for(const auto& edge : graph[v]){ // 특정 node 에서 시작하는 topological sorting : O(E)
        int neighbor = edge.first;
        if (!visited[neighbor]){
            topologicalSortUtil(neighbor , visited, Stack, graph);
        }
        
    }
    Stack.push(v); // toplogically sorted
    // top이 제일 predessecor, bottom이 제일 child

}





void flightRoute(const int n, const int m, const vector<vector<int>> & route_info)
{

    //single source shortest path : Dijkstra algorithm
    /*
    /*
    n : number of cities
    m : number of flights
    route_info : {a,b,c}: 
    a : source 
    b : target
    a,b : 1~n
    c : price 
    */

   //DAG Shortest path : O(V+E)
    /* 
    topological order대로 relaxation
    Acyclicity : simple path의  |V|-1를 보장 및 만족
    direction방향과 순서를 toplogical order이 알려줌. -> 이 순서대로 "relaxation"이 "가능했다." : shortest path를 연장해나간다.*/


    //graph
    vector<vector<pair<int, int>>> graph(n + 1); // Use 1-based indexing
    for (const auto& edge : route_info) {
        int u = edge[0];
        int v = edge[1];
        int weight = edge[2];
        graph[u].emplace_back(v, weight);
    }

    //topolocal sorting : O(V+E)
    stack<int>Stack;
    vector<bool> visited(n+1, false);
    for(int i = 1;i<=n; i++){ // O(V)
        if(!visited[i]){
            topologicalSortUtil(i, visited, Stack, graph);
        }
    }






    //Initialize single source : all vertex distance inf
    vector<long long>price(n+1, LLONG_MAX); // source -> 가는 price tracking
    price[1] = 0;
    vector<long long>route_count(n+1, 0); // for counting min-price-routes from source to each vertex
    route_count[1] = 1; 
    vector<int>flights(n+1, INT_MAX); // min num of flights in a min_price route from source to each vertex
    flights[1] = 0;
    vector<int>max_flights(n+1, 0); //// max num of flights in a min_price route from source to each vertex
    max_flights[1] = 0;


    while(!Stack.empty()){ // O(V) // topological order 그대로 인접한 edge에 대해 relaxation
        int u = Stack.top();
        Stack.pop();


        for (const auto& edge : graph[u]){ //O(V+E)
            int v = edge.first; //edge  : pair<int, int>
            int cost = edge.second;

            //relaxation
            if(price[u] + cost < price[v]){
           
                price[v] = price[u] + cost;
                route_count[v] = route_count[u] % INT_MAX;
                flights[v] = flights[u] +1;
                max_flights[v] = max_flights[u] + 1;
            }
            else if (price[u]  + cost == price[v]){
                route_count[v]  = (route_count[v] + route_count[u]) % INT_MAX;
                flights[v] = min(flights[v], flights[u] + 1);
                flights[u] = max(flights[v], max_flights[u] + 1);

            }

        }
    }
  

    std::cout<<price[n]<<" "<<route_count[n]<<" "<<flights[n]<<" "<<max_flights[n];
 
}



int main(){

    vector<vector<int>> my_route;
    my_route.push_back(vector<int>({1,4,5}));
    my_route.push_back(vector<int>({1,2,4}));
    my_route.push_back(vector<int>({2,4,5}));
    my_route.push_back(vector<int>({1,3,2}));
    my_route.push_back(vector<int>({3,4,3}));

    flightRoute(4, 5, my_route);

    return 0;
}