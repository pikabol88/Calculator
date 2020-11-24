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


//������������
Addition::Addition() : Operation(priority::ADD_SUB, "+", false) {}
double Addition::execute(double left, double right) {
    double num = (left + right);
    return num;
}

Operation* Addition::getOperation() {

    return new Addition();
}

//�����
Subtraction::Subtraction() : Operation(priority::ADD_SUB, "-", false) {}
double Subtraction::execute(double left, double right) {
    double num = (left - right);
    return num;
}
Operation* Subtraction::getOperation() {
    return new Subtraction();
}


//��������
Multiply::Multiply() : Operation(priority::ADD_SUB, "*", false) {}
double Multiply::execute(double left, double right) {
    double num = (left*  right);
    return num;
}
Operation* Multiply::getOperation() {
    return new Multiply();
}

//�������
Division::Division() : Operation(priority::ADD_SUB, "/", false) {}
double Division::execute(double left, double right) {
    double num = (left / right);
    return num;
}
Operation* Division::getOperation() {
    return new Division();
}

//�������
Power::Power() : Operation(priority::POWER, "^", false) {}
double Power::execute(double left, double right) {
    double num = pow(left, right);
    return num;
}
Operation* Power::getOperation() {
    return new Power();
}

//�������
Cosine::Cosine() : Operation(priority::FUNCTION, "cos", false) {}
double Cosine::execute(double left, double right) {
    double num = cos(left);
    return num;
}
Operation* Cosine::getOperation() {
    return new Cosine();
}

//�����
Sinus::Sinus() : Operation(priority::FUNCTION, "sin", false) {}
double Sinus::execute(double left, double right) {
    double num = sin(left);
    return num;
}
Operation* Sinus::getOperation() {
    return new Sinus();
}

