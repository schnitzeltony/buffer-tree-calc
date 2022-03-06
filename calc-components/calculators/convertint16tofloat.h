#ifndef CONVERTINT16TOFLOAT_H
#define CONVERTINT16TOFLOAT_H

#include "calc-components/calculatorbase.h"
#include "buffers/buffertemplate.h"

class ConvertInt16ToFloat : public CalculatorBase<float>
{
public:
    ConvertInt16ToFloat(CALC_PTR(int16_t) input,
                        BUFFER_PTR(float) output,
                        AbstractAccessStrategy::Ptr accessStrategy);
    virtual void doCalc(int sampleCount) override;
};




#endif // CONVERTINT16TOFLOAT_H
