#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <string> 
#include<map>
#include<vector>
#include "operations.h"
#include "expression.h"
#include "error.h"
#include "common.h"
#include <string>

class Calculator {
public:
    std::string str_exp;
    Expression *expression;

    Calculator();
    void setExpression(std::string exp);
    void processError();
    double runCalculating();

    BaseOperation baseOperations;
    static std::map<int, std::vector<Operation*>> oper_map;

private:
    std::vector<std::string> valid_operations;
    std::vector<std::string> valid_functions;

    bool isLexemDefined(std::string lexem);
    bool isLexemDefined(char * symbol);
    bool isOperationDefined(std::string lexem);
    bool isFunctionDefined(std::string lexem);


};




#endif //CALCULATOR_H