#include "ForGTest.hpp"

#include <gtest/gtest.h>

TEST(TestOne, TestOne)
{
    EXPECT_EQ(TestingClass::Func1(), 1);
    //    EXPECT_EQ(TestingClass::Func2(), 2);
    EXPECT_EQ(TestingClass::FuncInHeader(), 3);
}
