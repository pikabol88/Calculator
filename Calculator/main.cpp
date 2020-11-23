#include<iostream>
#include "expression.h"
#include "common.h"
#include <regex>
#include "calculator.h"

int main() {

    std::string str;
    Calculator calculator;
    while (std::cin >> str) {
        str = UnaryOperationsProcessing(str);
        calculator.setExpression(str);
        calculator.runCalculating();
        /*
        Expression expression = *new Expression(str);
        double result = expression.calculate();*/
        double result = calculator.runCalculating();
        std::cout << result<<"\n\n";
    }

    return 0;
}