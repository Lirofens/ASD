#ifndef ALGORITHMS_
#define ALGORITHMS_

#include "stack.h"

// (([{}]))

bool check_breckets(std::string str) {
	Stack<char> stack(str.size());
	for (const auto& el : str) {
		if (el == '(' || el == '{' || el == '[') stack.push(el);
		else {
			if (stack.top() == '(' && el == ')') stack.pop();
			else if (stack.top() == '[' && el == ']') stack.pop();
			else if (stack.top() == '{' && el == '}') stack.pop();
			else return false;
		}
	}
	if (!stack.is_empty()) return false;
	return true;
}
#endif