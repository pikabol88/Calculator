#ifndef TRIGONOMETRY_H
#define TRIGONOMETRY_H

#include <iostream>
#include <string> 
#include "expression.h"
#include "operations.h"

class Function : public Expression {   
public:
    IExpression* expression;
    Function(std::string str, Operation *fun);
    double calculate();
};

class Constant : public Expression {
public:
    Constant(Operation *constant);
    double calculate();
};

#endif //TRIGONOMETRY_H