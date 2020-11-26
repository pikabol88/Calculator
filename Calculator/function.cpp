#include "function.h"

Function::Function(std::string str, Operation *fun) {
    operations = fun;
    int i = 0;
    while (isalpha(str[i])) i++;
    addExpression(substring(str, i, str.length() - i), this->expression);
}

double Function::calculate() {   
    double num = operations->execute(expression->calculate(), 0);
    return  (negative) ? num * (-1) : num;
}

Constant::Constant(Operation * constant) {
    operations = constant;
}

double Constant::calculate() {
    double num = operations->execute(0, 0);
    return (negative) ? num * (-1) : num;
}
