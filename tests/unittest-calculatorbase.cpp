#include <gtest/gtest.h>
#include "calcfortest.h"
#include "buffers/buffertemplate.h"
#include "calc-components/calculators/calculatornull.h"
#include "calc-components/calculators/calculatordiff.h"
#include "access-strategies/singlethreadedaccessstrategy.h"

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

TEST(CALCULATORBASE, SINGLE_IN_OUT_SAMPLE_OFFSET_KEEP) {
    CALC_PTR(int16_t) inCalc = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) tstcalc = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc, 10);
    tstcalc->tryStartCalc(3);
    inCalc->keepSampleOffsetOnNextTryStart(true);
    tstcalc->prepareNextCalc();
    EXPECT_EQ(tstcalc->getSampleOffset(), 0);
    EXPECT_EQ(inCalc->getSampleOffset(), 3);

    tstcalc->tryStartCalc(3);
    inCalc->keepSampleOffsetOnNextTryStart(false);
    tstcalc->prepareNextCalc();
    EXPECT_EQ(tstcalc->getSampleOffset(), 0);
    EXPECT_EQ(inCalc->getSampleOffset(), 0);

    tstcalc->tryStartCalc(3);
    tstcalc->keepSampleOffsetOnNextTryStart(true);
    tstcalc->prepareNextCalc();
    EXPECT_EQ(tstcalc->getSampleOffset(), 3);
    EXPECT_EQ(inCalc->getSampleOffset(), 0);
}

TEST(CALCULATORBASE, SINGLE_IN_OUT_TRY_START_RETRY) {
    CALC_PTR(int16_t) inCalc = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) tstcalc = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc, 10);

    EXPECT_TRUE(tstcalc->tryStartCalc(3));

    EXPECT_FALSE(inCalc->tryStartCalc(3));
    EXPECT_FALSE(tstcalc->tryStartCalc(3));
}

TEST(CALCULATORBASE, SINGLE_IN_OUT_TRY_START_RESET_RETRY) {
    CALC_PTR(int16_t) inCalc = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) tstcalc = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc, 10);

    tstcalc->tryStartCalc(3);
    tstcalc->prepareNextCalc();
    EXPECT_TRUE(tstcalc->tryStartCalc(3));
}

TEST(CALCULATORBASE, SINGLE_IN_OUT_DONE) {
    CALC_PTR(int16_t) inCalc = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) tstcalc = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc, 10);

    EXPECT_FALSE(inCalc->isDone());
    EXPECT_FALSE(tstcalc->isDone());

    tstcalc->tryStartCalc(3);

    EXPECT_TRUE(inCalc->isDone());
    EXPECT_TRUE(tstcalc->isDone());
}

TEST(CALCULATORBASE, SINGLE_IN_OUT_DONE_RESET) {
    CALC_PTR(int16_t) inCalc = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) tstcalc = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc, 10);

    tstcalc->tryStartCalc(3);
    tstcalc->prepareNextCalc();

    EXPECT_FALSE(tstcalc->isDone());
    EXPECT_FALSE(inCalc->isDone());
}

TEST(CALCULATORBASE, DUAL_SECOND_UNTOUCHED) {
    CALC_PTR(int16_t) inCalc = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) tstcalc1 = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc, 10);
    CALC_PTR(int16_t) tstcalc2 = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(tstcalc1, 10);
    tstcalc1->tryStartCalc(3);
    EXPECT_EQ(tstcalc1->getSampleOffset(), 3);
    EXPECT_EQ(tstcalc2->getSampleOffset(), 0);
    EXPECT_EQ(inCalc->getSampleOffset(), 3);
}

