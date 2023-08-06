#include "wideconsole/tool/intsize.h"

#include <gtest/gtest.h>

using namespace WideConsole;

TEST(TestIntSize, TestIntSize)
{
    EXPECT_EQ(intSize(3.3), 1);
    EXPECT_EQ(intSize(0.3), 1);
    EXPECT_EQ(intSize(33), 2);
    EXPECT_EQ(intSize(33.3), 2);
    EXPECT_EQ(intSize(33333.3), 5);
}
