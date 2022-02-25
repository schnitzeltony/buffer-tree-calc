#ifndef CALCULATIONNODE_H
#define CALCULATIONNODE_H

#include "abstractcalculationcomponent.h"
#include "calc-strategies/abstractcalculationstrategy.h"

class CalculationNode: public AbstractCalculationComponent
{
public:
    virtual bool doCalc(int subBufferNo) override;
    virtual void init() override;
    virtual void destroy() override;
private:
    AbstractCalculationStrategyPtr m_outCalcStrategy;
};

#endif // CALCULATIONNODE_H
