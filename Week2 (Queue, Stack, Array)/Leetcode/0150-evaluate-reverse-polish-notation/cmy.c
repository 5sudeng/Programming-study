#include <stdio.h>
#include <stdbool.h> // to use bool type
#include <ctype.h> // isdigit()
#include <stdlib.h> // atoi()

int evalRPN(char** tokens, int tokensSize) {
    int stack[tokensSize];
    int top = -1;
    for (int i=0; i<tokensSize; i++) {
        char* token = tokens[i];
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            stack[++top] = atoi(token);
        } else {
            int op2 = stack[top--];
            int op1 = stack[top--];
            switch (token[0]) {
                case '+': stack[++top] = op1 + op2; break;
                case '-': stack[++top] = op1 - op2; break;
                case '*': stack[++top] = op1 * op2; break;
                case '/': stack[++top] = op1 / op2; break;
            }
        }
    }
    return stack[top];
}

int main() {
    char* tokens[] = {"4", "13", "5", "/", "+"};
    printf("%d", evalRPN(tokens, 5));
    return 0;
}