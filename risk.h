#ifndef RISK_H
#define RISK_H

class Risk
{
public:
    enum Probability{
        Unthinkable,
        Low,
        Middle,
        High
    };

    enum Damage{
        Marginal,
        Low,
        Middle,
        High
    };

    enum Resulting{

    };

    Risk();
    virtual ~Risk();



private:
    Probability probability;
    Damage damage;
};

#endif // RISK_H
