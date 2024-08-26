from typing import List

'''
Given a string expression of numbers and operators, 
return all possible results from computing all the different possible ways to group numbers and operators. 
You may return the answer in any order.

The test cases are generated such that the output values fit in a 32-bit integer 
and the number of different results does not exceed 104. 

examples
"2-1-1"
((2-1)-1) = 0 
(2-(1-1)) = 2

"2*3-4*5"
(2*(3-(4*5))) = -34 
((2*3)-(4*5)) = -14 
((2*(3-4))*5) = -10 
(2*((3-4)*5)) = -10 
(((2*3)-4)*5) = 10

1. recursion으로 풀기 : 문제를 쪼개가면서 풀기 top down
2. iteration으로 풀기 : bottom up
'''

class Solution:
    def diffWaysToCompute(self, expression: str) -> List[int]:
        # 이미 계산 한 것은 저장하기
       
        # if len(expression) ==1: ## 이건 두자리수는 적용이 안된다.
        if expression.isdigit() : ## 문자가 숫자인지 확인하는 코드
            return [int(expression)]
     

        # 경계를 기준으로 왼쪽 / 오른쪽 나눠서 계산
        ans = []
        for i, s in enumerate(expression):
            if s in ["+", "-","*"]:
                left = self.diffWaysToCompute(expression[:i])
                right = self.diffWaysToCompute(expression[i+1:])

                
                for l in left:
                    for r in right:
                        if s == "+":
                            ans.append(l+r)
                        elif s == "-":
                            ans.append(l-r)
                        else:
                            ans.append(l*r)
        return ans




def main():
    input_string =input("Inputs : ") # "2-1-1"
    # input_string = "2-1-1"
    sol = Solution()
    print(sol.diffWaysToCompute(input_string))


if __name__ == "__main__":
    main()
