#include <gtest/gtest.h>

#include "ForGTest.hpp"

TEST(TestOne, TestOne)
{
    EXPECT_EQ(TestingClass::Func1(), 1);
    //    EXPECT_EQ(TestingClass::Func2(), 2);
    EXPECT_EQ(TestingClass::FuncInHeader(), 3);
}
