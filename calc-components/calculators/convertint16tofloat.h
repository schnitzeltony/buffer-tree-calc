#ifndef CONVERTINT16TOFLOAT_H
#define CONVERTINT16TOFLOAT_H

#include "buffers/buffertemplate.h"
#include "calc-components/tcalccontainer.h"

class ConvertInt16ToFloat : public TCalcContainer<int16_t, float>
{
public:
    ConvertInt16ToFloat(AbstractAccessStrategy::Ptr accessStrategy,
                        CALC_PTR(int16_t, float) input,
                        BUFFER_PTR(float) output);
    virtual bool doCalc(int sampleCount) override;
};




#endif // CONVERTINT16TOFLOAT_H
