#include <iostream>
#include <vector>

std::vector<int> merge(std::vector<int> left, std::vector<int> right) {
    std::vector<int> merged;
    int i = 0, j = 0;

    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            merged.push_back(left[i]);
            i++;
        } else {
            merged.push_back(right[j]);
            j++;
        }
    }

    while (i < left.size()) {
        merged.push_back(left[i]);
        i++;
    }

    while (j < right.size()) {
        merged.push_back(right[j]);
        j++;
    }

    return merged;
}

std::vector<int> merge_sort(std::vector<int> data) {
    if (data.size() <= 1) {
        return data;
    }

    int middle = data.size() / 2;
    std::vector<int> left(data.begin(), data.begin() + middle);
    std::vector<int> right(data.begin() + middle, data.end());

    left = merge_sort(left);
    right = merge_sort(right);

    return merge(left, right);
}

int main() {
    std::vector<int> data = {3, 6, 7, 1, 2, 4, 8, 5};

    std::vector<int> sorted_data = merge_sort(data);

    for (int i = 0; i < sorted_data.size(); i++) {
        std::cout << sorted_data[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}