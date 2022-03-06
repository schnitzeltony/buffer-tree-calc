#include <gtest/gtest.h>
#include "calcfortest.h"
#include "buffers/buffertemplate.h"
#include "calc-components/calculators/calculatornull.h"
#include "access-strategies/singlethreadedaccessstrategy.h"
#include "calcfortest.h"

TEST(CALCULATORBASE, SINGLE_IN_OUT_COMPARE) {
    CALC_PTR(int16_t) inCalc = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(int16_t) inBuff = inCalc->getOutputBuffer();
    inBuff->at(0) = 1;
    inBuff->at(1) = 2;
    inBuff->at(2) = 3;
    inBuff->at(3) = 4;

    CALC_PTR(int16_t) tstcalc = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc, 10);
    BUFFER_PTR(int16_t) outBuff = tstcalc->getOutputBuffer();
    outBuff->at(3) = 0;

    tstcalc->tryStartCalc(3);

    EXPECT_EQ(inBuff->at(0), outBuff->at(0));
    EXPECT_EQ(inBuff->at(1), outBuff->at(1));
    EXPECT_EQ(inBuff->at(2), outBuff->at(2));
    EXPECT_NE(inBuff->at(3), outBuff->at(3));
}

TEST(CALCULATORBASE, SINGLE_IN_OUT_SAMPLE_OFFSET) {
    CALC_PTR(int16_t) inCalc = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) tstcalc = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc, 10);
    tstcalc->tryStartCalc(3);
    EXPECT_EQ(tstcalc->getSampleOffset(), 3);
    EXPECT_EQ(inCalc->getSampleOffset(), 3);
}

TEST(CALCULATORBASE, SINGLE_IN_OUT_TRY_START_RET) {
    CALC_PTR(int16_t) inCalc = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) tstcalc = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc, 10);

    EXPECT_TRUE(tstcalc->tryStartCalc(3));

    EXPECT_FALSE(inCalc->tryStartCalc(3));
    EXPECT_FALSE(tstcalc->tryStartCalc(3));
}


TEST(CALCULATORBASE, SINGLE_IN_OUT_DONE) {
    CALC_PTR(int16_t) inCalc = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) tstcalc = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc, 10);

    EXPECT_FALSE(tstcalc->isDone());
    EXPECT_FALSE(tstcalc->isDone());

    tstcalc->tryStartCalc(3);

    EXPECT_TRUE(tstcalc->isDone());
    EXPECT_TRUE(inCalc->isDone());
}

TEST(CALCULATORBASE, SINGLE_IN_OUT_DONE_RESET) {
    CALC_PTR(int16_t) inCalc = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) tstcalc = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc, 10);

    tstcalc->tryStartCalc(3);
    tstcalc.reset();

    EXPECT_FALSE(tstcalc->isDone());
    EXPECT_FALSE(inCalc->isDone());
}
