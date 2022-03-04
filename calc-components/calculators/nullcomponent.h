#ifndef NULLCOMPONENT_H
#define NULLCOMPONENT_H

#include "buffers/buffertemplate.h"
#include "calc-components/tcalccontainer.h"

template <class OUTTYPE>
class NullComponent : public TCalcContainer<OUTTYPE, OUTTYPE>
{
public:
    NullComponent(AbstractAccessStrategy::Ptr accessStrategy,
                  BUFFER_PTR(OUTTYPE) output) :
        TCalcContainer<OUTTYPE, OUTTYPE>({}, output, accessStrategy) { }
    virtual bool doCalc(int) override { return true; };
};

#endif // NULLCOMPONENT_H
