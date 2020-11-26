#ifndef POWER_H
#define POWER_H
//#include "../../dllPlugin.h"
#include "../../operations.h"
class Power : public Operation {
public:
    inline Power();
    inline virtual Operation *getOperation();
    virtual double execute(double left, double right);
};

//inline Operation *defineOperation();

extern "C" {
    __declspec(dllexport) Operation* defineOperation();
}
#endif // !POWER_H
