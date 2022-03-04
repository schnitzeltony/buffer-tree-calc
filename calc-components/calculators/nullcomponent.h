#ifndef NULLCOMPONENT_H
#define NULLCOMPONENT_H

#include "buffers/buffertemplate.h"
#include "calc-components/tcalculator.h"

template <class OUTTYPE>
class NullComponent : public TCalculator<OUTTYPE, OUTTYPE>
{
public:
    NullComponent(AbstractAccessStrategy::Ptr accessStrategy,
                  BUFFER_PTR(OUTTYPE) output) :
        TCalculator<OUTTYPE, OUTTYPE>({}, output, accessStrategy)
    {}
    virtual bool doCalc(int sampleCount) override { (void)sampleCount; return true; };
};

#endif // NULLCOMPONENT_H
