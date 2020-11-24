#ifndef TRIGONOMETRY_H
#define TRIGONOMETRY_H
#include <cmath>
#include <iostream>
#include <string> 
#include "expression.h"
#include "operations.h"

class Function : public Expression {   
public:
    IExpression* expression;
    Function(std::string str, Operation *oper);
    double calculate();
};

#endif //TRIGONOMETRY_H