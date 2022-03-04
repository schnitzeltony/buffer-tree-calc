#ifndef ABSTRACTCALCULATIONCOMPONENT_H
#define ABSTRACTCALCULATIONCOMPONENT_H

#include "access-strategies/abstractaccessstrategy.h"

class AbstractCalculationComponent
{
public:
    typedef std::shared_ptr<AbstractCalculationComponent> Ptr;
    AbstractCalculationComponent(AbstractAccessStrategy::Ptr accessStrategy);

    virtual void init() {}
    virtual void destroy() {}

    void prepareCalc();
    bool tryStartCalc(int sampleCount);
protected:
    virtual bool doCalc(int sampleCount) = 0;
    bool calcDone();
    void setDone();
    AbstractAccessStrategy::Ptr m_accessStrategy;
};

#endif // ABSTRACTCALCULATIONCOMPONENT_H
