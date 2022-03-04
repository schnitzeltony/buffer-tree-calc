#include "calculatorfftfloat.h"

CalculatorFftFloat::CalculatorFftFloat(AbstractAccessStrategy::Ptr accessStrategy,
                                   CALC_PTR(float, float) input,
                                   BUFFER_PTR(float) output) :
    TCalcContainer<float, float>({input}, output, accessStrategy)
{
}

bool CalculatorFftFloat::doCalc(int sampleCount)
{
    return true;
}

void CalculatorFftFloat::doInit()
{

}

void CalculatorFftFloat::doDestroy()
{

}
