#include "convertint16tofloat.h"

ConvertInt16ToFloat::ConvertInt16ToFloat(AbstractAccessStrategy::Ptr accessStrategy,
                                         CALC_PTR(int16_t, float) input,
                                         BUFFER_PTR(float) output) :
    TCalculator<int16_t, float>({input}, output, accessStrategy)
{
}

bool ConvertInt16ToFloat::doCalc(int sampleCount)
{
    return true;
}



ConvertFloatToInt16::ConvertFloatToInt16(AbstractAccessStrategy::Ptr accessStrategy,
                                         CALC_PTR(float, int16_t) input,
                                         BUFFER_PTR(int16_t) output) :
    TCalculator<float, int16_t>({input}, output, accessStrategy)
{
}

bool ConvertFloatToInt16::doCalc(int sampleCount)
{
    return true;
}
