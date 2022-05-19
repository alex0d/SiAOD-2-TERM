#include <iostream>
#include <string>
#include <cmath>
#include "Stack.h"

int evaluatePostfixExpression(const std::string& expr) {
    // Стек для хранения операндов.
    Stack stack = Stack();

    for (char elem : expr) {
        if (std::isdigit(elem)) {
            stack.push(elem - '0');
        }
        else {
            int rightOperand = stack.pop();
            int leftOperand = stack.pop();

            switch (elem) {
                case '+':
                    stack.push(leftOperand + rightOperand);
                    break;

                case '-':
                    stack.push(leftOperand - rightOperand);
                    break;

                case '*':
                    stack.push(leftOperand * rightOperand);
                    break;

                case '/':
                    stack.push(leftOperand / rightOperand);
                    break;

                case '^':
                    stack.push(pow(leftOperand, rightOperand));
                    break;
            }
        }
    }
    return stack.pop();
}

int main() {
    std::string expr;
    while (true) {
        std::cout << "Введите выражение в постфиксной форме БЕЗ пробела (0 для выхода): ";
        std::cin >> expr;
        if (expr == "0") {
            break;
        }
        std::cout << "Ответ: " << evaluatePostfixExpression(expr) << std::endl;
    }
    return 0;
}
