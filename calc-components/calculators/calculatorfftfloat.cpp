#include "calculatorfftfloat.h"

CalculatorFftFloat::CalculatorFftFloat(AbstractAccessStrategy::Ptr accessStrategy,
                                       CALC_PTR(float) input,
                                       BUFFER_PTR(float) output) :
    CalculatorBase<float>({input}, output, accessStrategy)
{
}

void CalculatorFftFloat::doCalc(int sampleCount)
{
}

void CalculatorFftFloat::init()
{

}

void CalculatorFftFloat::destroy()
{

}
