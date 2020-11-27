#ifndef NUMBER_H
#define NUMBER_H

#include "iexpression.h"
#include <string> 


class Number : public  IExpression {
    std::string number;
public:
    Number(const std::string &num);

    virtual double calculate();
};


#endif //NUMBER_H
