#ifndef ALGORITHMS_
#define ALGORITHMS_

#define EPSILON 0.0001
#define PI 3.14159

#include "stack.h"
#include <string>
#include <cmath>
#include <iomanip>

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
double get_number(const std::string& var) {
	double number;
	while (true) {
		std::cout << var << " = ";
		std::cin >> number;
		if (std::cin.fail()) {
			std::cout << "Incorrect input.\n";
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else {
			std::cin.ignore(32767, '\n');
			return number;
		}
	}
}

bool check_brackets(std::string str) {
	Stack<char> stack(str.size());
	for (const auto el : str) {
		if (findC(el, "([{")) stack.push(el);
		else if (el == '|' && (stack.is_empty()
			|| stack.top() != '|')) stack.push(el);
		else if (stack.is_empty()) return false;
		else {
			if (stack.top() == '(' && el == ')') stack.pop();
			else if (stack.top() == '[' && el == ']') stack.pop();
			else if (stack.top() == '{' && el == '}') stack.pop();
			else if (stack.top() == '|' && el == '|') stack.pop();
			else return false;
		}
	}
	return stack.is_empty();
}

double module(double x) {
	return (x >= 0) ? x : x * -1;
}
int factorial(int n) {
	int res{ 1 };
	for (int k = 1; k <= n; ++k)
		res *= k;
	return res;
}
double sine(double x) {
	while (x > PI) x -= 2*PI;
	while (x < -PI) x += 2*PI;
	double result = 0.0;
	double term = x;
	int sign = 1;

	for (int n = 1; n <= 10; n++) {
		result += sign * term;
		term *= x * x;
		term /= (2 * n) * (2 * n + 1);

		sign = -sign; 
	}

	return result;
}
double cosine(double x) {
	while (x > PI)  x -= 2 * PI;
	while (x < -PI) x += 2 * PI;
	double result = 1.0;
	double term = 1;
	int sign = -1;

	for (int n = 1; n <= 10; n++) {
		term *= x * x;
		term /= (2 * n - 1) * (2 * n);

		result += sign * term;
		sign = -sign;
	}

	return result;
}
double tangent(double x) {
	return sine(x) / cosine(x);
}

int priority(std::string op) {
	if (op == "+" || op == "-") return 0;
	if (op == "*" || op == "/") return 1;
	if (op == "^") return 2;
	else return 3;
}
#endif