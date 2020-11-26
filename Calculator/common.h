#ifndef COMMON_H
#define COMMON_H

#include <math.h>
#include <iostream>
#include <string> 
#include <regex>
#include <map>
#include <vector>

std::string substring(std::string str, int startPoint, int siz);
std::string replaceAll(const std::string& inputStr, const char *oldExp, const char *newExp);
bool brack(std::string str);
bool isNumber(std::string str);

#endif //COMMON_H