#ifndef CALCULATIONNODE_H
#define CALCULATIONNODE_H

#include "abstractcalculationcomponent.h"
#include <vector>

class ICalcNodeComponents
{
public:
    typedef std::shared_ptr<ICalcNodeComponents> Ptr;
    virtual std::vector<AbstractCalculationComponent *> getInputComponents() = 0;
    virtual AbstractCalculationComponent *getOutputComponent() = 0;
};

class CalculationNode: public AbstractCalculationComponent
{
public:
    CalculationNode(AbstractAccessStrategy::Ptr busyState, ICalcNodeComponents::Ptr calcComponents);
    virtual bool doCalc(int subBufferNo) override;
    virtual void init() override;
    virtual void destroy() override;
private:
    ICalcNodeComponents::Ptr m_calcComponents;
};

#endif // CALCULATIONNODE_H
