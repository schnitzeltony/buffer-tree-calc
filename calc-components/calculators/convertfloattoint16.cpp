#include "convertfloattoint16.h"

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
