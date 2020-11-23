#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <string> 
#include<map>
#include<vector>
#include "operations.h"
#include "expression.h"

class Calculator {
public:
    std::string str_exp;
    Expression *expression;

    Calculator();
    void setExpression(std::string exp);
    double runCalculating();

    BaseOperation baseOperations;
    static std::map<int, std::vector<Operation*>> oper_map;

};




#endif //CALCULATOR_H