#ifndef CALCULATORFFTFLOAT_H
#define CALCULATORFFTFLOAT_H

#include "buffers/buffertemplate.h"
#include "calc-components/calculatorbase.h"

class CalculatorFftFloat : public CalculatorBase<float>
{
public:
    CalculatorFftFloat(AbstractAccessStrategy::Ptr accessStrategy,
                       CALC_PTR(float) input,
                       BUFFER_PTR(float) output);
    virtual void doCalc(int sampleCount) override;

    template <typename ACCESS_STRATEGY>
    static std::shared_ptr<CalculatorFftFloat> createWithOutBuffer(int bufferSize)
    {
        return std::make_shared<CalculatorFftFloat>(std::make_shared<BufferTemplate<float>>(bufferSize),
                                                    createAccessStrategy<ACCESS_STRATEGY>());
    }
};

#endif // CALCULATORFFTFLOAT_H
