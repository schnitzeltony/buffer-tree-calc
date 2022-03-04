#ifndef CALCULATORFFTFLOAT_H
#define CALCULATORFFTFLOAT_H

#include "buffers/buffertemplate.h"
#include "calc-components/tcalccontainer.h"

class CalculatorFftFloat : public TCalcContainer<float, float>
{
public:
    CalculatorFftFloat(AbstractAccessStrategy::Ptr accessStrategy,
                       CALC_PTR(float, float) input,
                       BUFFER_PTR(float) output);
    virtual bool doCalc(int sampleCount) override;
    virtual void doInit() override;
    virtual void doDestroy() override;
};

#endif // CALCULATORFFTFLOAT_H
