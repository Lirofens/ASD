// Copyright 2025 Denis P.

#include <gtest/gtest.h>
#include "../lib_algorithms/algorithms.h"

TEST(TestStackLib, check_breckets_test_1) {
	std::string str{ "()" };
	EXPECT_TRUE(check_breckets(str));
}

TEST(TestStackLib, check_breckets_test_2) {
	std::string str{ "([]{})" };
	EXPECT_TRUE(check_breckets(str));
}

TEST(TestStackLib, check_breckets_test_3) {
	std::string str{ "()(" };
	EXPECT_FALSE(check_breckets(str));
}

TEST(TestStackLib, check_breckets_test_4) {
	std::string str{ "[])" };
	EXPECT_FALSE(check_breckets(str));
}

TEST(TestStackLib, check_breckets_test_5) {
	std::string str{ "" };
	EXPECT_TRUE(check_breckets(str));
}

TEST(TestStackLib, check_breckets_test_6) {
	std::string str{ "(a + b) * c" };
	EXPECT_FALSE(check_breckets(str));
}

TEST(DSUTests, Ilands) {
	int map[5][7] = {
	{1, 1, 0, 0, 0, 1, 1},
	{1, 0, 0, 0, 0, 1, 0},
	{0, 1, 1, 0, 1, 0, 0},
	{0, 0, 1, 1, 0, 0, 0},
	{0, 0, 1, 0, 0, 0, 1}
	};
	EXPECT_EQ(ilands(map), 5);

}

TEST(DSUTests, Ilands_0) {
	int map[5][7] = {
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0}
	};
	EXPECT_EQ(ilands(map), 0);

}

TEST(DSUTests, Ilands_1) {
	int map[5][7] = {
	{1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1} };
	EXPECT_EQ(ilands(map), 1);

}
TEST(CircleInListTest, hare_and_turtle) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);
	EXPECT_FALSE(check_circle(list));
	list.node(4)->next = list.node(1);
	EXPECT_TRUE(check_circle(list));
	list.node(4)->next = nullptr;
}

TEST(CircleInListTest, reversal_of_signs) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);
	EXPECT_FALSE(check_circle_rev(list.node(0)));
	list.node(4)->next = list.node(1);
	EXPECT_TRUE(check_circle_rev(list.node(0)));
	list.node(4)->next = nullptr;
}

TEST(CircleInListTest, hare_and_turtle_with_pos) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);
	EXPECT_FALSE(check_circle_with_pos(list));
	Node<int>* tmp = list.node(3)->next;
	list.node(3)->next = list.node(1);
	EXPECT_EQ(check_circle_with_pos(list)->value, 4);
	list.node(3)->next = tmp;
}