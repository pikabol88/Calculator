#include "function.h"

Function::Function(std::string str, Operation *fun) {
    base_operations = fun;
    int i = 0;
    while (isalpha(str[i])) i++;
    addExpression(substring(str, i, str.length() - i), this->expression);
}

double Function::calculate() {   
    double num = base_operations->execute(expression->calculate(), 0);
    return  (negative) ? num * (-1) : num;
}

Constant::Constant(Operation * constant) {
    base_operations = constant;
}

double Constant::calculate() {
    double num = base_operations->execute(0, 0);
    return (negative) ? num * (-1) : num;
}
