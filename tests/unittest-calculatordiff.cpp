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
    BUFFER_PTR(int16_t) buffSubtrahent = calcMinuent->getOutputBuffer();

    CALC_PTR(int16_t) calcDiff = CalculatorDiff<int16_t>::createWithOutBuffer<SingleThreadedAccessStrategy>(
                calcMinuent,
                calcSubtrahent,
                10);

    buffSubtrahent->at(0) = 10;
    buffMinuent->at(0) = 5;
    buffSubtrahent->at(1) = 8;
    buffMinuent->at(1) = 4;

}
