#ifndef TRIGONOMETRY_H
#define TRIGONOMETRY_H
#include <cmath>
#include <iostream>
#include <string> 
#include "expression.h"

class TrigonometryOperation {
public:
    static std::string sinus;
    static std::string cosine;
    static std::string tangent;
    static std::string cotangent;
};


class Function : public Expression {   
public:
    IExpression* expression;

    Function(std::string str, std::string func);

    double calculate();
};

#endif //TRIGONOMETRY_H