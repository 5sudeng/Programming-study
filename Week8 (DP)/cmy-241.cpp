#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:

    int calc(int a, int b, char op) {
        if (op == '+') { return a+b; }
        else if (op == '-') { return a-b; }
        else if (op == '*') { return a*b; }
        else { return 0; }
    }

    vector<int> diffWaysToCompute(string expression) {
        vector<int> ans;

        for (int i=0; i<expression.size(); ++i) {
            char c = expression[i];

            if (c=='+' || c=='-' || c=='*') {
                vector<int> left = diffWaysToCompute(expression.substr(0, i));
                vector<int> right = diffWaysToCompute(expression.substr(i+1));

                for (auto l : left) {
                    for (auto r : right) {
                        ans.push_back(calc(l, r, c));
                    }
                }
            }
        }

        if (ans.empty()) { ans.push_back(stoi(expression)); }
        return ans;
    }
};


int main() {
    Solution solution;

    // Test case 1
    string expression1 = "2-1-1";
    vector<int> result1 = solution.diffWaysToCompute(expression1);
    cout << "Results for expression \"" << expression1 << "\":" << endl;
    for (int r : result1) {
        cout << r << " ";
    }
    cout << endl;

    // Test case 2
    string expression2 = "2*3-4*5";
    vector<int> result2 = solution.diffWaysToCompute(expression2);
    cout << "Results for expression \"" << expression2 << "\":" << endl;
    for (int r : result2) {
        cout << r << " ";
    }
    cout << endl;

    // Additional test cases
    string expression3 = "10+5-3*2";
    vector<int> result3 = solution.diffWaysToCompute(expression3);
    cout << "Results for expression \"" << expression3 << "\":" << endl;
    for (int r : result3) {
        cout << r << " ";
    }
    cout << endl;

    return 0;
}