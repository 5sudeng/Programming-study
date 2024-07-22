#include <iostream>
#include <map>
#include <string>
using namespace std;


class Solution{
    public:
        string intToRoman(int num){
            string ans = "";
            // map<int, string , greater<int>> dictionary; //내림차순 정렬
            map<int, string , greater<int>> dictionary = {{9, "IX"},{10, "X"},{40,"XL"},
                                                            {50,"L"},{90,"XC"},{100,"C"},
                                                            {400,"CD"},{500,"D"},{900,"CM"},
                                                            {1000,"M"}};
            dictionary[1] = "I";
            dictionary.insert({4,"IV"});
            dictionary.insert(make_pair(5, "V"));


            for (std::pair<int, string>pair: dictionary){
                while(num>=pair.first){
                    ans +=pair.second;
                    num-=pair.first;
                }
            }
            return ans;
        }

};


int main(){
    int num = 3749;
    Solution sol;
    cout<<sol.intToRoman(num)<<endl;

    
}