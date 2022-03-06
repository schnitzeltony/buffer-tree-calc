#include <gtest/gtest.h>
#include "access-strategies/singlethreadedaccessstrategy.h"

TEST(SINGLE_THREAD_ACESS, MAKE_BUSY_TWICE) {
    SingleThreadedAccessStrategy st;
    EXPECT_TRUE(st.tryMakeBusy());
    EXPECT_FALSE(st.tryMakeBusy());
}

TEST(SINGLE_THREAD_ACESS, SET_DONE_ONCE) {
    SingleThreadedAccessStrategy st;
    EXPECT_FALSE(st.isDone());
    st.setDone();
    EXPECT_TRUE(st.isDone());
}

TEST(SINGLE_THREAD_ACESS, RESET) {
    SingleThreadedAccessStrategy st;
    EXPECT_TRUE(st.tryMakeBusy());
    EXPECT_FALSE(st.tryMakeBusy());
    st.setDone();
    EXPECT_TRUE(st.isDone());

    st.reset();
    EXPECT_FALSE(st.isDone());
    EXPECT_TRUE(st.tryMakeBusy());
}

TEST(SINGLE_THREAD_ACESS, DOUBLE_SETDONE_THROW) {
    SingleThreadedAccessStrategy st;
    EXPECT_NO_THROW(st.setDone());
    EXPECT_THROW(st.setDone(), double_done_exception);
}

TEST(SINGLE_THREAD_ACESS, DOUBLE_SETDONE_WITH_RESET) {
    SingleThreadedAccessStrategy st;
    EXPECT_NO_THROW(st.setDone());
    st.reset();
    EXPECT_NO_THROW(st.setDone());
    EXPECT_THROW(st.setDone(), double_done_exception);
}
