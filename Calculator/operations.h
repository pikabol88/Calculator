#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <math.h>
#include <iostream>
#include <string> 
#include <regex>
#include "iexpression.h"

 enum Priority {
    CONSTANT,
    ADD_SUB,
    MUL_DIV,
    POWER,
    FUNCTION,
} ;

class Operation {
protected:
    Priority prior;
    std::string name;

public: 
   // Operation(Priority operationPriority, std::string operationName);
    Operation(Priority const & operationPriority, std::string const & operationName);
    Priority getPriority();
    std::string getName();
    virtual Operation* getOperation() = 0;
    virtual double execute(double left, double right) = 0;
};

class BaseOperation {
public:
    static char unary_minus;
    static char double_unary_minus[];
    static char unary_plus;
    static char base_operations[];
    static char right_bracket;
    static char left_bracket;

};

#endif //OPERATIONS_H