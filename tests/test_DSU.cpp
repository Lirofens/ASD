// Copyright 2024 Denis P.

#include <gtest/gtest.h>
#include "../lib_DSU/DSU.h"

TEST(DSUTests, simple_unite_test_1) {
	DSU set(10);
	set.unite(3, 4);
	EXPECT_EQ(set.find(4), 3);
}

TEST(DSUTests, simple_unite_test_2) {
	DSU set(10);
	set.unite(3, 4);
	set.unite(3, 5);
	EXPECT_EQ(set.find(5), 3);
	EXPECT_EQ(set.find(4), 3);
}

TEST(DSUTests, simple_unite_test_3) {
	DSU set(10);
	set.unite(3, 4);
	set.unite(5, 3);
	EXPECT_EQ(set.find(5), 3);
	EXPECT_EQ(set.find(4), 3);
}

TEST(DSUTests, find_themself_test) {
	DSU set(10);
	EXPECT_EQ(set.find(3), 3);
}


TEST(DSUTests, mid_unite_test_1) {
	DSU set(10);
	set.unite(4, 3);

	set.unite(1, 2);

	set.unite(1, 4);

	EXPECT_EQ(set.find(2), 1);
	EXPECT_EQ(set.find(3), 1);
}

TEST(DSUTests, mid_unite_test_2) {
	DSU set(10);
	set.unite(4, 3);

	set.unite(1, 2);

	set.unite(4, 1);

	EXPECT_EQ(set.find(2), 4);
	EXPECT_EQ(set.find(3), 4);
}

TEST(DSUTests, hard_unite_test_1) {
	DSU set(10);
	set.unite(4, 3);
	set.unite(5, 4);

	set.unite(1, 2);
	set.unite(0, 1);

	set.unite(1, 4);

	EXPECT_EQ(set.find(5), 1);
	EXPECT_EQ(set.find(4), 1);
	EXPECT_EQ(set.find(3), 1);
	EXPECT_EQ(set.find(0), 1);
}

TEST(DSUTests, hard_unite_test_2) {
	DSU set(10);
	set.unite(0, 1);
	set.unite(0, 2);

	set.unite(3, 4);
	set.unite(3, 5);

	set.unite(2, 5);

	EXPECT_EQ(set.find(5), 0);
	EXPECT_EQ(set.find(4), 0);
	EXPECT_EQ(set.find(3), 0);
}

