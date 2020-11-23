#include<iostream>
#include "expression.h"
#include "common.h"
#include <regex>

int main() {

    std::string str;

    while (std::cin >> str) {
        str = UnaryOperationsProcessing(str);
        Expression expression = *new Expression(str);
        double result = expression.calculate();
        std::cout << result<<"\n\n";
    }

    return 0;
}