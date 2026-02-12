// Copyright 2025 Denis P.

#include <gtest/gtest.h>
#include "TVector.h"


TEST(TVectorTest, can_create_by_default_constructor_correctly) {
	TVector<int> vec;
	EXPECT_EQ(vec.size(), 0);
}

TEST(TVectorTest, can_create_with_specific_size_correctly) {
	TVector<double> vec(15);
	EXPECT_EQ(vec.size(), 15);
}

TEST(TVectorTest, can_create_with_included_array_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec(array, 5);
	EXPECT_EQ(vec.size(), 5);
	for (size_t i = 0; i < vec.size(); ++i)
		EXPECT_EQ(vec[i], array[i]);
}

TEST(TVectorTest, can_create_by_copy_constructor_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec1(array, 5), vec2(vec1);
	EXPECT_TRUE(vec1 == vec2);
}

TEST(TVectorTest, can_set_data_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec;
	vec.data(array, 5);
	EXPECT_EQ(vec[2], array[2]);
}

TEST(TVectorTest, can_set_size_correctly) {
	TVector<int> vec;
	vec.size(3);
	EXPECT_EQ(vec.size(), 3);
}

TEST(TVectorTest, can_set_capacity_correctly) {
	TVector<int> vec;
	vec.capacity(40);
	EXPECT_EQ(vec.capacity(), 40);
}

TEST(TVectorTest, can_push_back_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec(array, 5);
	vec.push_back(2);
	EXPECT_EQ(vec[5], 2);
}

TEST(TVectorTest, can_push_front_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec(array, 5);
	vec.push_front(2);
	EXPECT_EQ(vec[0], 2);
}

TEST(TVectorTest, can_insert_number_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec(array, 5);
	vec.insert(2, 0, 3);
	for (size_t i = 2; i < 5; ++i)
		EXPECT_EQ(vec[i], 0);
}

TEST(TVectorTest, can_insert_array_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec(array, 5);
	vec.insert(3, array, 5);
	for (size_t i = 3; i < 8; ++i)
		EXPECT_EQ(vec[i], array[i - 3]);
}

TEST(TVectorTest, can_pop_back_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec(array, 5);
	vec.pop_back();
	EXPECT_ANY_THROW(vec.at(4));
	EXPECT_EQ(vec.size(), 4);
}

TEST(TVectorTest, can_pop_front_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec(array, 5);
	vec.pop_front();
	EXPECT_NE(vec[0], 1);
	EXPECT_EQ(vec.size(), 4);
}

TEST(TVectorTest, can_eraze_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec(array, 5);
	vec.eraze(1, 3);
	EXPECT_NE(vec[1], 2);
	EXPECT_EQ(vec.size(), 2);
}

TEST(TVectorTest, can_emplace_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec(array, 5);
	vec.emplace(2, 4);
	EXPECT_EQ(vec[2], 4);
}

TEST(TVectorTest, can_assign_number_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec(array, 5);
	vec.assign(1, 0, 4);
	for (size_t i = 1; i < vec.size(); ++i)
		EXPECT_EQ(vec[i], 0);
}

TEST(TVectorTest, can_assign_array_correctly) {
	int array1[5]{ 1, 2, 3, 4, 5 };
	int array2[3]{ 10, -10, 0 };
	TVector<int> vec(array1, 5);
	vec.assign(1, array2, 3);
	for (size_t i = 0; i < 3; ++i)
		EXPECT_EQ(vec[i + 1], array2[i]);
}

TEST(TVectorTest, can_using_functoin_at_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec(array, 5);
	EXPECT_ANY_THROW(vec.at(5));
}

TEST(TVectorTest, can_clear_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec(array, 5);
	vec.clear();
	EXPECT_EQ(vec.capacity(), 0);
	EXPECT_ANY_THROW(vec.at(5));
}

TEST(TVectorTest, can_using_shrink_func_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec(array, 5);
	vec.shrink_to_fit();
	EXPECT_EQ(vec.capacity(), vec.size());
}

TEST(TVectorTest, func_inactivity) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec(array, 5);
	size_t vecCap = vec.capacity();
	vec.reserve(4);
	EXPECT_EQ(vec.capacity(), vecCap);
}

