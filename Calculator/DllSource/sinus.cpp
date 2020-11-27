#include "sinus.h"

Sinus::Sinus() : Operation(Priority::FUNCTION, "sin") {}
double Sinus::execute(double left, double right) {
    double num = sin(left);
    return num;
}
Operation* Sinus::getOperation() {
    return new Sinus();
}

Operation *defineOperation() {
    return new Sinus();
}