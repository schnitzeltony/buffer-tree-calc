#ifndef SAMPLETOFFTFLOAT_H
#define SAMPLETOFFTFLOAT_H

#include "calc-components/abstractcalculationcomponent.h"
#include "buffers/buffertemplate.h"

class SampleToFftFloat : public AbstractCalculationComponent
{
public:
    SampleToFftFloat(AbstractAccessStrategy::Ptr accessStrategy,
                     BUFFER_PTR(float) input,
                     BUFFER_PTR(float) output);
    virtual void init() override;
    virtual void destroy() override;
    virtual bool doCalc(int sampleCount) override;
private:
    BUFFER_PTR(float) m_input;
    BUFFER_PTR(float) m_output;
};

#endif // SAMPLETOFFTFLOAT_H
