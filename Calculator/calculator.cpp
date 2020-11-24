#include "calculator.h"

std::map<int, std::vector<Operation*>> Calculator::oper_map = {};



void Calculator::setExpression(std::string exp) {
    str_exp = exp;
    ErrorState::setErrorState(ErrorState::SUCCESS);
    processError();
    if (ErrorState::getErrorState() == ErrorState::SUCCESS) {
        if (expression) {
            free(expression);
        }
        expression = new Expression(exp);
    }
    else {
        std::cout << ErrorState::getErrorMessage();
    }
 }

void Calculator::processError() {
    int left_bracket = 0;
    int right_bracket = 0;
    bool isDigit = false;
    std::string lexem;
    int startIndex;
    for (int i = 0;i < str_exp.size();i++) {
        while (isdigit(str_exp[i])) {
            isDigit = true;
            i++;           
        }
        if (i >= str_exp.size())
            break;
        if (str_exp[i] == '(') {
            left_bracket++;
            isDigit = false;
        }
        else if (str_exp[i] == ')') {
            right_bracket++;
            if (!isDigit) {
                ErrorState::setErrorState(ErrorState::ERROR_EMPTY_BRACKETS);
                break;
            }
        }
        else if (isalpha(str_exp[i])) {
            startIndex = i;
            while (isalpha(str_exp[i])) i++;            
            if (!isLexemDefined(substr(str_exp, startIndex, i-startIndex))) {
                ErrorState::setErrorState(ErrorState::ERROR_FUNCTION);
                break;
            }
            i--;
            
        }
        else if (str_exp[i] == '.');
        else {
            std::string tmp(1, str_exp[i]);
            if (!isLexemDefined(tmp)) {
                ErrorState::setErrorState(ErrorState::ERROR_OPERATION);
                break;
            }
        }
    }
    if (ErrorState::getErrorState() == ErrorState::SUCCESS) {
        if (left_bracket != right_bracket) {
            ErrorState::setErrorState(ErrorState::ERROR_BRACKETS);
        }
    }

    /*std::cout << (std::find(vector1.begin(), vector1.end(), 13) == vector1.end() ? "нету " : "есть ") << 13 << " в массиве." << std::endl;

    std::vector<Operation*> expressions = (*Calculator::oper_map.find(priority::MUL_DIV)).second;
    for (int i = 0; i < str.length(); ++i) {
        tmp = str[i];
        if (brackets == 0) {
            for (auto& el : expressions) {
                if (!(el->getName()).compare(tmp)) {
                    operations = el->getOperation();
                    processExpression(str, i);
                    *isActivated = true;
                    return;
                }
            }
        }*/
}

double Calculator::runCalculating() {   
    return  expression->calculate();
   
}

bool Calculator::isLexemDefined(std::string lexem) {
    if (isalpha(lexem[0])) return isFunctionDefined(lexem);
    else return isOperationDefined(lexem);
}

bool Calculator::isLexemDefined(char *symbol) {
    std::string lexem(symbol);
    if (isalpha(lexem[0])) return isFunctionDefined(lexem);
    else return isOperationDefined(lexem);
}

bool Calculator::isOperationDefined(std::string lexem) {
    for (auto& el : valid_operations) {
        if (!el.compare(lexem)) {
            return true;
        }
    }
    return false;
}
 
bool Calculator::isFunctionDefined(std::string lexem) {
    for (auto& el : valid_functions) {
        if (!el.compare(lexem)) {
            return true;
        }
    }
    return false;
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
