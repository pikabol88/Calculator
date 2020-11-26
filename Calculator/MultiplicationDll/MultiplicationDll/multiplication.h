#ifndef MULTIPLY_H
#define MULTIPLY_H
#include "../../dllPlugin.h"
class Multiply : public Operation {
public:
    inline Multiply();

    inline virtual Operation *getOperation();

    double execute(double left, double right);
};

#endif // !MULTIPLY_H

