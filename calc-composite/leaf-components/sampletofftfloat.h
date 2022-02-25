#ifndef SAMPLETOFFTFLOAT_H
#define SAMPLETOFFTFLOAT_H

#include "calc-composite/abstractcalculationcomponent.h"
#include "buffers/bufferbarefloat.h"

class SampleToFftFloat : public AbstractCalculationComponent
{
public:
    SampleToFftFloat(AbstractAccessStrategy::Ptr accessStrategy,
                     BufferBareFloat::Ptr input,
                     BufferBareFloat::Ptr output);
    virtual void init() override;
    virtual void destroy() override;
    virtual bool doCalc(int subBufferNo) override;
private:
    BufferBareFloat::Ptr m_input;
    BufferBareFloat::Ptr m_output;
};

#endif // SAMPLETOFFTFLOAT_H
