#include <iostream>
#include "Expression.hpp"
#include <gtest/gtest.h>

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    Eval::Expression ex;
    std::cout << "\n\n\n";
    try
    {
        std::cin >> ex;
        ex.toPostfix();
        std::cout << "\nPostfix notation: ";
        while(not ex.backup.empty())
        {
            if(ex.backup.front() >= 0)
                std::cout << ex.backup.front() << ' ';
            else
            {
                switch(ex.backup.front())
                {
                    case -1:
                        std::cout << "+ ";
                        break;
                    case -2:
                        std::cout << "- ";
                        break;
                    case -3:
                        std::cout << "* ";
                        break;
                    case -4:
                        std::cout << "/ ";
                        break;
                    default:
                        break;
                }
            }
            ex.backup.pop();
        }
        std::cout << "\n\nResult: " << ex.eval();
    }
    catch(const char* ex)
    {
        std::cout << ex;
    }

    system("pause>nul");
    return 0;
}