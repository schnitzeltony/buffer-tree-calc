#include "calcfortest.h"
#include "buffers/buffertemplate.h"
#include "calc-components/calculators/calculatornull.h"
#include "calc-components/calculators/calculatormult.h"
#include "access-strategies/singlethreadedaccessstrategy.h"
#include <gtest/gtest.h>
#include <complex>

TEST(TEST_MULT_CALC, VALID_INT16) {
    CALC_PTR(int16_t) calcBuff1 = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(int16_t) buffBuff1 = calcBuff1->getOutputBuffer();
    CALC_PTR(int16_t) calcBuff2 = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(int16_t) buffBuff2 = calcBuff2->getOutputBuffer();

    CALC_PTR(int16_t) calcMult = CalculatorMult<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(
                calcBuff1,
                calcBuff2,
                10);

    buffBuff1->at(0) = 10;
    buffBuff2->at(0) = 5;
    buffBuff1->at(1) = 8;
    buffBuff2->at(1) = 4;
    calcMult->tryStartCalc(2);

    BUFFER_PTR(int16_t) multBuff = calcMult->getOutputBuffer();
    EXPECT_EQ(buffBuff1->at(0) * buffBuff2->at(0), multBuff->at(0));
    EXPECT_EQ(buffBuff1->at(1) * buffBuff2->at(1), multBuff->at(1));
}

TEST(TEST_MULT_CALC, VALID_FLOAT) {
    CALC_PTR(float) calcBuff1 = CalculatorNull<float>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(float) buffBuff1 = calcBuff1->getOutputBuffer();
    CALC_PTR(float) calcBuff2 = CalculatorNull<float>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(float) buffBuff2 = calcBuff2->getOutputBuffer();

    CALC_PTR(float) calcMult = CalculatorMult<float>::createWithOutBuffer<SingleThreadedAccessStrategy>(
                calcBuff1,
                calcBuff2,
                10);

    buffBuff1->at(0) = 10;
    buffBuff2->at(0) = 5;
    buffBuff1->at(1) = 8;
    buffBuff2->at(1) = 4;
    calcMult->tryStartCalc(2);

    BUFFER_PTR(float) multBuff = calcMult->getOutputBuffer();
    EXPECT_FLOAT_EQ(buffBuff1->at(0) * buffBuff2->at(0), multBuff->at(0));
    EXPECT_FLOAT_EQ(buffBuff1->at(1) * buffBuff2->at(1), multBuff->at(1));
}

TEST(TEST_MULT_CALC, VALID_DOUBLE) {
    CALC_PTR(double) calcBuff1 = CalculatorNull<double>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(double) buffBuff1 = calcBuff1->getOutputBuffer();
    CALC_PTR(double) calcBuff2 = CalculatorNull<double>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(double) buffBuff2 = calcBuff2->getOutputBuffer();

    CALC_PTR(double) calcMult = CalculatorMult<double>::createWithOutBuffer<SingleThreadedAccessStrategy>(
                calcBuff1,
                calcBuff2,
                10);

    buffBuff1->at(0) = 10;
    buffBuff2->at(0) = 5;
    buffBuff1->at(1) = 8;
    buffBuff2->at(1) = 4;
    calcMult->tryStartCalc(2);

    BUFFER_PTR(double) multBuff = calcMult->getOutputBuffer();
    EXPECT_DOUBLE_EQ(buffBuff1->at(0) * buffBuff2->at(0), multBuff->at(0));
    EXPECT_DOUBLE_EQ(buffBuff1->at(1) * buffBuff2->at(1), multBuff->at(1));
}

TEST(TEST_MULT_CALC, SCALAR_VALID_INT16) {
    CALC_PTR(int16_t) calcBuff1 = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(int16_t) buffBuff1 = calcBuff1->getOutputBuffer();
    CALC_PTR(int16_t) calcBuff2 = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(1);
    BUFFER_PTR(int16_t) buffBuff2 = calcBuff2->getOutputBuffer();

    CALC_PTR(int16_t) calcMult = CalculatorMult<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(
                calcBuff1,
                calcBuff2,
                10,
                true);

    buffBuff1->at(0) = 1;
    buffBuff1->at(1) = 2;
    buffBuff2->at(0) = 1;
    calcMult->tryStartCalc(2);

    BUFFER_PTR(int16_t) multBuff = calcMult->getOutputBuffer();
    EXPECT_EQ(buffBuff1->at(0) * buffBuff2->at(0), multBuff->at(0));
    EXPECT_EQ(buffBuff1->at(1) * buffBuff2->at(0), multBuff->at(1));
}


TEST(TEST_MULT_CALC, VALID_FLOAT_COMPLEX_AND_VAL) {
    CALC_PTR(std::complex<float>) calcBuff1 = CalculatorNull<std::complex<float>>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(std::complex<float>) buffBuff1 = calcBuff1->getOutputBuffer();
    CALC_PTR(float) calcBuff2 = CalculatorNull<float>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(float) buffBuff2 = calcBuff2->getOutputBuffer();

    CALC_PTR(std::complex<float>) calcMult = CalculatorMult2<std::complex<float>, float>::createWithOutBuffer<SingleThreadedAccessStrategy>(
                calcBuff1,
                calcBuff2,
                10);

    buffBuff1->at(0).real(10);
    buffBuff1->at(0).imag(20);
    buffBuff1->at(1).real(8);
    buffBuff1->at(1).imag(16);

    buffBuff2->at(0) = 5;
    buffBuff2->at(1) = 4;
    calcMult->tryStartCalc(2);

    BUFFER_PTR(std::complex<float>) multBuff = calcMult->getOutputBuffer();
    EXPECT_FLOAT_EQ(buffBuff1->at(0).real() * buffBuff2->at(0), multBuff->at(0).real());
    EXPECT_FLOAT_EQ(buffBuff1->at(0).imag() * buffBuff2->at(0), multBuff->at(0).imag());
    EXPECT_FLOAT_EQ(buffBuff1->at(1).real() * buffBuff2->at(1), multBuff->at(1).real());
    EXPECT_FLOAT_EQ(buffBuff1->at(1).imag() * buffBuff2->at(1), multBuff->at(1).imag());
}

