#ifndef RPNCALCULATOR_HPP
#define RPNCALCULATOR_HPP

#include <string>

class RPNCalculator {
public:
    RPNCalculator();
    int evaluate(const std::string& expression);
private:
    bool isOperator(const std::string& token) const;
    int performOperation(const std::string& operation, int operand1, int operand2) const;
};

#endif
