#ifndef ALGORITHMS_
#define ALGORITHMS_

#include "stack.h"
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
#endif