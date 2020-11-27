#include "number.h"

Number::Number(const std::string &num) {
    number = num;
    negative = false;
}

double Number::calculate() {
    double num = std::stod(number);
    return (negative) ? num * (-1) : num;
}
