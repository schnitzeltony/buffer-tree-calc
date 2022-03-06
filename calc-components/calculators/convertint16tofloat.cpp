#include "convertint16tofloat.h"

ConvertInt16ToFloat::ConvertInt16ToFloat(CALC_PTR(int16_t) input,
                                         BUFFER_PTR(float) output,
                                         AbstractAccessStrategy::Ptr accessStrategy) :
    CalculatorBase<float>({input}, output, accessStrategy)
{
}

void ConvertInt16ToFloat::doCalc(int sampleCount)
{
}
