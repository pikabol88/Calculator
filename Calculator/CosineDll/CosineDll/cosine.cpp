#include "cosine.h"

Cosine::Cosine() : Operation(Priority::FUNCTION, "cos") { }

Operation* Cosine::getOperation() {
    return new Cosine();
}

double Cosine::execute(double left, double right) {
    double num = cos(left);
    return num;
}

Operation *defineOperation() {
    return new Cosine();
}