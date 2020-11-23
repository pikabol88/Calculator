#ifndef OPERATIONS_H
#define OPERATIONS_H
#include <math.h>
#include <iostream>
#include <string> 
#include<regex>
#include "iexpression.h"

typedef enum priority {
    CONSTANT,
    ADD_SUB,
    MUL_DIV,
    POWER,
    FUNCTION,
} priority_t;


class Operation {
protected:
    priority_t priority;
    std::string name;
    bool isFunction;

public: 
    Operation(priority_t operationPriority, std::string operationName, bool isFunction);
    priority_t getPriority();
    std::string getName();
    virtual Operation* getOperation() = 0;
    virtual double execute(IExpression *left, IExpression *right) = 0;
};



class Addition: public Operation {
public:
    Addition();
    virtual Operation *getOperation();
    virtual double execute(IExpression *left, IExpression *right);
};

class Subtraction : public Operation {
public:
    Subtraction();
    virtual Operation *getOperation();
    virtual double execute(IExpression *left, IExpression *right);
};

class Multiply : public Operation {
public:
    Multiply();
    virtual Operation *getOperation();
    virtual double execute(IExpression *left, IExpression *right);
};

class Division : public Operation {
public:
    Division();
    virtual Operation *getOperation();
    virtual double execute(IExpression *left, IExpression *right);
};








class BaseOperation {
public:
    static char unary_minus;
    static char double_unary_minus[];
    static char unary_plus;
    static char operations[];
    static char right_bracket;
    static char left_bracket;

};




#endif //OPERATIONS_H