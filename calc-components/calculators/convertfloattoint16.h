#ifndef CONVERTFLOATTOINT16_H
#define CONVERTFLOATTOINT16_H

#include "buffers/buffertemplate.h"
#include "calc-components/calculatorbase.h"

class ConvertFloatToInt16 : public CalculatorBase<int16_t>
{
public:
    ConvertFloatToInt16(CALC_PTR(float) input,
                        BUFFER_PTR(int16_t) output,
                        AbstractAccessStrategy::Ptr accessStrategy);
    virtual void doCalc(int sampleCount) override;
};


#endif // CONVERTFLOATTOINT16_H
