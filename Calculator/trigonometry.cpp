#include "trigonometry.h"
#include "common.h"

std::string TrigonometryOperation::sinus = "sin";
std::string TrigonometryOperation::cosine = "cos";
std::string TrigonometryOperation::tangent = "tg";
std::string TrigonometryOperation::cotangent = "ctg";

Function::Function(std::string str, std::string func) {
    operation = func;
    int i = 0;
    while (isalpha(str[i])) i++;
    addExpression(substr(str, i, str.length() - i), this->expression);
}

double Function::calculate() {
    double num;
    if (operation == TrigonometryOperation::cosine) {
        num = cos(expression->calculate());
        return  (negative) ? num * (-1) : num;
    }
    if (operation == TrigonometryOperation::sinus) {
        num = sin(expression->calculate());
        return  (negative) ? num * (-1) : num;
    }
    if (operation == TrigonometryOperation::tangent) {
        num = tan(expression->calculate());
        return  (negative) ? num * (-1) : num;
    }
    if (operation == TrigonometryOperation::cotangent) {
        num = 1/(tan(expression->calculate()));
        return  (negative) ? num * (-1) : num;
    }


}


