#ifndef ADDITIONAL_H
#define ADDITIONAL_H

#include "..//..//dllPlugin.h"
class Addition : public Operation {
public:
    Addition();
    virtual Operation *getOperation();
    virtual double execute(double left, double right);
};

#endif // !ADDITIONAL_H


