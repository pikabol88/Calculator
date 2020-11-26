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
    Operation(Priority operationPriority, std::string operationName);
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

class Addition: public Operation {
public:
    Addition();
    virtual Operation *getOperation();
    virtual double execute(double left, double right);
};

class Subtraction : public Operation {
public:
    Subtraction();
    virtual Operation *getOperation();
    virtual double execute(double left, double right);
};

class Division : public Operation {
public:
    Division();
    virtual Operation *getOperation();
    virtual double execute(double left, double right);
};

class Sinus : public Operation {
public:
    Sinus();
    virtual Operation *getOperation();
    virtual double execute(double left, double right);
};

class Pi : public Operation {
public:
    Pi();
    virtual Operation *getOperation();
    virtual double execute(double left, double right);
};

#endif //OPERATIONS_H