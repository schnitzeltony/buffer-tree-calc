#include "convertfloattoint16.h"

ConvertFloatToInt16::ConvertFloatToInt16(CALC_PTR(float) input,
                                         BUFFER_PTR(int16_t) output,
                                         AbstractAccessStrategy::Ptr accessStrategy) :
    CalculatorBase<int16_t>({input}, output, accessStrategy)
{
}

void ConvertFloatToInt16::doCalc(int sampleCount)
{
}
