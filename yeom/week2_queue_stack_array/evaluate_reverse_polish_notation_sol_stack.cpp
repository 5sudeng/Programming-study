#include <iostream>
#include<string>
#include<vector>
#include<stack>


using namespace std;

//to_string : to string, stoi : string to int
/*
You are given an array of strings tokens that represents an arithmetic expression in a Reverse Polish Notation.
Evaluate the expression. Return an integer that represents the value of the expression.
*/
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        


        stack<int> S;
        for(auto t : tokens){
            


            if(t == "+" || t == "-" || t == "*" || t== "/"){
                int b= S.top();
                S.pop();
                int a =S.top();
                S.pop();

                if(t== "+"){
                    S.push(a+b); 
                }
                else if(t== "-"){
                    S.push(a-b); 
                } 
                else if(t== "*"){
                    S.push(a*b); 
                } 
                else{
                    S.push(a/b); 
                } 
            }
            else{
                S.push(stoi(t));
            }
        
        }
        return S.top();

    }
};

int main()
{
    vector<string> tokens = {"10","6","9","3","+","-11","*","/","*","17","+","5","+"};
    Solution sol;
    cout << sol.evalRPN(tokens)<<endl;
}

