#include "division.h"
Division::Division() : Operation(Priority::MUL_DIV, "/") {}

double Division::execute(double left, double right) {
    double num = (left / right);
    return num;
}
Operation* Division::getOperation() {
    return new Division();
}

Operation *defineOperation() {
    return new Division();
}