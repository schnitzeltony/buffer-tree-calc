#ifndef ABSTRACTCALCULATIONCOMPONENT_H
#define ABSTRACTCALCULATIONCOMPONENT_H

#include "access-strategies/abstractaccessstrategy.h"

class AbstractCalculationComponent
{
public:
    AbstractCalculationComponent(AbstractAccessStrategy::Ptr busyState);

    virtual void init() {}
    virtual void destroy() {}

    void prepareCalc();
    bool startCalc(int subBufferNo);
    bool calcDone();
    void setDone(bool done);
protected:
    virtual bool doCalc(int subBufferNo) = 0;
    AbstractAccessStrategy::Ptr m_busyState;
};

typedef std::shared_ptr<AbstractCalculationComponent> AbstractCalculationComponentPtr;


#endif // ABSTRACTCALCULATIONCOMPONENT_H
