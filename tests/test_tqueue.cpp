// Copyright 2025 Denis P.

#include <gtest/gtest.h>
#include "../lib_tqueue/TQueue.h"

TEST(TestTQueueLib, can_create_with_def_constr) {
    ASSERT_NO_THROW(TQueue<int> a);
}

TEST(TestTQueueLib, can_push_correctly) {
    TQueue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    EXPECT_EQ(q.head(), 1);
}

TEST(TestTQueueLib, can_pop_correctly) {
    TQueue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.pop();
    q.pop();

    EXPECT_EQ(q.head(), 3);
}

TEST(TestTQueueLib, can_push_and_pop_correctly) {
    TQueue<int> q;
    q.push(1);
    q.push(2);
    q.push(3); //1 2 3
    q.pop();
    q.pop(); // 3
    q.push(4);
    q.push(5); // 3 4 5
    q.pop();
    q.pop(); // 5
    q.pop(); // -
    q.push(6);
    q.push(7); // 6 7
    q.pop(); // 7

    EXPECT_EQ(q.head(), 7);
}


TEST(TestTQueueLib, throw_is_empty_correctly) {
    TQueue<int> q;
    q.push(1);
    q.pop();

    EXPECT_ANY_THROW(q.pop());
}