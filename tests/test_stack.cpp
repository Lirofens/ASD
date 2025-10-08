// Copyright 2025 Denis P.

#include <gtest/gtest.h>
#include "../lib_stack/stack.h"

#define EPSILON 0.000001

TEST(TestStackLib, can_create_with_def_constr) {
    ASSERT_NO_THROW(Stack<int> a);
}