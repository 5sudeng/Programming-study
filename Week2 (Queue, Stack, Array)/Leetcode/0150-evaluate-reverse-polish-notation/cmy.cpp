#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <cctype> // isdigit()
#include <cstdlib> // atoi()
#include <algorithm>
using namespace std;

int evalRPN(vector<string>& tokens) {
    map<string, int> opMap = {
        {"+", 1}, {"-", 2}, {"*", 3}, {"/", 4}
    };

    stack<int> st;
    for (auto token : tokens) {
        if (opMap.find(token) == opMap.end()) {
            st.push(stoi(token));
        } else {
            int op2 = st.top(); st.pop();
            int op1 = st.top(); st.pop();
            int result;
            switch(opMap[token]) {
                case 1: result = op1 + op2; break;
                case 2: result = op1 - op2; break;
                case 3: result = op1 * op2; break;
                case 4: result = op1 / op2; break;
            }
            st.push(result);
        }
    }
    return st.top();
}

int main() {
    vector<string> tokens = {"2", "1", "+", "3", "*"};
    cout << evalRPN(tokens) << endl;
}