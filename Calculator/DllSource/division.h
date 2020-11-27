#ifndef DIVISION_H
#define DIVISION_H
#include "../../dllPlugin.h"

class Division : public Operation {
public:
    Division();
    virtual Operation *getOperation();
    virtual double execute(double left, double right);
};
#endif // !DIVISION_H

