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



