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

    buffIntegerInput->at(0) = 0;
    buffIntegerInput->at(1) = -std::numeric_limits<int16_t>::max();
    buffIntegerInput->at(2) = std::numeric_limits<int16_t>::max();

    calcConvert->tryStartCalc(3);

    BUFFER_PTR(float) buffFloatOutput = calcConvert->getOutputBuffer();
    EXPECT_FLOAT_EQ(buffFloatOutput->at(0), 0.0);
    EXPECT_FLOAT_EQ(buffFloatOutput->at(1), -1.0);
    EXPECT_FLOAT_EQ(buffFloatOutput->at(2), 1.0);
}

TEST(TEST_CONVERT_INT16_TO_FLOAT, CONVERSION_SCALED_BY_ZERO) {
    CALC_PTR(int16_t) calcIntegerInput = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(int16_t) buffIntegerInput = calcIntegerInput->getOutputBuffer();

    BUFFER_PTR(float) buffFloatOutput = std::make_shared<BufferTemplate<float>>(10);
    AbstractAccessStrategy::Ptr accessStrategy = createAccessStrategy<SingleThreadedAccessStrategy>();
    //ConvertIntegerToFloating<int16_t, float> calcConvert(calcIntegerInput, buffFloatOutput, accessStrategy, 0.0);
}

TEST(TEST_CONVERT_INT32_TO_FLOAT, CONVERSION_DEFAULT_SCALE) {
    CALC_PTR(int32_t) calcIntegerInput = CalculatorNull<int32_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(int32_t) buffIntegerInput = calcIntegerInput->getOutputBuffer();

    CALC_PTR(float) calcConvert = ConvertIntegerToFloating<int32_t, float>::createWithOutBuffer<SingleThreadedAccessStrategy>(
                calcIntegerInput,
                10);

    buffIntegerInput->at(0) = 0;
    buffIntegerInput->at(1) = -std::numeric_limits<int32_t>::max();
    buffIntegerInput->at(2) = std::numeric_limits<int32_t>::max();

    calcConvert->tryStartCalc(3);

    BUFFER_PTR(float) buffFloatOutput = calcConvert->getOutputBuffer();
    EXPECT_FLOAT_EQ(buffFloatOutput->at(0), 0.0);
    EXPECT_FLOAT_EQ(buffFloatOutput->at(1), -1.0);
    EXPECT_FLOAT_EQ(buffFloatOutput->at(2), 1.0);
}

TEST(TEST_CONVERT_INT16_TO_DOUBLE, CONVERSION_DEFAULT_SCALE) {
    CALC_PTR(int16_t) calcIntegerInput = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(int16_t) buffIntegerInput = calcIntegerInput->getOutputBuffer();

    CALC_PTR(double) calcConvert = ConvertIntegerToFloating<int16_t, double>::createWithOutBuffer<SingleThreadedAccessStrategy>(
                calcIntegerInput,
                10);

    buffIntegerInput->at(0) = 0;
    buffIntegerInput->at(1) = -std::numeric_limits<int16_t>::max();
    buffIntegerInput->at(2) = std::numeric_limits<int16_t>::max();

    calcConvert->tryStartCalc(3);

    BUFFER_PTR(double) buffFloatOutput = calcConvert->getOutputBuffer();
    EXPECT_FLOAT_EQ(buffFloatOutput->at(0), 0.0);
    EXPECT_FLOAT_EQ(buffFloatOutput->at(1), -1.0);
    EXPECT_FLOAT_EQ(buffFloatOutput->at(2), 1.0);
}

TEST(TEST_CONVERT_INT32_TO_DOUBLE, CONVERSION_DEFAULT_SCALE) {
    CALC_PTR(int32_t) calcIntegerInput = CalculatorNull<int32_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(int32_t) buffIntegerInput = calcIntegerInput->getOutputBuffer();

    CALC_PTR(double) calcConvert = ConvertIntegerToFloating<int32_t, double>::createWithOutBuffer<SingleThreadedAccessStrategy>(
                calcIntegerInput,
                10);

    buffIntegerInput->at(0) = 0;
    buffIntegerInput->at(1) = -std::numeric_limits<int32_t>::max();
    buffIntegerInput->at(2) = std::numeric_limits<int32_t>::max();

    calcConvert->tryStartCalc(3);

    BUFFER_PTR(double) buffFloatOutput = calcConvert->getOutputBuffer();
    EXPECT_FLOAT_EQ(buffFloatOutput->at(0), 0.0);
    EXPECT_FLOAT_EQ(buffFloatOutput->at(1), -1.0);
    EXPECT_FLOAT_EQ(buffFloatOutput->at(2), 1.0);
}
