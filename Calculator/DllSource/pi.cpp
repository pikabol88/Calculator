#include "pi.h"

Pi::Pi() : Operation(Priority::CONSTANT, "pi") {}
double Pi::execute(double left, double right) {
    double num = 2 * asin(1);
    return num;
}
Operation* Pi::getOperation() {
    return new Pi();
}

Operation *defineOperation() {
    return new Pi();
}