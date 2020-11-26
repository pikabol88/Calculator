#ifndef COSINE_H
#define COSINE_H
#include "../../dllPlugin.h"

class Cosine : public Operation {
public:
    inline Cosine();

    inline virtual Operation *getOperation();

    double execute(double left, double right);
};



#endif // !COSINE_H

