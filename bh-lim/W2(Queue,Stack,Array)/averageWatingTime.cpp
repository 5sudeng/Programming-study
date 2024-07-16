#include <iostream>
#include <vector>
#include <iomanip>

double averageWaitingTime(const std::vector<std::vector<int>>& customers) {
    int ntime = customers[0][0];
    std::vector<int> wtime;
    wtime.push_back(customers[0][1]);
    ntime = ntime + customers[0][1];

    for (size_t i = 1; i < customers.size(); ++i) {
        const auto& customer = customers[i];
        if (customer[0] < ntime) {
            wtime.push_back((ntime - customer[0]) + customer[1]);
            ntime += customer[1];
        } else {
            wtime.push_back(customer[1]);
            ntime = customer[0] + customer[1];
        }
    }

    double sum = 0;
    for (int wt : wtime) {
        sum += wt;
    }

    return sum / wtime.size();
}

int main() {
    std::vector<std::vector<int>> customers = {{5, 2}, {5, 4}, {10, 3}, {20, 1}};
    std::cout << std::fixed << std::setprecision(6) << averageWaitingTime(customers) << std::endl;
    return 0;
}