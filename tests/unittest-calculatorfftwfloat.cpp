#include "calcfortest.h"
#include "buffers/buffertemplate.h"
#include "calc-components/calculators/calculatornull.h"
#include "calc-components/calculators/calculatorfftwfloat.h"
#include "calc-components/calculators/calculatorfftwinvfloat.h"
#include "calc-components/calculators/calculatormult.h"
#include "access-strategies/singlethreadedaccessstrategy.h"
#include <gtest/gtest.h>
#include <math.h>
#include <complex>
#include <memory>

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
    EXPECT_NO_THROW(CalculatorFftwFloat::createWithOutBuffer<SingleThreadedAccessStrategy>(calcFFtIn, buffSize));
    EXPECT_THROW(CalculatorFftwFloat::createWithOutBuffer<SingleThreadedAccessStrategy>(calcFFtIn, buffSize-1), std::out_of_range);
}

TEST(TEST_FFT_FLOAT, FFT_INV_BUFFER_SIZES) {
    constexpr int buffSize = 256;

    CALC_PTR(std::complex<float>) calcFFtVals = CalculatorNull<std::complex<float>>::createWithOutBuffer<SingleThreadedAccessStrategy>(buffSize);
    EXPECT_NO_THROW(CalculatorFftwInvFloat::createWithOutBuffer<SingleThreadedAccessStrategy>(calcFFtVals, buffSize));
    EXPECT_THROW(CalculatorFftwInvFloat::createWithOutBuffer<SingleThreadedAccessStrategy>(calcFFtVals, buffSize-1), std::out_of_range);
}

TEST(TEST_FFT_FLOAT, FFT_CONVERSION) {
    constexpr int buffSize = 256;

    CALC_PTR(float) calcFFtIn = CalculatorNull<float>::createWithOutBuffer<SingleThreadedAccessStrategy>(buffSize);
    BUFFER_PTR(float) buffTimeVals = calcFFtIn->getOutputBuffer();
    calcTestCurve(buffTimeVals);

    CALC_PTR(std::complex<float>) fftCalc = CalculatorFftwFloat::createWithOutBuffer<SingleThreadedAccessStrategy>(calcFFtIn, buffSize);
    fftCalc->tryStartCalc(buffSize);

    EXPECT_FLOAT_EQ(fftCalc->getOutputBuffer()->at(1).real(), ampOrder1 * float(buffSize) / 2);
    EXPECT_FLOAT_EQ(fftCalc->getOutputBuffer()->at(2).real(), ampOrder2 * float(buffSize) / 2);
}

TEST(TEST_FFT_FLOAT, FFT_CONVERSION_AND_INVERS) {
    constexpr int buffSize = 256;

    CALC_PTR(float) calcFFtIn = CalculatorNull<float>::createWithOutBuffer<SingleThreadedAccessStrategy>(buffSize);
    BUFFER_PTR(float) buffTimeVals = calcFFtIn->getOutputBuffer();
    calcTestCurve(buffTimeVals);

    CALC_PTR(std::complex<float>) fftCalc = CalculatorFftwFloat::createWithOutBuffer<SingleThreadedAccessStrategy>(calcFFtIn, buffSize);

    CALC_PTR(float) calcNormal = CalculatorNull<float>::createWithOutBuffer<SingleThreadedAccessStrategy>(1);
    calcNormal->getOutputBuffer()->at(0) = 1/float(buffSize);

    CALC_PTR(std::complex<float>) fftCalcNormalised =
            CalculatorMult2<std::complex<float>, float>::createWithOutBuffer<SingleThreadedAccessStrategy>(
                fftCalc,
                calcNormal,
                buffSize,
                true);

    CALC_PTR(float) fftCalcInvers = CalculatorFftwInvFloat::createWithOutBuffer<SingleThreadedAccessStrategy>(fftCalcNormalised, buffSize);
    fftCalcInvers->tryStartCalc(buffSize);

    BUFFER_PTR(float) curveBuff = fftCalcInvers->getOutputBuffer();
    for (int i(0); i<buffSize; i++) {
        EXPECT_NEAR(curveBuff->at(i), buffTimeVals->at(i), 1e-4);
    }
}
