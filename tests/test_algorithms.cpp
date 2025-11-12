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