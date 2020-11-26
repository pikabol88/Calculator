#include "operations.h"
#include "expression.h"

char BaseOperation::unary_minus = '_';
char BaseOperation::double_unary_minus[] = { '_','_' };
char BaseOperation::unary_plus = '#';
char BaseOperation::operations[] = { '+','*','/','-','(' ,')'};
char BaseOperation::left_bracket = '(';
char BaseOperation::right_bracket = ')';

Operation::Operation()
{
}

Operation::Operation(Priority operationPriority, std::string operationName) {
    prior = operationPriority;
    name = operationName;
}

Priority Operation::getPriority() {
    return prior;
}

std::string Operation::getName() {
    return name;
}

//суммирование
Addition::Addition() : Operation(Priority::ADD_SUB, "+") {}
double Addition::execute(double left, double right) {
    double num = (left + right);
    return num;
}

Operation* Addition::getOperation() {

    return new Addition();
}

//минус
Subtraction::Subtraction() : Operation(Priority::ADD_SUB, "-") {}
double Subtraction::execute(double left, double right) {
    double num = (left - right);
    return num;
}
Operation* Subtraction::getOperation() {
    return new Subtraction();
}


//деление
Division::Division() : Operation(Priority::ADD_SUB, "/") {}
double Division::execute(double left, double right) {
    double num = (left / right);
    return num;
}
Operation* Division::getOperation() {
    return new Division();
}

//синус
Sinus::Sinus() : Operation(Priority::FUNCTION, "sin") {}
double Sinus::execute(double left, double right) {
    double num = sin(left);
    return num;
}
Operation* Sinus::getOperation() {
    return new Sinus();
}

//пи
Pi::Pi() : Operation(Priority::CONSTANT, "pi") {}
double Pi::execute(double left, double right) {
    double num = 2*asin(1);
    return num;
}
Operation* Pi::getOperation() {
    return new Pi();
}

