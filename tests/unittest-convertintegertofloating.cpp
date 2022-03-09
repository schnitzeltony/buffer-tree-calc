#include "calc-components/calculators/convertintegertofloating.h"
#include "buffers/buffertemplate.h"
#include "calc-components/calculators/calculatornull.h"
#include "access-strategies/singlethreadedaccessstrategy.h"
#include <gtest/gtest.h>


TEST(TEST_CONVERT_INT16_TO_FLOAT, CONVERSION_DEFAULT_SCALE) {
    CALC_PTR(int16_t) calcIntegerInput = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(int16_t) buffIntegerInput = calcIntegerInput->getOutputBuffer();

    CALC_PTR(float) calcConvert = ConvertIntegerToFloating<int16_t, float>::createWithOutBuffer<SingleThreadedAccessStrategy>(
                calcIntegerInput,
                10);

    buffIntegerInput->at(0) = -std::numeric_limits<int16_t>::max();
    buffIntegerInput->at(1) = std::numeric_limits<int16_t>::max();
    buffIntegerInput->at(2) = 0;

    calcConvert->tryStartCalc(2);

    BUFFER_PTR(float) buffFloatOutput = calcConvert->getOutputBuffer();
    EXPECT_FLOAT_EQ(buffFloatOutput->at(0), -1.0);
    EXPECT_FLOAT_EQ(buffFloatOutput->at(1), 1.0);
    EXPECT_FLOAT_EQ(buffFloatOutput->at(2), 0.0);
}
