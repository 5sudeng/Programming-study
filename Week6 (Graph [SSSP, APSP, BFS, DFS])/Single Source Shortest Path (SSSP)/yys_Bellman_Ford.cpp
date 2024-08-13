#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <climits>

using namespace std;
void flightRoute(const int n, const int m, const vector<vector<int>> & route_info);

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

   // no graph
   // and priority queueu대신 edge-list활용 -> 모든 edge 순회할 예정이므로.
   // 모든 엣지 돌면서 relaxation : |V|-1 times
   // 마지막에 negative cycle 검사. 



    //Initialize single source : all vertex distance inf
    vector<long long>price(n+1, LLONG_MAX); // source -> 가는 price tracking
    price[1] = 0;
    vector<long long>route_count(n+1, 0); // for counting min-price-routes from source to each vertex
    route_count[1] = 1; 
    vector<int>flights(n+1, INT_MAX); // min num of flights in a min_price route from source to each vertex
    flights[1] = 0;
    vector<int>max_flights(n+1, 0); //// max num of flights in a min_price route from source to each vertex
    max_flights[1] = 0;


    
    // no queueu

    /* 
    Bellmanford : O(VE)*/

    for (int i = 1; i< n-1; ++i) { // for |V|-1 times
        for (const auto& edge : route_info){ // & : by reference : 변수 그 자체 부르기.
            int u = edge[0];
            int v = edge[1];
            long long cost = edge[2];
            //relaxation
            if (price[u] != LLONG_MAX && price[u] + cost < price[v]){
                price[v] = price[u] +cost;
                route_count[v] = route_count[u] % INT_MAX; // 경로 수.

                flights[v] = flights[u] +1; // min_flights
                max_flights[v] = max_flights[u] + 1;

            }
            else if(price[u] != LLONG_MAX && price[u] + cost == price[v]){
                // 같아지는 경우에,  경로 수도 늘어나고, max 비행수도 달라짐.
                route_count[v] = route_count[u] + 1;
                flights[v] = min(flights[v], flights[u] + 1); // 항상 최소 경우의 수를 유지하기 위함.(애초에 초기화를 inf로 했기에 해야함.)
                max_flights[v]  = max(max_flights[v], max_flights[u] + 1);
            }
        }
    }

    // check negative-weight cycles
    for (const auto & edge : route_info){
        int u = edge[0];
        int v = edge[1];
        int cost = edge[2];

        if (price[u]  + cost < price[v]){
            cout<<"Contains a negative cycle"<<endl;
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