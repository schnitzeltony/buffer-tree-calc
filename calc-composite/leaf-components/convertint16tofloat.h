#ifndef CONVERTINT16TOFLOAT_H
#define CONVERTINT16TOFLOAT_H

#include "calc-composite/abstractcalculationcomponent.h"
#include "buffers/buffertemplate.h"

class ConvertInt16ToBareFloat : public AbstractCalculationComponent
{
public:
    ConvertInt16ToBareFloat(AbstractAccessStrategy::Ptr accessStrategy,
                            BUFFER_PTR(int16_t) input,
                            BUFFER_PTR(float) output);
    virtual bool doCalc(int sampleCount) override;
private:
    BUFFER_PTR(int16_t) m_input;
    BUFFER_PTR(float) m_output;
};

#endif // CONVERTINT16TOFLOAT_H
