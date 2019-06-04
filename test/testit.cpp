#include <gtest/gtest.h>

TEST(SomeTest, TestIt) {
    EXPECT_TRUE(1);
}

TEST(SomeTest, TestPass) {
    EXPECT_TRUE(1);
}

TEST(SomeTest, TestFail) {
    EXPECT_TRUE(0);
}