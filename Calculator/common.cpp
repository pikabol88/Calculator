#include"common.h"
#include "operations.h"

std::string substr(std::string str, int startPoint, int size) {
    std::string newStr = "";
    for (int i = 0; i < size; ++i)
        newStr += str[startPoint + i];
    return newStr;
}

std::string replaceAll(const std::string& inputStr, const char *oldExp, const char *newExp) {
    std::regex rx(oldExp);
    std::string newStr;
    newStr = std::regex_replace(inputStr, rx, newExp);
    return newStr;
}

std::string UnaryOperationsProcessing(std::string str) {
    int size = str.length();
    bool isOperation = false;
    int i = 0;

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
    char unary = BaseOperation::unary_plus;
    std::string newStr = replaceAll(str,"#", "");
    newStr = replaceAll(newStr, &unary, "");
    return newStr;
}

