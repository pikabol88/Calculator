#include "calculator.h"

typedef Operation* (*load)();

std::map<int, std::vector<Operation*>> Calculator::operations_map = {};

Calculator::Calculator() {

#ifdef _DEBUG
    const char* path = "../PluginDll/DebugPlugins";
#else
    const char* path = "../PluginDll/ReleasePlugins";
#endif // DEBUG

    processPlugins(path);
    connectPlugins();
}

void Calculator::processPlugins(std::string path) {
    std::filesystem::directory_iterator folder(path);
    std::cout << "Connected plugins:" << std::endl;

    for (auto& dll : folder) {
        if (dll.path().extension().string() != ".dll") {
            continue;
        }

        HMODULE dlllib = LoadLibrary(dll.path().string().c_str());
        if (!dlllib) {
            std::cout << "error with connecting " << dll.path().filename().string() << std::endl;
            continue;
        }
        load loadOperation = (load)GetProcAddress(dlllib, "defineOperation");
        if (!loadOperation) {
            std::cout << "error with loading plugin " << dll.path().filename().string() << std::endl;
            FreeLibrary(dlllib);
            continue;
        }
        dll_libs.push_back(dlllib);
        plugins.push_back(loadOperation());
        std::cout << "\t- " << dll.path().filename().string() << std::endl;
    }
    std::cout << "\n";
}

void Calculator::connectPlugins() {

    std::vector<Operation*> add_sub;
    std::vector<Operation*> mul_div;
    std::vector<Operation*> power;
    std::vector<Operation*> fun;
    std::vector<Operation*> constant;

    for (auto& el : plugins) {
        switch (el->getPriority()) {
        case Priority::ADD_SUB:
            add_sub.push_back(el->getOperation());
            valid_operations.push_back(el->getName());
            break;
        case Priority::MUL_DIV:
            mul_div.push_back(el->getOperation());
            valid_operations.push_back(el->getName());
            break;
        case Priority::POWER:
            power.push_back(el->getOperation());
            valid_operations.push_back(el->getName());
            break;
        case Priority::FUNCTION:
            valid_functions.push_back(el->getName());
            fun.push_back(el->getOperation());
            break;
        case Priority::CONSTANT:
            valid_functions.push_back(el->getName());
            constant.push_back(el->getOperation());
            break;
        default:
            break;
        }
    }
    operations_map.insert(make_pair(Priority::ADD_SUB, add_sub));
    operations_map.insert(make_pair(Priority::MUL_DIV, mul_div));
    operations_map.insert(make_pair(Priority::POWER, power));
    operations_map.insert(make_pair(Priority::FUNCTION, fun));
    operations_map.insert(make_pair(Priority::CONSTANT, constant));
}

void Calculator::setExpression(std::string exp) {
    str_exp = exp;
    ErrorState::setErrorState(ErrorState::SUCCESS);
    processError();
    if (ErrorState::isSuccess()) {
        if (expression != nullptr) {
            free(expression);
        }
        expression = new Expression(exp);
    }
}

std::string Calculator::unaryOperationsProcessing(std::string str) {
    int i = 0;
    str = replaceAll(str, " ", "");
    int size = str.length();
    while (str[i] == '-') { str[i++] = BaseOperation::unary_minus; }
    while (str[i] == '+') { str[i++] = BaseOperation::unary_plus; }

    for (i; i < size; i++) {
        if (strchr(BaseOperation::base_operations, str[i])) {
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
        && str_exp[currentIndex] != BaseOperation::left_bracket && str_exp[currentIndex] != BaseOperation::right_bracket) 
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
    str = unaryOperationsProcessing(str);
    setExpression(str);
    if (ErrorState::isSuccess()) {
        return  expression->calculate();
    }
}

Calculator::~Calculator() {
    delete expression;
    for (auto& map_el : operations_map) {
        for (auto& vec_el : map_el.second) {
            delete vec_el;
        }
    }
    for (auto &lib : dll_libs) {
        FreeLibrary(lib);
    }
}

