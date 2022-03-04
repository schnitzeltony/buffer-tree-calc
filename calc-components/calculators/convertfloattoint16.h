#ifndef CONVERTFLOATTOINT16_H
#define CONVERTFLOATTOINT16_H

#include "buffers/buffertemplate.h"
#include "calc-components/tcalculator.h"

class ConvertFloatToInt16 : public TCalculator<float, int16_t>
{
public:
    ConvertFloatToInt16(AbstractAccessStrategy::Ptr accessStrategy,
                        CALC_PTR(float, int16_t) input,
                        BUFFER_PTR(int16_t) output);
    virtual bool doCalc(int sampleCount) override;
};


#endif // CONVERTFLOATTOINT16_H
