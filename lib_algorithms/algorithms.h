#ifndef ALGORITHMS_
#define ALGORITHMS_

#include "stack.h"
#include <string>
#include <cmath>

inline bool is_letter(char c) {
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}
inline bool is_digit(char c) {
	return (c >= '0' && c <= '9');
}
bool findC(const char c, std::string str) {
	for (size_t i = 0; i < str.size(); i++)
		if (c == str[i]) return true;
	return false;
}

bool check_brackets(std::string str) {
	Stack<char> stack(str.size());
	for (const auto el : str) {
		if (findC(el, "([{")) stack.push(el);
		else if (el == '~' && (stack.is_empty() || findC(stack.top(), "([{"))) stack.push(el);
		else if (stack.top() == '~' && el == '|') stack.push(el);
		else if (stack.is_empty()) return false;
		else {
			if (stack.top() == '(' && el == ')') stack.pop();
			else if (stack.top() == '[' && el == ']') stack.pop();
			else if (stack.top() == '{' && el == '}') stack.pop();
			else if (stack.top() == '|' && el == '|') stack.pop();
			else if (stack.top() == '~' && el == '~') stack.pop();
			else return false;
		}
	}
	return stack.is_empty();
}

int factorial(int n) {
	int res{ 1 };
	for (int k = 1; k <= n; ++k)
		res *= k;
	return res;
}
double sine(double x) {
	double res{ 0 }; int fac{ 1 };
	for (int n = 0; n < 5; n++)
		res += pow((-1), n) * pow(x, 2 * n + 1) / factorial(2 * n + 1);
	return res;
}
double cosine(double x) {
	double res{ 0 }; int fac{ 1 };
	for (int n = 0; n < 5; n++)
		res += pow((-1), n) * pow(x, 2 * n ) / factorial(2 * n);
	return res;
}
double tangent(double x) {
	return sine(x) / cosine(x);
}

#endif