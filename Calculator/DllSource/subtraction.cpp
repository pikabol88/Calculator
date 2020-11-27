#include "subtraction.h"

Subtraction::Subtraction() : Operation(Priority::ADD_SUB, "-") {}
double Subtraction::execute(double left, double right) {
    double num = (left - right);
    return num;
}
Operation* Subtraction::getOperation() {
    return new Subtraction();
}

Operation *defineOperation() {
    return new Subtraction();
}