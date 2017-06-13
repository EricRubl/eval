//
// Created by Eric on 13.06.2017.
//

#include <gtest/gtest.h>
#include "../DynamicStack.hpp"
#include "../DynamicQueue.hpp"
//#include "../Expression.hpp"

TEST(DynamicStack, TestConstructorDestructor)
{
    Eval::DynamicStack<int> a;
}

TEST(DynamicStack, TestEmpty)
{
    Eval::DynamicStack<int> a;
    EXPECT_TRUE(a.empty());
}

TEST(DynamicStack, TestPush)
{
    Eval::DynamicStack<int> a;
    a.push(1);
    EXPECT_EQ(a.empty(), false);
}

TEST(DynamicStack, TestTop)
{
    Eval::DynamicStack<int> a;
    a.push(1);
    EXPECT_EQ(a.top(), 1);
}

TEST(DynamicStack, TestPop)
{
    Eval::DynamicStack<int> a;
    a.push(1);
    a.pop();
    ASSERT_ANY_THROW(a.top());
}

TEST(DynamicQueue, ConstructorDestructor)
{
    Eval::DynamicQueue<int> a;
}

TEST(DynamicQueue, TestEmpty)
{
    Eval::DynamicQueue<int> a;
    EXPECT_TRUE(a.empty());
}

TEST(DynamicQueue, TestPush)
{
    Eval::DynamicQueue<int> a;
    a.push(1);
    EXPECT_FALSE(a.empty());
}

TEST(DynamicQueue, TestFront)
{
    Eval::DynamicQueue<int> a;
    a.push(1);
    a.push(2);
    EXPECT_EQ(a.front(), 1);
}

TEST(DynamicQueue, TestPop)
{
    Eval::DynamicQueue<int> a;
    a.push(1);
    a.pop();
    ASSERT_ANY_THROW(a.front());
}


