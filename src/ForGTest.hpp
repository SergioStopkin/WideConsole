#pragma once

class TestingClass {
public:
    static int Func1();
    static int Func2();

    static int FuncInHeader()
    {
        return 3;
    }
};
