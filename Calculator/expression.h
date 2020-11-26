#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <math.h>
#include <iostream>
#include <string> 
#include "iexpression.h"
#include "operations.h"
#include "common.h"


class Expression: public IExpression {
private:
    IExpression* left;
    IExpression* right;

protected:
    std::string operation;

public:
    Expression();
    Expression(std::string str);

    Expression *getExpression();

    double calculate();
    ~Expression();
    
protected:
    void processExpression(std::string str, int index);
    void addExpression(std::string str, IExpression *&place);

private:
    void parseExpression(const std::string str);
    void processPower(const std::string str, bool * isActivated);
    void processSecondPriorityOperations(const std::string str, bool * isActivated);
    void processFirstPriorityOperations(const std::string str, bool * isActivated);
    void processBrackets(const std::string str, bool * isActivated);
    Operation* defineTrigonometry(std::string str);
    Operation * defineConstant(std::string str);
};


#endif //EXPRESSION_H
