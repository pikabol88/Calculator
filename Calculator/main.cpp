#include<iostream>
#include "expression.h"
#include "common.h"
#include <regex>
#include "calculator.h"

int main() {

    std::string str;
    Calculator calculator;
    double result;
    std::cout << "enter the expression:\n";
    while (std::getline(std::cin, str)) {
        
        result = calculator.runCalculating(str);
        if (ErrorState::isSuccess()) {
            std::cout << "answer:\n";
            std::cout << result << "\n\n";           
        }
        else {
            std::cout << ErrorState::getErrorMessage()<<"\n\n";
        }
        std::cout << "enter the expression:\n";
    }

    return 0;
}