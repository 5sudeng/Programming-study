from typing import List
def evalRPN(tokens: List[str]) -> int:
    stack = []
    for token in tokens:
        if token not in {"+", "-", "*", "/"}:
            stack.append(int(token))
        else:
            b = stack.pop()
            a = stack.pop()
            if token == "+":
                stack.append(a + b)
            elif token == "-":
                stack.append(a - b)
            elif token == "*":
                stack.append(a * b)
            elif token == "/":
                stack.append(int(a/b))
    return stack[-1]

# Example usage
tokens1 = ["2", "1", "+", "3", "*"]
tokens2 = ["4", "13", "5", "/", "+"]
tokens3 = ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]

print(evalRPN(tokens1))  # Output: 9
print(evalRPN(tokens2))  # Output: 6
print(evalRPN(tokens3))  # Output: 22