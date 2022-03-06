#include <gtest/gtest.h>
#include "buffers/buffertemplate.h"

TEST(TEST_DIFF_CALC, SUBSTRACT_VALID_INT16) {
    BUFFER_PTR(int16_t) buffMinuent = std::make_shared<BufferTemplate<int16_t>>(2);
    BUFFER_PTR(int16_t) buffSubtrahent = std::make_shared<BufferTemplate<int16_t>>(2);

    buffSubtrahent->at(0) = 10;
    buffMinuent->at(0) = 5;
    buffSubtrahent->at(1) = 8;
    buffMinuent->at(1) = 4;

    BufferTemplate<int16_t> buffDifference(2);
}
