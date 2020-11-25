#include"common.h"

std::string substring(std::string str, int startPoint, int size) {
    std::string newStr = "";
    for (int i = 0; i < size; ++i)
        newStr += str[startPoint + i];
    return newStr;
}

std::string replaceAll(const std::string& inputStr, const char *oldExp, const char *newExp) {
    std::regex rx(oldExp);
    return std::regex_replace(inputStr, rx, newExp);
}

bool brack(std::string str) {
    int brackets = 0;
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == '(') brackets++;
        if (str[i] == ')') brackets--;
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