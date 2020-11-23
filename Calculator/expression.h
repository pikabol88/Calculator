#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <math.h>
#include <iostream>
#include <string> 
#include "iexpression.h"


class Expression: public IExpression {
private:
    IExpression* left;
    IExpression* right;

protected:
    std::string operation;
    std::string full;    

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
};

class Number : public  IExpression {
    std::string number;
public:
    Number(std::string num);
    virtual double calculate();
};


#endif //EXPRESSION_H
