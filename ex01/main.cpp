#include "RPN.hpp"
#include <iostream>

//stack

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./RPN \"expression\"" << std::endl;
        return 1;
    }

    RPNCalculator calculator;

    try {
        int result = calculator.evaluate(argv[1]);
        std::cout << result << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
