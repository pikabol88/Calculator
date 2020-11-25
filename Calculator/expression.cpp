#include "expression.h"
#include "function.h"
#include "common.h"
#include "operations.h"
#include "iexpression.h"
#include "calculator.h"
#include <vector>
#include <map>


#include <regex>



bool brack(std::string s) {
    int brackets = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '(') brackets++;
        if (s[i] == ')') brackets--;
        if (brackets < 0) return 0;
    }
    if (brackets != 0) return 0;
    return 1;
}


bool isNumber(std::string str) {
    std::regex rx("_");
    int place = str.find_first_of("*/-+^()");
    if (place < 0) {
        return true;
    }
    return false;
}

Operation* defineTrigonometry(std::string str) {
    std::string tmp;
    std::vector<Operation*> expressions = (*Calculator::oper_map.find(priority::FUNCTION)).second;
    for (int i = 0;i < str.size();i++) {
        if (str[i] == BaseOperation::left_bracket) {
            tmp = substr(str, 0, i);
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

Number::Number(std::string num) {
    number = num;
    negative = false;
   
}

double Number:: calculate() {
    double num = std::stod(number);    
    return (negative) ? num * (-1) : num;
}


Expression::Expression() {
    negative = false;
    unary = false;
}

Expression::Expression(std::string str){
    negative = false;
    parseExpression(str);
    
}

Expression* Expression:: getExpression() {
    return this;
}

double Expression::calculate() {
    double num;
    if (operations == nullptr) {
        num = left->calculate();
    }
    else {
        if (!(right == nullptr)) {
            num = operations->execute(left->calculate(), right->calculate());
        }
        else {
            num = operations->execute(left->calculate(), 0);
        }
    }
    return (negative) ? num * (-1) : num;
}


Expression::~Expression() {
}

void Expression::parseExpression(const std::string str) {    
    bool isRecurtionActivated = false;
    full = str;

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

void Expression::processPower(const std::string str, bool *isActivated) {
    int brackets = 0;
    std::string tmp;
    std::vector<Operation*> expressions = (*Calculator::oper_map.find(priority::POWER)).second;
    for (int i = 0; i < str.length(); ++i) {
        tmp = str[i];
        if (brackets == 0) {
            for (auto& el : expressions) {
                if (!(el->getName()).compare(tmp)) {
                    operations = el->getOperation();
                    if (str[0] == BaseOperation::unary_minus) {
                        negative = true;
                        processExpression(substr(str, 1, str.length() - 1), i - 1);
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


void Expression::processFirstPriorityOperations(const std::string str, bool *isActivated) {
    int brackets = 0;
    std::string tmp;
    std::vector<Operation*> expressions = (*Calculator::oper_map.find(priority::MUL_DIV)).second;
    for (int i = 0; i < str.length(); ++i) {
        tmp = str[i];
        if (brackets == 0) {
            for (auto& el :expressions) {
                if (!(el->getName()).compare(tmp)) {                    
                    operations = el->getOperation();
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



void Expression::processSecondPriorityOperations(const std::string str, bool *isActivated) {
    int brackets = 0;
    std::string tmp;
    std::vector<Operation*> expressions = (*Calculator::oper_map.find(priority::ADD_SUB)).second;
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
        }
        if (str[i] == '(') brackets++;
        if (str[i] == ')') brackets--;
    }
}


void Expression::processBrackets(const std::string str, bool *isActivated) {
    if (str[0] == BaseOperation::left_bracket && str[str.length() - 1] == BaseOperation::right_bracket && brack(substr(str, 1, str.length() - 2))) {
        *isActivated = true;
        return parseExpression(substr(str, 1, str.length() - 2));
    } else if (str[0] == BaseOperation::unary_minus && str[1] == BaseOperation::left_bracket && 
               str[str.length() - 1] == BaseOperation::right_bracket && brack(substr(str, 2, str.length() - 3))) {
        negative = true;
        *isActivated = true;
        return parseExpression(substr(str, 2, str.length() - 3));
    }    
}


void Expression::processExpression(std::string str, int index) {
    std::string substrl = substr(str, 0, index);
    std::string substrr = substr(str, index + 1, str.length() - index - 1);
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
        str = substr(str, 1, str.length()-1);
        first_minus = true;
    }
    std::string tmp = str;
    if (str[0] == BaseOperation::left_bracket) {       
        tmp = substr(tmp, 1, tmp.length() - 2);
        if (str[1] == BaseOperation::unary_minus) {
            tmp = std::regex_replace(tmp, unary_minus, "");
            minus_after_bracket = true;
        }
    }
    opertmp = defineTrigonometry(str);
    if (opertmp) {
        place = new Function(tmp, opertmp);
        place->negative = first_minus;
    }    
    else {
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
}
