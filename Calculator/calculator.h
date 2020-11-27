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
    ~Calculator();   

    double runCalculating(std::string str);      
    static std::map<int, std::vector<Operation*>> operations_map;

private:
    std::vector<HMODULE> dll_libs;
    std::vector<Operation*> plugins;

    std::vector<std::string> valid_operations;
    std::vector<std::string> valid_functions;

    void processPlugins(std::string path);
    void connectPlugins();

    bool isLexemDefined(std::string lexem);
    bool isOperationDefined(std::string lexem);
    bool isOperationUnaryMinus(std::string lexem);
    bool isFunctionDefined(std::string lexem);

    void processError();
    bool processAlphaError(int *index);
    bool processOperationError(int * index);
    void setExpression(std::string exp);
    std::string unaryOperationsProcessing(std::string str);
    
};

#endif //CALCULATOR_H