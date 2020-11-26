#ifndef IEXPRESSION_H
#define IEXPRESSION_H

class Expression;
class Operation;

class IExpression {
public:
    bool negative;
    bool unary;
    Operation *base_operations;

    //TO DO: safe handling of adding expressions to children
    virtual Expression *getExpression() { return 0; }
    virtual double calculate() { return 0; }
    virtual ~IExpression() {}
};

#endif //IEXPRESSION_H