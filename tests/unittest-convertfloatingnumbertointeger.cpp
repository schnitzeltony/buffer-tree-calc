#include "calc-components/calculators/convertfloatingnumbertointeger.h"
#include "buffers/buffertemplate.h"
#include "calc-components/calculators/calculatornull.h"
#include "access-strategies/singlethreadedaccessstrategy.h"
#include <gtest/gtest.h>
#include <limits>

TEST(TEST_CONVERT_FLOAT_TO_INT16, CONVERSION_DEFAULT_SCALE) {
    CALC_PTR(float) calcFloatInput = CalculatorNull<float>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(float) buffFloatInput = calcFloatInput->getOutputBuffer();

    CALC_PTR(int16_t) calcConvert = ConvertFloatingToInteger<float, int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(
                calcFloatInput,
                10);

    buffFloatInput->at(0) = -1.0;
    buffFloatInput->at(1) = 1.0;
    calcConvert->tryStartCalc(2);

    BUFFER_PTR(int16_t) buffIntegerOutput = calcConvert->getOutputBuffer();
    EXPECT_EQ(buffIntegerOutput->at(0), -std::numeric_limits<int16_t>::max());
    EXPECT_EQ(buffIntegerOutput->at(1), std::numeric_limits<int16_t>::max());
}

TEST(TEST_CONVERT_FLOAT_TO_INT32, CONVERSION_DEFAULT_SCALE) {
    CALC_PTR(float) calcFloatInput = CalculatorNull<float>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(float) buffFloatInput = calcFloatInput->getOutputBuffer();

    CALC_PTR(int32_t) calcConvert = ConvertFloatingToInteger<float, int32_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(
                calcFloatInput,
                10);

    buffFloatInput->at(0) = -1.0;
    buffFloatInput->at(1) = 1.0;
    calcConvert->tryStartCalc(2);

    BUFFER_PTR(int32_t) buffIntegerOutput = calcConvert->getOutputBuffer();
    EXPECT_EQ(buffIntegerOutput->at(0), -std::numeric_limits<int32_t>::max());
    EXPECT_EQ(buffIntegerOutput->at(1), std::numeric_limits<int32_t>::max());
}
