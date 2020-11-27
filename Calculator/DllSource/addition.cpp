#include "addition.h"

Addition::Addition() : Operation(Priority::ADD_SUB, "+") {}

double Addition::execute(double left, double right) {
    double num = (left + right);
    return num;
}

Operation* Addition::getOperation() {
    return new Addition();
}

Operation *defineOperation() {
    return new Addition();
}