#ifndef CONVERTINT16TOFLOAT_H
#define CONVERTINT16TOFLOAT_H

#include "buffers/buffertemplate.h"
#include "calc-components/tcalculator.h"

class ConvertInt16ToFloat : public TCalculator<int16_t, float>
{
public:
    ConvertInt16ToFloat(AbstractAccessStrategy::Ptr accessStrategy,
                        CALC_PTR(int16_t, float) input,
                        BUFFER_PTR(float) output);
    virtual bool doCalc(int sampleCount) override;
};




#endif // CONVERTINT16TOFLOAT_H
