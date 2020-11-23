#include "calculator.h"

std::map<int, std::vector<Operation*>> Calculator::oper_map = {};



void Calculator::setExpression(std::string exp) {
    if (expression) {
        free(expression);
    }
    expression = new Expression(exp);
}

double Calculator::runCalculating()
{
   return  expression->calculate();
   
}

Calculator::Calculator() {
    std::vector<Operation*> add_sub;
    add_sub.push_back(new Addition());
    add_sub.push_back(new Subtraction());

    std::vector<Operation*> mul_div;
    mul_div.push_back(new Multiply());
    mul_div.push_back(new Division());

    oper_map.insert(make_pair(priority::ADD_SUB, add_sub));
    oper_map.insert(make_pair(priority::MUL_DIV, mul_div));

    
}
