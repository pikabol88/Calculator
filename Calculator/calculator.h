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

    double runCalculating(std::string &str);    
    static std::map<int, std::vector<Operation*>> operations_map;

private:

    typedef enum symbol {
        DIGIT,
        FLOAT_POINT,
        ALPHA,
        BRACKET,
        RIGHT_BRACKET,
        LEFT_BRACKET,
        NULLIC,
        OPERATION,
    }symbol_t;

    std::vector<HMODULE> dll_libs;
    std::vector<Operation*> plugins;

    std::vector<std::string> valid_operations;
    std::vector<std::string> valid_functions;

    void processPlugins(std::string const & path);
    void connectPlugins();

    void setExpression(std::string const & exp);

    bool processExpressionBeg();
    bool processPointError(symbol_t * previos, const int index);
    void processError();
    bool processAlphaError(int *index);
    bool processOperationError(int * index);
    bool isLexemDefined(std::string const & lexem);
    bool isOperationDefined(std::string const & lexem);
    bool isOperationUnaryMinus(std::string const & lexem);
    bool isFunctionDefined(std::string const & lexem);

    std::string unaryOperationsProcessing(std::string &str);
    
};

#endif //CALCULATOR_H