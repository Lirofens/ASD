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

