#include <gtest/gtest.h>
#include "calcfortest.h"
#include "buffers/buffertemplate.h"
#include "calc-components/calculators/calculatornull.h"
#include "calc-components/calculators/calculatordiff.h"
#include "access-strategies/singlethreadedaccessstrategy.h"

TEST(TEST_DIFF_CALC, SUBSTRACT_VALID_INT16) {
    CALC_PTR(int16_t) calcMinuent = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(int16_t) buffMinuent = calcMinuent->getOutputBuffer();
    CALC_PTR(int16_t) calcSubtrahent = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(int16_t) buffSubtrahent = calcSubtrahent->getOutputBuffer();

    CALC_PTR(int16_t) calcDiff = CalculatorDiff<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(
                calcMinuent,
                calcSubtrahent,
                10);

    buffSubtrahent->at(0) = 10;
    buffMinuent->at(0) = 5;
    buffSubtrahent->at(1) = 8;
    buffMinuent->at(1) = 4;
    calcDiff->tryStartCalc(2);

    BUFFER_PTR(int16_t) diffBuff = calcDiff->getOutputBuffer();
    EXPECT_EQ(buffMinuent->at(0) - buffSubtrahent->at(0), diffBuff->at(0));
    EXPECT_EQ(buffMinuent->at(1) - buffSubtrahent->at(1), diffBuff->at(1));
}

TEST(TEST_DIFF_CALC, SUBSTRACT_VALID_FLOAT) {
    CALC_PTR(float) calcMinuent = CalculatorNull<float>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(float) buffMinuent = calcMinuent->getOutputBuffer();
    CALC_PTR(float) calcSubtrahent = CalculatorNull<float>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(float) buffSubtrahent = calcSubtrahent->getOutputBuffer();

    CALC_PTR(float) calcDiff = CalculatorDiff<float>::createWithOutBuffer<SingleThreadedAccessStrategy>(
                calcMinuent,
                calcSubtrahent,
                10);

    buffSubtrahent->at(0) = 10;
    buffMinuent->at(0) = 5;
    buffSubtrahent->at(1) = 8;
    buffMinuent->at(1) = 4;
    calcDiff->tryStartCalc(2);

    BUFFER_PTR(float) diffBuff = calcDiff->getOutputBuffer();
    EXPECT_FLOAT_EQ(buffMinuent->at(0) - buffSubtrahent->at(0), diffBuff->at(0));
    EXPECT_FLOAT_EQ(buffMinuent->at(1) - buffSubtrahent->at(1), diffBuff->at(1));
}

TEST(TEST_DIFF_CALC, SUBSTRACT_VALID_DOUBLE) {
    CALC_PTR(double) calcMinuent = CalculatorNull<double>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(double) buffMinuent = calcMinuent->getOutputBuffer();
    CALC_PTR(double) calcSubtrahent = CalculatorNull<double>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(double) buffSubtrahent = calcSubtrahent->getOutputBuffer();

    CALC_PTR(double) calcDiff = CalculatorDiff<double>::createWithOutBuffer<SingleThreadedAccessStrategy>(
                calcMinuent,
                calcSubtrahent,
                10);

    buffSubtrahent->at(0) = 10;
    buffMinuent->at(0) = 5;
    buffSubtrahent->at(1) = 8;
    buffMinuent->at(1) = 4;
    calcDiff->tryStartCalc(2);

    BUFFER_PTR(double) diffBuff = calcDiff->getOutputBuffer();
    EXPECT_DOUBLE_EQ(buffMinuent->at(0) - buffSubtrahent->at(0), diffBuff->at(0));
    EXPECT_DOUBLE_EQ(buffMinuent->at(1) - buffSubtrahent->at(1), diffBuff->at(1));
}

TEST(TEST_DIFF_CALC, SUBSTRACT_SCALAR_VALID_INT16) {
    CALC_PTR(int16_t) calcMinuent = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(int16_t) buffMinuent = calcMinuent->getOutputBuffer();
    CALC_PTR(int16_t) calcSubtrahent = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(1);
    BUFFER_PTR(int16_t) buffSubtrahent = calcSubtrahent->getOutputBuffer();

    CALC_PTR(int16_t) calcDiff = CalculatorDiff<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(
                calcMinuent,
                calcSubtrahent,
                10,
                true);

    buffSubtrahent->at(0) = 1;
    buffMinuent->at(0) = 1;
    buffMinuent->at(1) = 2;
    calcDiff->tryStartCalc(2);

    BUFFER_PTR(int16_t) diffBuff = calcDiff->getOutputBuffer();
    EXPECT_EQ(buffMinuent->at(0) - buffSubtrahent->at(0), diffBuff->at(0));
    EXPECT_EQ(buffMinuent->at(1) - buffSubtrahent->at(0), diffBuff->at(1));
}

