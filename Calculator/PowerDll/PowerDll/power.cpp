#include "power.h"

Power::Power() : Operation(Priority::POWER, "^") {}

double Power::execute(double left, double right) {
    double num = pow(left, right);
    return num;
}
Operation* Power::getOperation() {
    return new Power();
}

Operation *defineOperation() {
    return new Power();
}