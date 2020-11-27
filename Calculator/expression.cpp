#include "expression.h"
#include "function.h"
#include "calculator.h"
#include "number.h"

Expression::Expression() {
    negative = false;
    unary = false;
}

Expression::~Expression() {
    delete left;
    delete right;
}

Operation* Expression::defineTrigonometry(std::string str) {
    std::string tmp;
    std::vector<Operation*> expressions = (*Calculator::operations_map.find(Priority::FUNCTION)).second;
    for (int i = 0;i < str.size();i++) {
        if (str[i] == BaseOperation::left_bracket) {
            tmp = substring(str, 0, i);
            break;
        }
    }
    for (auto& el : expressions) {        
        if (!(el->getName()).compare(tmp)) {
           return el->getOperation();
        }
    }
    return nullptr;
}

Operation* Expression::defineConstant(std::string str) {
    std::vector<Operation*> expressions = (*Calculator::operations_map.find(Priority::CONSTANT)).second;    
    for (auto& el : expressions) {
        if (!(el->getName()).compare(str)) {
            return el->getOperation();
        }
    }
    return nullptr;
}

Expression::Expression(const std::string  &str){
    negative = false;
    parseExpression(str);
}

Expression* Expression:: getExpression() {
    return this;
}

double Expression::calculate() {
    double num;
    if (base_operations == nullptr) {
        num = left->calculate();
    }
    else {
        if (!(right == nullptr)) { 
            num = base_operations->execute(left->calculate(), right->calculate());
        } else num = base_operations->execute(left->calculate(), 0);
    }
    return (negative) ? num * (-1) : num;
}


void Expression::parseExpression(const std::string &str) {    
    bool isRecurtionActivated = false;

    processBrackets(str, &isRecurtionActivated);
    if (isRecurtionActivated) return;  
    processSecondPriorityOperations(str, &isRecurtionActivated);
    if (isRecurtionActivated) return;
    processFirstPriorityOperations(str, &isRecurtionActivated);
    if (isRecurtionActivated) return;
    processPower(str, &isRecurtionActivated);
    if (isRecurtionActivated) return;
    
    processExpression(str, str.length());
}

void Expression::processPower(const std::string &str, bool *isActivated) {
    int brackets = 0;
    std::string tmp;
    std::vector<Operation*> expressions = (*Calculator::operations_map.find(Priority::POWER)).second;
    for (int i = 0; i < str.length(); ++i) {
        tmp = str[i];
        if (brackets == 0) {
            for (auto& el : expressions) {
                if (!(el->getName()).compare(tmp)) {
                    base_operations = el->getOperation();
                    if (str[0] == BaseOperation::unary_minus) {
                        negative = true;
                        processExpression(substring(str, 1, str.length() - 1), i - 1);
                    }
                    else
                        processExpression(str, i);
                    *isActivated = true;
                    return;
                }
            }
        }
        if (str[i] == BaseOperation::left_bracket) brackets++;
        if (str[i] == BaseOperation::right_bracket) brackets--;
    }
}


void Expression::processFirstPriorityOperations(const std::string &str, bool *isActivated) {
    int brackets = 0;
    std::string tmp;
    std::vector<Operation*> expressions = (*Calculator::operations_map.find(Priority::MUL_DIV)).second;
    for (int i = 0; i < str.length(); ++i) {
        tmp = str[i];
        if (brackets == 0) {
            for (auto& el :expressions) {
                if (!(el->getName()).compare(tmp)) {                    
                    base_operations = el->getOperation();
                    processExpression(str, i);
                    *isActivated = true;
                    return;
                }
            }
        }
        if (str[i] == BaseOperation::left_bracket) brackets++;
        if (str[i] == BaseOperation::right_bracket) brackets--;
    }
}



void Expression::processSecondPriorityOperations(const std::string &str, bool *isActivated) {
    int brackets = 0;
    std::string tmp;
    std::vector<Operation*> expressions = (*Calculator::operations_map.find(Priority::ADD_SUB)).second;
    for (int i = 0; i < str.length(); ++i) {
        tmp = str[i];
        if (brackets == 0) {
            for (auto& el : expressions) {                
                if (!(el->getName()).compare(tmp)) {
                    base_operations = el->getOperation();
                    processExpression(str, i);
                    *isActivated = true;
                    return;
                }
            }
        }
        if (str[i] == '(') brackets++;
        if (str[i] == ')') brackets--;
    }
}


void Expression::processBrackets(const std::string &str, bool *isActivated) {
    if (str[0] == BaseOperation::left_bracket && str[str.length() - 1] == BaseOperation::right_bracket && brack(substring(str, 1, str.length() - 2))) {
        *isActivated = true;
        return parseExpression(substring(str, 1, str.length() - 2));
    } else if (str[0] == BaseOperation::unary_minus && str[1] == BaseOperation::left_bracket && 
               str[str.length() - 1] == BaseOperation::right_bracket && brack(substring(str, 2, str.length() - 3))) {
        negative = true;
        *isActivated = true;
        return parseExpression(substring(str, 2, str.length() - 3));
    }    
}


void Expression::processExpression(const std::string &str, int index) {
    std::string substrl = substring(str, 0, index);
    std::string substrr = substring(str, index + 1, str.length() - index - 1);
    if(!substrl.empty()) addExpression(substrl, this->left);
    if(!substrr.empty()) addExpression(substrr, this->right);
    else unary = true;
    operation = str[index];
}


void Expression::addExpression(std::string str, IExpression *&place) {

    std::regex unary_minus("_");
    std::regex right_bracket("\\(");
    std::regex left_bracket("\\)");
    Operation *opertmp;
    bool first_minus = false;
    bool minus_after_bracket = false;
    std::string func;
    if (str[0] == BaseOperation::unary_minus) {
        str = substring(str, 1, str.length() - 1);
        first_minus = true;
    }
    std::string tmp = str;
    if (str[0] == BaseOperation::left_bracket) {
        tmp = substring(tmp, 1, tmp.length() - 2);
        if (str[1] == BaseOperation::unary_minus) {
            tmp = std::regex_replace(tmp, unary_minus, "");
            minus_after_bracket = true;
        }
    }
    opertmp = defineTrigonometry(str);
    if (opertmp) {
        place = new Function(tmp, opertmp);
        place->negative = first_minus;
        return;
    }
    opertmp = defineConstant(str);
    if (opertmp) {
        place = new Constant(opertmp);
        place->negative = first_minus;
        return;
    }
    if (isNumber(tmp)) {
        tmp = std::regex_replace(tmp, unary_minus, "");
        place = new Number(tmp);
        if (first_minus || minus_after_bracket) {
            place->negative = true;
        }
    }
    else {
        place = new Expression(str);
        place->negative = first_minus;
    }
}
