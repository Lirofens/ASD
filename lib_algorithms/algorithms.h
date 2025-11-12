#ifndef ALGORITHMS_
#define ALGORITHMS_

#include "stack.h"
#include "DSU.h"
#include <string>


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
#endif