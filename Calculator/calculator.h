#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "operations.h"
#include "expression.h"
#include "error.h"
#include "common.h"
#include <Windows.h>
#include <filesystem>


class Calculator {
public:
    std::string str_exp;
    Expression *expression;

    Calculator();
    void processPlugins(std::string path);
    void connectPlugins();
    ~Calculator();

    double runCalculating(std::string str);
    void setExpression(std::string exp);
    void processError();
    std::string UnaryOperationsProcessing(std::string str); 
   
    //BaseOperation baseOperations;
    static std::map<int, std::vector<Operation*>> oper_map;

private:
    std::vector<HMODULE> _libs;
    std::vector<Operation*> plugins;

    std::vector<std::string> valid_operations;
    std::vector<std::string> valid_functions;

    bool isLexemDefined(std::string lexem);
    bool isOperationDefined(std::string lexem);
    bool isFunctionDefined(std::string lexem);

    bool processAlphaError(int *index);
    bool processOperationError(int * index);
};

#endif //CALCULATOR_H