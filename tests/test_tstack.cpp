// Copyright 2025 Denis P.

#include <gtest/gtest.h>
#include "../lib_tstack/tstack.h"

TEST(TestTStackLib, can_create_with_def_constr) {
    ASSERT_NO_THROW(TStack<int> a);
}

TEST(TestTStackLib, can_push_correctly) {
    TStack<double> s;
    s.push(0.0);
    s.push(1.0);
    s.push(-1.0);

    EXPECT_EQ(s.top(), -1.0);
}

TEST(TestTStackLib, can_pop_correctly) {
    TStack<double> s;
    s.push(0.0);
    s.push(1.0);
    s.push(-1.0);
    s.pop();

    EXPECT_EQ(s.top(), 1.0);
}

TEST(TestTStackLib, can_push_and_pop_correctly) {
    TStack<double> s;
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

TEST(TestTStackLib, throw_is_empty_func_correctly) {
    TStack<double> s;
    s.push(0.0);
    s.pop();
    ASSERT_ANY_THROW(s.pop());
}

TEST(TestTStackLib, throw_top_func_correctly) {
    TStack<double> s;
    s.push(0.0);
    s.pop();
    ASSERT_ANY_THROW(s.top());
}