#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_with_default_constructor)
{
    TStack<int> stack;
    EXPECT_EQ(stack.size(), 0);
    EXPECT_EQ(stack.capacity(), 0);
}

TEST(TStack, can_create_with_positive_length)
{
    TStack<int> stack(10);
    EXPECT_EQ(stack.size(), 0);
    EXPECT_EQ(stack.capacity(), 10);
}

TEST(TStack, cant_create_too_big)
{
    EXPECT_ANY_THROW(TStack<int> stack(LONG_MAX));
}

TEST(TStack, can_create_a_copy)
{
    TStack<int> stack1;
    stack1.push(1);
    stack1.push(2);

    TStack<int> stack2(stack1);
    EXPECT_EQ(stack2.size(), 2);
    EXPECT_EQ(stack2.top(), 2);

    stack2.pop();
    EXPECT_EQ(stack2.top(), 1);
}

TEST(TStack, can_create_with_move_constructor)
{
    TStack<int> stack1;
    stack1.push(1);
    stack1.push(2);

    TStack<int> stack2(std::move(stack1));
    EXPECT_EQ(stack2.size(), 2);
    EXPECT_EQ(stack2.top(), 2);

    EXPECT_EQ(stack1.size(), 0);
    EXPECT_EQ(stack1.capacity(), 0);
}

TEST(TStack, can_assign)
{
    TStack<int> stack1;
    stack1.push(1);
    stack1.push(2);

    TStack<int> stack2;
    stack2 = stack1;
    EXPECT_EQ(stack2.size(), 2);
    EXPECT_EQ(stack2.top(), 2);

    stack2.pop();
    EXPECT_EQ(stack2.top(), 1);
}

TEST(TStack, capacity_doesnt_change_on_assign_shorter)
{
    TStack<int> stack1;
    stack1.push(1);

    TStack<int> stack2;
    stack2.push(1);
    stack2.push(2);
    stack2.push(3);
    size_t cap = stack2.capacity();
    stack2 = stack1;
    EXPECT_EQ(stack2.capacity(), cap);
}

TEST(TStack, can_perform_move_assignment)
{
    TStack<int> stack1;
    stack1.push(1);
    stack1.push(2);

    TStack<int> stack2;
    stack2 = std::move(stack1);
    EXPECT_EQ(stack2.size(), 2);
    EXPECT_EQ(stack2.top(), 2);

    EXPECT_EQ(stack1.size(), 0);
    EXPECT_EQ(stack1.capacity(), 0);
}

TEST(TStack, can_push)
{
    TStack<int> stack;
    stack.push(1);
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.top(), 1);
    stack.push(2);
    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.top(), 2);
}

TEST(TStack, can_pop)
{
    TStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.pop();
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.top(), 1);
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

TEST(TStack, cant_pop_from_empty)
{
    TStack<int> stack;
    EXPECT_ANY_THROW(stack.pop());
}

TEST(TStack, cant_get_top_from_empty)
{
    TStack<int> stack;
    EXPECT_ANY_THROW(stack.top());
}

TEST(TStack, can_reserve_memory)
{
    TStack<int> stack;
    stack.reserve(10);
    EXPECT_EQ(stack.capacity(), 10);
}

TEST(TStack, doesnt_reserve_less_than_current)
{
    TStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    size_t cap = stack.capacity();
    stack.reserve(2);
    EXPECT_EQ(stack.capacity(), cap);
}

TEST(TStack, cant_reserve_too_many_elements)
{
    TStack<int> stack;
    EXPECT_ANY_THROW(stack.reserve(LONG_MAX));
}

TEST(TStack, test_empty)
{
    TStack<int> stack;
    EXPECT_TRUE(stack.empty());
    stack.push(1);
    EXPECT_FALSE(stack.empty());
}