#include "calcfortest.h"
#include "buffers/buffertemplate.h"
#include "calc-components/calculators/calculatornull.h"
#include "calc-components/calculators/calculatorfftwfloat.h"
#include "access-strategies/singlethreadedaccessstrategy.h"
#include <gtest/gtest.h>
#include <math.h>

static constexpr float ampOrder1 = 1.0;
static constexpr float ampOrder2 = 0.5;

static void calcTestCurve(BUFFER_PTR(float) buff)
{
    int numSamples = buff->size();
    for(int i=0; i<numSamples; ++i) {
        buff->at(i) =
                ampOrder1 * cos(((1 * 2*M_PI * i) / numSamples) ) +
                ampOrder2 * cos(((2 * 2*M_PI * i) / numSamples));
    }
}

TEST(TEST_FFT_FLOAT, FFT_BUFFER_SIZES) {
    constexpr int buffSize = 256;

    CALC_PTR(float) calcFFtIn = CalculatorNull<float>::createWithOutBuffer<SingleThreadedAccessStrategy>(buffSize);
    EXPECT_NO_THROW(CalculatorFftwFloat::createWithOutBuffer<SingleThreadedAccessStrategy>(calcFFtIn, buffSize*2, false));
    EXPECT_THROW(CalculatorFftwFloat::createWithOutBuffer<SingleThreadedAccessStrategy>(calcFFtIn, buffSize*2-1, false), std::out_of_range);
}

TEST(TEST_FFT_FLOAT, FFT_INV_BUFFER_SIZES) {
    constexpr int buffSize = 256;

    CALC_PTR(float) calcFFtVals = CalculatorNull<float>::createWithOutBuffer<SingleThreadedAccessStrategy>(buffSize);
    EXPECT_NO_THROW(CalculatorFftwFloat::createWithOutBuffer<SingleThreadedAccessStrategy>(calcFFtVals, buffSize/2, true));
    EXPECT_THROW(CalculatorFftwFloat::createWithOutBuffer<SingleThreadedAccessStrategy>(calcFFtVals, buffSize/2-1, true), std::out_of_range);
}

TEST(TEST_FFT_FLOAT, FFT_CONVERSION) {
    constexpr int buffSize = 256;

    CALC_PTR(float) calcFFtIn = CalculatorNull<float>::createWithOutBuffer<SingleThreadedAccessStrategy>(buffSize);
    BUFFER_PTR(float) buffTimeVals = calcFFtIn->getOutputBuffer();
    calcTestCurve(buffTimeVals);

    CALC_PTR_FFTW(float) fftCalc = CalculatorFftwFloat::createWithOutBuffer<SingleThreadedAccessStrategy>(calcFFtIn, buffSize*2, false);
    fftCalc->tryStartCalc(0);

    BUFFER_PTR(float) fftBuff = fftCalc->getOutputBuffer();
    EXPECT_FLOAT_EQ(fftCalc->getFftRe(1), ampOrder1 * float(buffSize) / 2);
    EXPECT_FLOAT_EQ(fftCalc->getFftRe(2), ampOrder2 * float(buffSize) / 2);
}