TEST(TVectorTest, can_using_reserve_func1_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec(array, 5);
	size_t vecCap = vec.capacity();
	vec.reserve(20);
	EXPECT_NE(vec.capacity(), vecCap);
}

TEST(TVectorTest, can_reduce_correctly) {
	int array[15]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	TVector<int> vec(array, 15);
	EXPECT_EQ(vec.capacity(), 30);
	vec.resize(10);
	EXPECT_EQ(vec.capacity(), 15);
	EXPECT_EQ(vec.size(), 10);
}

TEST(TVectorTest, can_increase_correctly) {
	int array[14]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	TVector<int> vec(array, 14);
	EXPECT_EQ(vec.capacity(), 15);
	vec.resize(20);
	EXPECT_EQ(vec.capacity(), 30);
	EXPECT_EQ(vec.size(), 14);
}

TEST(TVectorTest, can_get_data_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec(array, 5);
	const int* data = vec.data();
	EXPECT_EQ(data, vec.data());
}

TEST(TVectorTest, can_get_size_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec(array, 5);
	size_t size = vec.size();
	EXPECT_EQ(size, 5);
}

TEST(TVectorTest, can_get_capacity_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec(array, 5);
	size_t cap = vec.capacity();
	EXPECT_EQ(cap, 15);
}

TEST(TVectorTest, can_get_back_element_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec(array, 5);
	const int el = vec.back();
	EXPECT_EQ(el, vec[4]);
}

TEST(TVectorTest, can_get_front_element_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec(array, 5);
	const int el = vec.front();
	EXPECT_EQ(el, vec[0]);
}

TEST(TVectorTest, can_using_is_empty_func_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec(array, 5);
	EXPECT_FALSE(vec.is_empty());
}

TEST(TVectorTest, can_using_is_full_and_local_resize_func_correctly) {
	int array[14]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	TVector<int> vec(array, 14);
	EXPECT_EQ(vec.capacity(), 15);
	vec.push_back(16);
	EXPECT_EQ(vec.capacity(), 30);
}

TEST(TVectorTest, index_operator) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec(array, 5);
	EXPECT_EQ(vec[1], vec.at(1));
}

TEST(TVectorTest, equality_operator_1) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec1(array, 5), vec2;
	vec2 = vec1;
	EXPECT_TRUE(vec1 == vec2);
}

TEST(TVectorTest, equality_operator_2) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec1(array, 5);
	ASSERT_NO_THROW(vec1 = vec1);
}

TEST(TVectorTest, ineqvality_operator) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec1(array, 5), vec2;
	EXPECT_TRUE(vec1 != vec2);
}

TEST(TVectorTest, assignment_operator) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec1(array, 5), vec2;
	vec2 = vec1;
	EXPECT_TRUE(vec1 == vec2);
}

TEST(TVectorTest, clear_vector_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec1(array, 5);
	vec1.clear();
	vec1.clear();
}

TEST(TVectorTest, quick_sort_correctly) {
	int array[5]{ 2, 1, 4, 3, 5 };
	TVector<int> vec1(array, 5);
	quick_sort(vec1, 0, 4);
	for (size_t i = 0; i < 4; ++i)
		EXPECT_EQ(vec1[i] + 1, vec1[i + 1]);
}

TEST(TVectorTest, binary_search_correctly) {
	int array[5]{ 1, 2, 3, 4, 5 };
	TVector<int> vec1(array, 5);
	size_t in_el = binary_search(vec1, 4);
	EXPECT_EQ(in_el, 3);
}

TEST(TVectorTest, iterator_test) {
	TVector<int> list, empty_list;

	for (size_t i = 0; i < 5; ++i) list.push_back(i);
	int exp_v = 0;
	for (TVector<int>::iterator it = list.begin(); it != list.end(); ++it)
		EXPECT_EQ(*it, exp_v++);
	for (TVector<int>::iterator it = list.end(); it != list.begin(); --it)
		EXPECT_EQ(*it, exp_v--);
	for (TVector<int>::iterator it = list.begin(); it != list.end(); ++it) {
		*it = exp_v;
		EXPECT_EQ(*it, exp_v++);
	}
	for (TVector<int>::iterator it = empty_list.begin(); it != empty_list.end(); ++it)
		ASSERT_NO_THROW(*it = 0);

}

