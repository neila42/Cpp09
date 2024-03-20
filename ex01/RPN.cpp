#include "RPN.hpp"
#include <stack>
#include <sstream>
#include <cstdlib>

RPNCalculator::RPNCalculator() {}

bool RPNCalculator::isOperator(const std::string& token) const {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

int RPNCalculator::performOperation(const std::string& operation, int operand1, int operand2) const {
    if (operation == "+") return operand1 + operand2;
    if (operation == "-") return operand1 - operand2;
    if (operation == "*") return operand1 * operand2;
    if (operation == "/") return operand1 / operand2; // Assume operand2 is not 0 for simplicity
    return 0;
}

int RPNCalculator::evaluate(const std::string& expression) {
    std::istringstream tokens(expression);
    std::string token;
    std::stack<int> s;

    while (tokens >> token) {
        if (isdigit(token[0])) {
            s.push(atoi(token.c_str()));
        } else if (isOperator(token)) {
            if (s.size() < 2) throw std::runtime_error("Error: insufficient operands");
            int op2 = s.top(); s.pop();
            int op1 = s.top(); s.pop();
            s.push(performOperation(token, op1, op2));
        } else {
            throw std::runtime_error("Error: invalid token");
        }
    }

    if (s.size() != 1) throw std::runtime_error("Error: invalid expression");
    return s.top();
}
