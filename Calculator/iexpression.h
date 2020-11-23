#ifndef IEXPRESSION_H
#define IEXPRESSION_H

class Expression;

class IExpression {
public:
    bool negative;
    bool unary;
    //�������� ������ �� ���������� � ������
    virtual Expression *getExpression() { return 0; }
    virtual double calculate() { return 0; }
    virtual ~IExpression() {}
};

#endif //IEXPRESSION_H