#ifndef CONVERTINT16TOFLOAT_H
#define CONVERTINT16TOFLOAT_H

#include "calc-components/abstractcalculationcomponent.h"
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


class ConvertFloatToInt16 : public TCalculator<float, int16_t>
{
public:
    ConvertFloatToInt16(AbstractAccessStrategy::Ptr accessStrategy,
                        CALC_PTR(float, int16_t) input,
                        BUFFER_PTR(int16_t) output);
    virtual bool doCalc(int sampleCount) override;
};


#endif // CONVERTINT16TOFLOAT_H
