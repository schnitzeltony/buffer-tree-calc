#ifndef NULLCOMPONENT_H
#define NULLCOMPONENT_H

#include "buffers/buffertemplate.h"
#include "calc-components/abstractcalculationcomponent.h"

template <class T>
class NullComponent : public AbstractCalculationComponent
{
public:
    NullComponent(BUFFER_PTR(T) inputOutput) :
        AbstractCalculationComponent(AbstractAccessStrategy::Ptr())
    {
        (void)inputOutput;
    }
protected:
    virtual bool doCalc(int sampleCount)
    {
        (void) sampleCount;
        return true;
    }
};

#endif // NULLCOMPONENT_H
