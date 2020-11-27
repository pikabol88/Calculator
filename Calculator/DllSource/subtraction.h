#ifndef SUBTRACTION_H
#define SUBTRACTION_H
#include "../../dllPlugin.h"

class Subtraction : public Operation {
public:
    Subtraction();
    virtual Operation *getOperation();
    virtual double execute(double left, double right);
};


#endif // !SUBTRACTION_H
