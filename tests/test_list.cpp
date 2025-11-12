// Copyright 2025 Denis P.

#include <gtest/gtest.h>
#include "../lib_list/list.h"

TEST(TestListLib, can_create_by_default_const_correctly) {
	ASSERT_NO_THROW(List<int> list);
}

TEST(TestListLib, can_create_by_copy_const_correctly) {
	List<int> list;
	list.push_front(1);
	list.push_back(2);
	list.push_back(3);
	List<int> list_c(list);
	list_c.pop_back();
	EXPECT_EQ(list_c.head(), 1);
	EXPECT_EQ(list_c.tail(), 2);
}

TEST(TestListLib, push_front_correctly) {
	List<int> list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	EXPECT_EQ(list.head(), 3);
	EXPECT_EQ(list.tail(), 1);
}

TEST(TestListLib, push_back_correctly) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	EXPECT_EQ(list.head(), 1);
	EXPECT_EQ(list.tail(), 3);
}

TEST(TestListLib, push_front_and_back_correctly) {
	List<int> list;
	list.push_front(1);
	list.push_front(0);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_front(-1);
	list.push_back(5);
	EXPECT_EQ(list.head(), -1);
	EXPECT_EQ(list.tail(), 5);
}

TEST(TestListLib, pop_front_correctly) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.pop_front();
	EXPECT_EQ(list.head(), 2);
	EXPECT_EQ(list.tail(), 3);
}

TEST(TestListLib, throw_pop_front_correctly) {
	List<int> list;
	list.push_back(1);
	list.pop_front();
	EXPECT_ANY_THROW(list.pop_front());
}

TEST(TestListLib, pop_back_correctly) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.pop_back();
	EXPECT_EQ(list.head(), 1);
	EXPECT_EQ(list.tail(), 3);
}

TEST(TestListLib, push_and_pop_front_and_push_and_pop_back_correctly) {
	List<int> list;
	list.push_front(0);
	list.pop_front();
	list.push_front(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);
	list.pop_back();
	list.push_back(6);
	list.pop_back();
	list.pop_back();
	EXPECT_EQ(list.head(), 1);
	EXPECT_EQ(list.tail(), 3);
}

TEST(TestListLib, insert_by_pos_correctly) {
	List<int> list;
	list.push_front(1);
	list.push_back(2);
	list.push_back(3);
	list.insert(1, 10);
	list.pop_front();
	EXPECT_EQ(list.head(), 10);
}

TEST(TestListLib, throw_insert_by_pos_correctly) {
	List<int> list;
	list.push_back(1);
	EXPECT_ANY_THROW(list.insert(3, 4));
}

TEST(TestListLib, insert_by_node_correctly) {
	List<int> list;
	list.push_front(1);
	list.push_back(2);
	list.push_back(3);
	list.insert(list.node(1), 10);
	list.pop_back();
	EXPECT_EQ(list.tail(), 10);
}

TEST(TestListLib, eraze_by_pos_correctly) {
	List<int> list;
	list.push_front(1);
	list.push_back(2);
	list.push_back(3);
	list.eraze(2);
	list.pop_front();
	EXPECT_EQ(list.head(), 2);
}

TEST(TestListLib, eraze_by_node_correctly) {
	List<int> list;
	list.push_front(1);
	list.push_back(2);
	list.push_back(3);
	list.eraze(list.node(1));
	list.pop_back();
	EXPECT_EQ(list.tail(), 1);
}

TEST(TestListLib, throw_get_head_correctly) {
	List<int> list;
	list.push_back(1);
	list.pop_back();
	EXPECT_ANY_THROW(list.head());
}

TEST(TestListLib, iterator_test) {
	List<int> list, empty_list;

	for (size_t i = 0; i < 5; ++i) list.push_back(i);
	int exp_v = 0;
	for (List<int>::iterator it = list.begin(); it != list.end(); ++it)
		EXPECT_EQ(*it, exp_v++);
	for (List<int>::iterator it = list.begin(); it != list.end(); ++it) {
		*it = exp_v;
		EXPECT_EQ(*it, exp_v++);
	}

	ASSERT_NO_THROW({
		for (List<int>::iterator it = empty_list.begin(); it != empty_list.end(); ++it)
			*it = 0;
		}
	);
	
}



TEST(TestDListLib, throw_get_head_correctly) {
	DList<int> list;
	list.push_back(1);
	EXPECT_EQ(list.head(), 1);
	list.pop_back();
	EXPECT_ANY_THROW(list.head());
}

TEST(TestDListLib, push_back_correctly) {
	DList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.pop_front();

	EXPECT_EQ(list.head(), 2);
	EXPECT_EQ(list.tail(), 3);
}

TEST(TestDListLib, push_front_correctly) {
	DList<int> list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	list.pop_back();

	EXPECT_EQ(list.head(), 3);
	EXPECT_EQ(list.tail(), 2);
}

TEST(TestDListLib, pop_back_correctly) {
	DList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.pop_back();
	EXPECT_EQ(list.head(), 1);
	EXPECT_EQ(list.tail(), 2);
}

TEST(TestDListLib, iterator_test) {
	DList<int> list, empty_list;

	for (size_t i = 0; i < 5; ++i) list.push_back(i);
	int exp_v = 0;
	for (DList<int>::iterator it = list.begin(); it != list.end(); ++it)
		EXPECT_EQ(*it, exp_v++);
	for (DList<int>::iterator it = list.rbegin(); it != list.rend(); --it)
		EXPECT_EQ(*it, --exp_v);
	for (DList<int>::iterator it = list.begin(); it != list.end(); ++it) {
		*it = exp_v;
		EXPECT_EQ(*it, exp_v++);
	}

	ASSERT_NO_THROW(
		for (DList<int>::iterator it = empty_list.begin(); it != empty_list.end(); ++it)
			*it = 0;
	);

}