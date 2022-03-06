#include <gtest/gtest.h>
#include "buffers/buffertemplate.h"

TEST(BUFFERTEMPLATE, SIZE) {
    constexpr std::size_t buffSize1 = 1;
    BufferTemplate<int16_t> buff1(buffSize1);
    EXPECT_EQ(buff1.size(), buffSize1);

    constexpr std::size_t buffSize2 = 2;
    BufferTemplate<float> buff2(buffSize2);
    EXPECT_EQ(buff2.size(), buffSize2);

    constexpr std::size_t buffSize3 = 3;
    BufferTemplate<double> buff3(buffSize3);
    EXPECT_EQ(buff3.size(), buffSize3);
}

TEST(BUFFERTEMPLATE, SHARED_POINTER_ACCESS) {
    constexpr std::size_t buffSize1 = 1;
    BUFFER_PTR(int16_t) buff1 = std::make_shared<BufferTemplate<int16_t>>(buffSize1);
    EXPECT_EQ(buff1->size(), buffSize1);
}

TEST(BUFFERTEMPLATE, SET_VALUES) {
    BufferTemplate<int16_t> buff(2);

    buff.at(0) = 1;
    EXPECT_EQ(buff.at(0), 1);

    buff.at(0) = 2;
    EXPECT_EQ(buff.at(0), 2);

    buff.at(1) = 3;
    EXPECT_EQ(buff.at(1), 3);
}

TEST(BUFFERTEMPLATE, BUFFER_ACCESS) {
    BufferTemplate<int16_t> buff(2);

    int16_t *ptr = buff.data();
    ptr[0] = 1;
    EXPECT_EQ(buff.at(0), 1);

    ptr[0] = 2;
    EXPECT_EQ(buff.at(0), 2);

    ptr[1] = 3;
    EXPECT_EQ(buff.at(1), 3);
}

TEST(BUFFERTEMPLATE, OUT_OF_BOUNDS_ACCESS) {
    BufferTemplate<int16_t> buff1(1);
    EXPECT_NO_THROW(buff1.at(0) = 0);
    EXPECT_THROW(buff1.at(-1) = 0, std::out_of_range);
    EXPECT_THROW(buff1.at(1) = 0, std::out_of_range);

    BufferTemplate<int16_t> buff2(2);
    EXPECT_NO_THROW(buff2.at(0) = 0);
    EXPECT_NO_THROW(buff2.at(1) = 0);
    EXPECT_THROW(buff2.at(2) = 0, std::out_of_range);
}
