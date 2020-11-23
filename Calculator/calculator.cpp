#include "calculator.h"

Calculator::Calculator() {
    std::vector<Operation*> add_sub;
    add_sub.push_back(new Addition());
    add_sub.push_back(new Subtraction());

    std::vector<Operation*> mul_div;
    add_sub.push_back(new Multiply());
    add_sub.push_back(new Division());

    operations.insert(make_pair(priority::ADD_SUB, add_sub));
    operations.insert(make_pair(priority::MUL_DIV, mul_div));

}
