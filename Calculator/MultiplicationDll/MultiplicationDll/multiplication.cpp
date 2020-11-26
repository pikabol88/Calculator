#include "multiplication.h"

Multiply::Multiply() : Operation(Priority::MUL_DIV, "*") { }

Operation* Multiply::getOperation() {
    return new Multiply();
}

double Multiply::execute(double left, double right) {
    double num = (left*  right);
    return num;
}

Operation *defineOperation() {
    return new Multiply();
}