TEST(CALCULATORBASE, DUAL_IN_OUT_COMPARE) {
    CALC_PTR(int16_t) inCalc = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    BUFFER_PTR(int16_t) inBuff = inCalc->getOutputBuffer();
    inBuff->at(0) = 1;
    inBuff->at(1) = 2;
    inBuff->at(2) = 3;
    inBuff->at(3) = 4;

    CALC_PTR(int16_t) tstcalc1 = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc, 10);
    BUFFER_PTR(int16_t) outBuff1 = tstcalc1->getOutputBuffer();
    outBuff1->at(3) = 0;

    CALC_PTR(int16_t) tstcalc2 = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(tstcalc1, 10);
    BUFFER_PTR(int16_t) outBuff2 = tstcalc2->getOutputBuffer();
    outBuff2->at(3) = 0;

    tstcalc2->tryStartCalc(3);

    EXPECT_EQ(inBuff->at(0), outBuff1->at(0));
    EXPECT_EQ(inBuff->at(1), outBuff1->at(1));
    EXPECT_EQ(inBuff->at(2), outBuff1->at(2));
    EXPECT_NE(inBuff->at(3), outBuff1->at(3));

    EXPECT_EQ(inBuff->at(0), outBuff2->at(0));
    EXPECT_EQ(inBuff->at(1), outBuff2->at(1));
    EXPECT_EQ(inBuff->at(2), outBuff2->at(2));
    EXPECT_NE(inBuff->at(3), outBuff2->at(3));
}

TEST(CALCULATORBASE, DUAL_IN_OUT_SAMPLE_OFFSET) {
    CALC_PTR(int16_t) inCalc = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) tstcalc1 = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc, 10);
    CALC_PTR(int16_t) tstcalc2 = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(tstcalc1, 10);
    tstcalc2->tryStartCalc(3);
    EXPECT_EQ(tstcalc1->getSampleOffset(), 3);
    EXPECT_EQ(tstcalc2->getSampleOffset(), 3);
    EXPECT_EQ(inCalc->getSampleOffset(), 3);
}

TEST(CALCULATORBASE, DUAL_IN_OUT_TRY_START_RETRY) {
    CALC_PTR(int16_t) inCalc = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) tstcalc1 = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc, 10);
    CALC_PTR(int16_t) tstcalc2 = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(tstcalc1, 10);

    EXPECT_TRUE(tstcalc2->tryStartCalc(3));

    EXPECT_FALSE(inCalc->tryStartCalc(3));
    EXPECT_FALSE(tstcalc1->tryStartCalc(3));
    EXPECT_FALSE(tstcalc2->tryStartCalc(3));
}

TEST(CALCULATORBASE, DUAL_IN_OUT_TRY_START_RESET_RETRY) {
    CALC_PTR(int16_t) inCalc = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) tstcalc1 = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc, 10);
    CALC_PTR(int16_t) tstcalc2 = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(tstcalc1, 10);

    tstcalc2->tryStartCalc(3);
    tstcalc2->prepareNextCalc();
    EXPECT_TRUE(tstcalc2->tryStartCalc(3));

    tstcalc2->prepareNextCalc();
    EXPECT_TRUE(tstcalc1->tryStartCalc(3));
    EXPECT_TRUE(tstcalc2->tryStartCalc(3));
}

TEST(CALCULATORBASE, DUAL_IN_OUT_DONE) {
    CALC_PTR(int16_t) inCalc = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) tstcalc1 = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc, 10);
    CALC_PTR(int16_t) tstcalc2 = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(tstcalc1, 10);

    EXPECT_FALSE(inCalc->isDone());
    EXPECT_FALSE(tstcalc1->isDone());
    EXPECT_FALSE(tstcalc2->isDone());

    tstcalc2->tryStartCalc(3);
    EXPECT_TRUE(inCalc->isDone());
    EXPECT_TRUE(tstcalc1->isDone());
    EXPECT_TRUE(tstcalc2->isDone());
}

TEST(CALCULATORBASE, DUAL_IN_OUT_DONE_RESET) {
    CALC_PTR(int16_t) inCalc = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) tstcalc1 = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc, 10);
    CALC_PTR(int16_t) tstcalc2 = CalcForTest<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(tstcalc1, 10);

    tstcalc2->tryStartCalc(3);
    tstcalc2->prepareNextCalc();

    EXPECT_FALSE(tstcalc1->isDone());
    EXPECT_FALSE(tstcalc2->isDone());
    EXPECT_FALSE(inCalc->isDone());

    tstcalc2->prepareNextCalc();
    tstcalc1->tryStartCalc(3);
    EXPECT_TRUE(inCalc->isDone());
    EXPECT_TRUE(tstcalc1->isDone());
    EXPECT_FALSE(tstcalc2->isDone());
}

