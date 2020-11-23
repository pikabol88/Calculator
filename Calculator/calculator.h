#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <math.h>
#include <iostream>
#include <string> 
#include<regex>
#include<map>
#include<vector>
#include "operations.h"

class Calculator {
public:
    Calculator();
    void setExpression();
    double runCalculating();
private:
    BaseOperation baseOperations;
    std::map<int, std::vector<Operation*>> operations;
};




#endif //CALCULATOR_H