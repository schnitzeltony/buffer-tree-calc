#ifndef ABSTRACTCALCULATIONCOMPONENT_H
#define ABSTRACTCALCULATIONCOMPONENT_H

#include "access-strategies/abstractaccessstrategy.h"

class AbstractCalculationComponent
{
public:
    typedef std::shared_ptr<AbstractCalculationComponent> Ptr;
    AbstractCalculationComponent(AbstractAccessStrategy::Ptr accessStrategy);

    virtual void init() = 0;
    virtual void destroy() = 0;

    void prepareCalc();
    bool tryStartCalc(int sampleCount);

    virtual bool doCalc(int sampleCount) = 0;
    bool calcDone();
    void setDone();
protected:
    AbstractAccessStrategy::Ptr m_accessStrategy;
};

#endif // ABSTRACTCALCULATIONCOMPONENT_H
