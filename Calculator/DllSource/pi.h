#ifndef PI_H
#define PI_H
#include "../../dllPlugin.h"

class Pi : public Operation {
public:
    Pi();
    virtual Operation *getOperation();
    virtual double execute(double left, double right);
};

#endif // !PI_H

