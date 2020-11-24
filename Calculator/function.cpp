#include "function.h"
#include "common.h"

Function::Function(std::string str, Operation *oper) {
    operations = oper;
    int i = 0;
    while (isalpha(str[i])) i++;
    addExpression(substr(str, i, str.length() - i), this->expression);
}

double Function::calculate() {   
    double num = operations->execute(expression->calculate(), 0);
    return  (negative) ? num * (-1) : num;
}


