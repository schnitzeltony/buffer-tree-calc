#include "convertint16tofloat.h"

ConvertInt16ToFloat::ConvertInt16ToFloat(AbstractAccessStrategy::Ptr accessStrategy,
                                         CALC_PTR(int16_t, float) input,
                                         BUFFER_PTR(float) output) :
    TCalcContainer<int16_t, float>({input}, output, accessStrategy)
{
}

bool ConvertInt16ToFloat::doCalc(int sampleCount)
{
    return true;
}
