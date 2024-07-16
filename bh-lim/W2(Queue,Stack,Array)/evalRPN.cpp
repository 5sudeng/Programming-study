#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

int evalRPN(vector<string>& tokens) {
    stack<int> stack;
    for (const string& token : tokens) {
        if (token != "+" && token != "-" && token != "*" && token != "/") {
            stack.push(stoi(token));
        }
        else {
            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();
            if (token == "+") {
                stack.push(a + b);
            } else if (token == "-") {
                stack.push(a - b);
            } else if (token == "*") {
                stack.push(a * b);
            } else if (token == "/") {
                stack.push(a / b);
            }
        }
    }
    return stack.top();
}

int main() {
    vector<string> tokens1 = {"2", "1", "+", "3", "*"};
    vector<string> tokens2 = {"4", "13", "5", "/", "+"};
    vector<string> tokens3 = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};

    cout << evalRPN(tokens1) << endl;  // Output: 9
    cout << evalRPN(tokens2) << endl;  // Output: 6
    cout << evalRPN(tokens3) << endl;  // Output: 22

    return 0;
}