#include "calculator.h"

std::map<int, std::vector<Operation*>> Calculator::oper_map = {};

void Calculator::setExpression(std::string exp) {
    str_exp = exp;
    ErrorState::setErrorState(ErrorState::SUCCESS);
    processError();
    if (ErrorState::isSuccess()) {
        if (expression == nullptr) {
            free(expression);
        }
        expression = new Expression(exp);
    }
}

std::string Calculator::UnaryOperationsProcessing(std::string str) {
    int i = 0;
    str = replaceAll(str, " ", "");
    int size = str.length();
    while (str[i] == '-') { str[i++] = BaseOperation::unary_minus; }
    while (str[i] == '+') { str[i++] = BaseOperation::unary_plus; }

    for (i; i < size; i++) {
        if (strchr(BaseOperation::operations, str[i])) {
            do {
                i++;
                if (str[i] == '-') { str[i] = BaseOperation::unary_minus; }
                else if (str[i] == '+') { str[i] = BaseOperation::unary_plus; }
                break;
            } while (i < size - 1);
            i--;
        }
    }
    std::string newStr = replaceAll(str, "#", "");
    newStr = replaceAll(newStr, "__", "");
    return newStr;
}

bool Calculator::processAlphaError(int *index){
    int startIndex = *(index);
    int currentIndex = *(index);
    while (isalpha(str_exp[currentIndex])) currentIndex++;
    if (!isLexemDefined(substring(str_exp, startIndex, currentIndex - startIndex))) {
        ErrorState::setErrorState(ErrorState::ERROR_FUNCTION);
        return true;
    }
    currentIndex--;
    *(index) = currentIndex;
    return false;
}

bool Calculator::processOperationError(int *index) {
    int startIndex = *(index);
    int currentIndex = *(index);
    while (!isalpha(str_exp[currentIndex]) && !isdigit(str_exp[currentIndex])
        && str_exp[currentIndex] != BaseOperation::left_bracket&&str_exp[currentIndex] != BaseOperation::right_bracket) 
        currentIndex++;

    if (!isLexemDefined(substring(str_exp, startIndex, currentIndex - startIndex))) {
        ErrorState::setErrorState(ErrorState::ERROR_OPERATION);
        return true;
    }
    currentIndex--;
    *(index) = currentIndex;
    return false;
}

bool Calculator::isLexemDefined(std::string lexem) {
    if (isalpha(lexem[0])) return isFunctionDefined(lexem);
    else return isOperationDefined(lexem);
}


bool Calculator::isOperationDefined(std::string lexem) {
    for (auto& el : valid_operations) {
        if (!el.compare(lexem)) { return true; }
    }
    return false;
}

bool Calculator::isFunctionDefined(std::string lexem) {
    for (auto& el : valid_functions) {
        if (!el.compare(lexem)) { return true; }
    }
    return false;
}

void Calculator::processError() {
    int left_bracket = 0;
    int right_bracket = 0;
    bool isDigit = false;
    bool previosIsPoint = false;

    for (int i = 0; i < str_exp.size(); i++) {
        while (isdigit(str_exp[i])) {
            isDigit = true;
            i++;
        }
        if (i >= str_exp.size())  break;

        if (str_exp[i] == '.') {
            if (previosIsPoint) {
                ErrorState::setErrorState(ErrorState::ERROR_POINT);
                break;
            }
            previosIsPoint = true;
        } else {
            previosIsPoint = false;
            if (str_exp[i] == '(') {
                left_bracket++;
                isDigit = false;
            } else if (str_exp[i] == ')') {
                right_bracket++;
                if (!isDigit) {
                    ErrorState::setErrorState(ErrorState::ERROR_EMPTY_BRACKETS);
                    break;
                }
            } else if (isalpha(str_exp[i])) {
                if(processAlphaError(&i)) break;
            }
            else if (processOperationError(&i)) break;
        }
    }

    if (ErrorState::isSuccess()) {
        if (left_bracket != right_bracket) {
            ErrorState::setErrorState(ErrorState::ERROR_BRACKETS);
        }
    }
}



double Calculator::runCalculating(std::string str) {
    str = UnaryOperationsProcessing(str);
    setExpression(str);
    if (ErrorState::isSuccess()) {
        return  expression->calculate();
    }
}


Calculator::Calculator() {
    Operation *element;
    std::vector<Operation*> add_sub;

    element = new Addition();
    valid_operations.push_back(element->getName());
    add_sub.push_back(element);

    element = new Subtraction();
    valid_operations.push_back(element->getName());
    add_sub.push_back(new Subtraction());

    std::vector<Operation*> mul_div;

    element = new Multiply();
    valid_operations.push_back(element->getName());
    mul_div.push_back(new Multiply());

    element = new Division();
    valid_operations.push_back(element->getName());
    mul_div.push_back(new Division());

    std::vector<Operation*> pov;

    element = new Power();
    valid_operations.push_back(element->getName());
    pov.push_back(new Power());


    std::vector<Operation*> fun;
    element = new Cosine();
    valid_functions.push_back(element->getName());
    fun.push_back(new Cosine());

    element = new Sinus();
    valid_functions.push_back(element->getName());
    fun.push_back(new Sinus());


    oper_map.insert(make_pair(priority::ADD_SUB, add_sub));
    oper_map.insert(make_pair(priority::MUL_DIV, mul_div));
    oper_map.insert(make_pair(priority::POWER, pov));
    oper_map.insert(make_pair(priority::FUNCTION, fun));
}

Calculator::~Calculator() {
    delete expression;
    for (auto& map_el : oper_map) {
        for (auto& vec_el : map_el.second) {
            delete vec_el;
        }
    }
}

