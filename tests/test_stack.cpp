// Copyright 2025 Denis P.

#include <gtest/gtest.h>
#include "../lib_stack/stack.h"

TEST(TestStackLib, can_create_with_def_constr) {
    ASSERT_NO_THROW(Stack<int> a);
}

TEST(TestStackLib, can_create_with_specific_size) {
    ASSERT_NO_THROW(Stack<int> a(10));
}

TEST(TestStackLib, can_push_correctly) {
    Stack<double> s;
    s.push(0.0);
    s.push(1.0);
    s.push(-1.0);

    EXPECT_EQ(s.top(), -1.0);
}

TEST(TestStackLib, can_pop_correctly) {
    Stack<double> s;
    s.push(0.0);
    s.push(1.0);
    s.push(-1.0);
    s.pop();

    EXPECT_EQ(s.top(), 1.0);
}

TEST(TestStackLib, can_push_and_pop_correctly) {
    Stack<double> s;
    s.push(0.0);
    s.push(1.0);
    s.push(-1.0);
    s.pop();
    s.push(-1.0);
    s.push(2.0);
    s.push(4.0);
    s.pop();
    s.push(4.0);
    s.pop();

    EXPECT_EQ(s.top(), 2.0);
}

TEST(TestStackLib, throw_is_full_func_correctly) {
    Stack<double> s(1);
    s.push(0.0);
    ASSERT_ANY_THROW(s.push(0.0));
}

TEST(TestStackLib, throw_is_empty_func_correctly) {
    Stack<double> s(3);
    s.push(0.0);
    s.pop();
    ASSERT_ANY_THROW(s.pop());
}

TEST(TestStackLib, throw_top_func_correctly) {
    Stack<double> s(3);
    s.push(0.0);
    s.pop();
    ASSERT_ANY_THROW(s.top());
}