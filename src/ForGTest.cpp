#include <iostream>

#include "ForGTest.hpp"

int TestingClass::Func1()
{
    return 1;
}

// cppcheck-suppress unusedFunction
int TestingClass::Func2()
{
    return 2;
}
