#include <iostream>
#include <vector>
using namespace std;

double averageWaitingTime(vector<vector<int>>& customers) {
    int now = 0;
    double wait = 0;
    for (auto customer : customers) {
        if (customer[0] < now) {
            now += customer[1];
            wait += (now - customer[0]);
        } else {
            now = customer[0] + customer[1];
            wait += customer[1];
        }
    }
    return wait/customers.size();
}
