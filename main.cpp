#include <iostream>
#include "Expression.hpp"
#include <gtest/gtest.h>

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    Eval::Expression ex;
    try
    {
        std::cin >> ex;
        ex.toPostfix();
        std::cout << ex.eval();
    }
    catch(const char* ex)
    {
        std::cout << ex;
    }

    system("pause>nul");
    return 0;
}