// diff calc is our firs calculator with two inputs
TEST(CALCULATORBASE, SINGLE_TREE_SECOND_UNTOUCHED) {
    CALC_PTR(int16_t) inCalc1 = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) inCalc2 = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) calcDiff = CalculatorDiff<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc1, inCalc2, 10);

    inCalc1->tryStartCalc(3);
    inCalc2->tryStartCalc(3);
    EXPECT_EQ(inCalc1->getSampleOffset(), 3);
    EXPECT_EQ(inCalc2->getSampleOffset(), 3);
    EXPECT_EQ(calcDiff->getSampleOffset(), 0);
}

TEST(CALCULATORBASE, SINGLE_TREE_SAMPLE_OFFSET) {
    CALC_PTR(int16_t) inCalc1 = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) inCalc2 = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) calcDiff = CalculatorDiff<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc1, inCalc2, 10);
    calcDiff->tryStartCalc(3);
    EXPECT_EQ(inCalc1->getSampleOffset(), 3);
    EXPECT_EQ(inCalc2->getSampleOffset(), 3);
    EXPECT_EQ(calcDiff->getSampleOffset(), 3);
}

TEST(CALCULATORBASE, SINGLE_TREE_TRY_START_RETRY) {
    CALC_PTR(int16_t) inCalc1 = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) inCalc2 = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) calcDiff = CalculatorDiff<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc1, inCalc2, 10);
    EXPECT_TRUE(calcDiff->tryStartCalc(3));
    EXPECT_FALSE(inCalc1->tryStartCalc(3));
    EXPECT_FALSE(inCalc2->tryStartCalc(3));
    EXPECT_FALSE(calcDiff->tryStartCalc(3));
}

TEST(CALCULATORBASE, SINGLE_TREE_TRY_START_RESET_RETRY) {
    CALC_PTR(int16_t) inCalc1 = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) inCalc2 = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) calcDiff = CalculatorDiff<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc1, inCalc2, 10);

    calcDiff->tryStartCalc(3);
    calcDiff->prepareNextCalc();
    EXPECT_TRUE(calcDiff->tryStartCalc(3));

    calcDiff->prepareNextCalc();
    EXPECT_TRUE(inCalc1->tryStartCalc(3));
    EXPECT_TRUE(inCalc2->tryStartCalc(3));
}

TEST(CALCULATORBASE, SINGLE_TREE_DONE) {
    CALC_PTR(int16_t) inCalc1 = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) inCalc2 = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) calcDiff = CalculatorDiff<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc1, inCalc2, 10);

    EXPECT_FALSE(inCalc1->isDone());
    EXPECT_FALSE(inCalc2->isDone());
    EXPECT_FALSE(calcDiff->isDone());

    calcDiff->tryStartCalc(3);
    EXPECT_TRUE(inCalc1->isDone());
    EXPECT_TRUE(inCalc2->isDone());
    EXPECT_TRUE(calcDiff->isDone());
}

TEST(CALCULATORBASE, SINGLE_TREE_DONE_RESET) {
    CALC_PTR(int16_t) inCalc1 = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) inCalc2 = CalculatorNull<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(10);
    CALC_PTR(int16_t) calcDiff = CalculatorDiff<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(inCalc1, inCalc2, 10);

    calcDiff->tryStartCalc(3);
    calcDiff->prepareNextCalc();

    EXPECT_FALSE(inCalc1->isDone());
    EXPECT_FALSE(inCalc2->isDone());
    EXPECT_FALSE(calcDiff->isDone());

    calcDiff->prepareNextCalc();
    inCalc1->tryStartCalc(3);
    inCalc2->tryStartCalc(3);
    EXPECT_TRUE(inCalc1->isDone());
    EXPECT_TRUE(inCalc2->isDone());
    EXPECT_FALSE(calcDiff->isDone());
}
