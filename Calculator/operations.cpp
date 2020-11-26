#include "operations.h"

Operation::Operation(Priority operationPriority, std::string operationName) {
    prior = operationPriority;
    name = operationName;
}

Priority Operation::getPriority() {
    return prior;
}

std::string Operation::getName() {
    return name;
}

char BaseOperation::unary_minus = '_';
char BaseOperation::double_unary_minus[] = { '_','_' };
char BaseOperation::unary_plus = '#';
char BaseOperation::base_operations[] = { '+','*','/','-','(' ,')' };
char BaseOperation::left_bracket = '(';
char BaseOperation::right_bracket = ')';

