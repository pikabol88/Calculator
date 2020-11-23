#include "operations.h"
#include "expression.h"

char BaseOperation::unary_minus = '_';
char BaseOperation::double_unary_minus[] = { '_','_' };
char BaseOperation::unary_plus = '#';
char BaseOperation::operations[] = { '+','*','/','-','(' };
char BaseOperation::left_bracket = '(';
char BaseOperation::right_bracket = ')';

Operation::Operation(priority_t operationPriority, std::string operationName, bool function) {
    priority = operationPriority;
    name = operationName;
    isFunction = function;
}

priority_t Operation::getPriority() {
    return priority;
}

std::string Operation::getName() {
    return name;
}


//суммирование
Addition::Addition() : Operation(priority::ADD_SUB, "+", false) {}
double Addition::execute(IExpression * left, IExpression * right) {
    double num = (left->calculate() + right->calculate());
    return num;
}

Operation* Addition::getOperation() {

    return new Addition();
}

//минус
Subtraction::Subtraction() : Operation(priority::ADD_SUB, "-", false) {}
double Subtraction::execute(IExpression * left, IExpression * right) {
    double num = (left->calculate() - right->calculate());
    return num;
}
Operation* Subtraction::getOperation() {
    return new Subtraction();
}


//умножить
Multiply::Multiply() : Operation(priority::ADD_SUB, "-", false) {}
double Multiply::execute(IExpression * left, IExpression * right) {
    double num = (left->calculate() - right->calculate());
    return num;
}
Operation* Multiply::getOperation() {
    return new Multiply();
}

//деление
Division::Division() : Operation(priority::ADD_SUB, "-", false) {}
double Division::execute(IExpression * left, IExpression * right) {
    double num = (left->calculate() - right->calculate());
    return num;
}
Operation* Division::getOperation() {
    return new Division();
}

