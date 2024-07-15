def evalRPN(tokens):
    """
    :type tokens: List[str]
    :rtype: int
    """
    stack = []
    for token in tokens:
        try:
            stack.append(int(token))
        except:
            op2 = stack.pop()
            op1 = stack.pop()
            if token == "+":
                stack.append(op1+op2)
            elif token == "-":
                stack.append(op1-op2)
            elif token == "*":
                stack.append(op1*op2)
            else:
                stack.append(int(op1/op2))
    return stack.pop()

tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
print(evalRPN(tokens))