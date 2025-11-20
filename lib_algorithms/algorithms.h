#ifndef ALGORITHMS_
#define ALGORITHMS_

#include "stack.h"
#include "DSU.h"
#include "list.h"
#include <string>
#include "../third_party/gtest/googletest/include/gtest/internal/gtest-internal.h"


bool check_breckets(std::string str) {
	Stack<char> stack(str.size());
	for (const auto el : str) {
		if (el == '(' || el == '{' || el == '[') stack.push(el);
		else if (stack.is_empty()) return false;
		else {
			if		(stack.top() == '(' && el == ')') stack.pop();
			else if (stack.top() == '[' && el == ']') stack.pop();
			else if (stack.top() == '{' && el == '}') stack.pop();
			else return false;
		}
	}
	return stack.is_empty();
}

template<int rows, int cols>
int ilands(int(&mass)[rows][cols]) noexcept {
	DSU map(rows * cols);
	int count0 = 0, count = 0;
	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < cols; ++j) {
			if (mass[i][j]) {
				if (mass[i][j + 1] && j != cols - 1)
					map.unite(cols * i + j, cols * i + j + 1);
				if (mass[i + 1][j] && i != rows - 1)
					map.unite(cols * i + j, cols * (i + 1) + j);
			}
			else count0++;
		}

	for (size_t i = 0; i < rows * cols; ++i)
		if (map.find(i) == i) count++;
	return count - count0;
}

template <class T>
bool check_circle(const List<T>& list) {
	List<T>::iterator slow = list.begin();
	List<T>::iterator fast = slow;
	while (slow != list.end() || fast != list.end()) {
		slow++;
		if (++fast != nullptr) fast++;
		else break;
		if (slow == fast) return true;
	}
	return false;
}

template <class T>
Node<T>* check_circle_with_pos(const List<T>& list) {
	Node<T>* slow = list.node(0);
	Node<T>* fast = slow;
	while (slow != fast || slow == list.node(0)) {
		if (slow->next != nullptr)
			slow = slow->next;
		if (fast->next != nullptr)
			fast = fast->next->next;
		if (slow == fast && !fast->next) return nullptr;
		if (slow == fast) return fast;
	}
	return fast;
}

template <class T>
bool check_circle_rev(Node<T> *head) {
	Node<T>* prev = nullptr;
	Node<T>* cur = head;
	Node<T>* next = nullptr;
	while (cur) {
		next = cur->next;
		if (next == head) {
			cur = prev;
			prev = next = nullptr;
			while (cur) {
				next = cur->next;
				cur->next = prev;
				prev = cur;
				cur = next;
			}
			return true;
		}
		cur->next = prev;
		prev = cur;
		cur = next;
	}

	cur = prev;
	prev = next = nullptr;
	while (cur) {
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	return false;
}


#endif