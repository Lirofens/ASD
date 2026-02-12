#ifndef EXPRESSION_
#define EXPRESSION_

#include <iostream>
#include <string>
#include "list.h"
#include "stack.h"
#include "algorithms.h"

enum TypeLexem { OPEN_B, CLOSE_B, VARIABLE, OPERATOR, CONSTANT, FUNCTION };

//The structure of the tokens with the fields that make up the expression.
struct Lexem {
	std::string name;
	double value;
	double (*function)(double);
	TypeLexem type;
	Lexem() : name(""), value(0), function(nullptr), type(OPEN_B) {}
	Lexem(std::string n, double v, double (*f)(double), TypeLexem t)
		: name(n), value(v), function(f), type(t) {}

	friend std::ostream& operator<< (std::ostream& out, const Lexem& lexem);
};
std::ostream& operator<< (std::ostream& out, const Lexem& lexem) {
	if (lexem.type == CONSTANT) out << lexem.value;
	else if (lexem.type == OPERATOR && lexem.name != "~")
		out << ' ' << lexem.name << ' ';
	else out << lexem.name;
	return out;
}


//A custom exception class for storing the exception throw index in string parsing.
class error_in_expr : public std::logic_error {
private:
	size_t pos;
public:
	error_in_expr(std::string str, size_t pos)
		: std::logic_error(str), pos(pos) {}
	size_t where() const { return pos; }
};

//A namespace with a parsing function and auxiliary functions.
namespace Parser {
	
	void push_const(List<Lexem>& list, const std::string& str, size_t& i) {
		std::string number;
		while ((is_digit(str[i]) || str[i] == '.') && i < str.size()) {
			if (str[i] == '.') {
				number += str[i++];
				while (is_digit(str[i]) && i < str.size())
					number += str[i++];
				break;
			}
			number += str[i++];
		}
		size_t j{ (i == str.size()) ? i - 1 : i};
		while (str[j] == ' ' && j < str.size() - 1) j++;
		if (!(findC(str[j], "+-*/^)]}|")) && j != str.size() - 1)
			throw error_in_expr("The constant must be followed by a closing bracket or an operator.", i);
		j = (i - number.size() == 0) ? i - number.size() : i - number.size() - 1;
		while (str[j] == ' ' && j > 0) j--;
		if (j != 0 && list.tail().type != OPEN_B && list.tail().type != OPERATOR) {
			i -= number.size();
			throw error_in_expr("A constant must be preceded by a open bracket or an operator.", i);
		}
		double value = std::stod(number);
		list.push_back(*(new Lexem("const", value, nullptr, CONSTANT)));
		i--;
	}
	void push_operator(List<Lexem>& list, const std::string& str, size_t& i) {
		if (i == str.size() - 1) throw error_in_expr("The expression ends with an operator.", i);
		size_t j{ i + 1 }, next{ j };

		if (str[i] == '+' || str[i] == '-') {
			//Checking to the right of the operator and minimizing operations.
			bool op = (str[i] == '+') ? true : false;
			while (j < str.size() - 1 && findC(str[j], " +-")) {
				if (str[j] == '-') op = !op;
				j++;
			}
			if (str[j] == ' ') throw error_in_expr("The expression ends with an operator.", i);
			if (findC(str[j], ")]}/*^"))
				throw error_in_expr("There cannot be a opening bracket or another operator before the operator (+ or -).", i);
			next = j - 1;

			//Checking to the left of the operator.
			j = (i == 0) ? i : i - 1;
			while (str[j] == ' ' && j > 0) j--;

			//Pushing the operator.
			if (i == 0 || str[j] == ' ' || list.tail().type == OPEN_B)
				list.push_back(*(new Lexem("const", 0, nullptr, CONSTANT)));
			list.push_back(*(new Lexem((op) ? "+" : "-", 0, nullptr, OPERATOR)));
			i = next;
		}
		else {
			//Checking to the right of the operator.
			while (j < str.size() - 1 && str[j] == ' ') j++;
			if (str[j] == ' ') throw error_in_expr("The expression ends with an operator.", i);
			if (findC(str[j], ")]}+-/*^"))
				throw error_in_expr("There cannot be a opening bracket or another operator before the operator (*, / or ^).", i);

			//Checking to the left of the operator.
			j = (i == 0) ? i : i - 1;
			while (str[j] == ' ' && j > 0) j--;
			if (str[j] == ' ' || i == 0) throw error_in_expr("The expression begins with an operator", i);
			if (list.is_empty() || list.tail().type == OPEN_B)
				throw error_in_expr("There cannot be a closing bracket or another operator after the operator.", i);

			//Pushing the operator.
			std::string op{ str[i] };
			list.push_back(*(new Lexem(op, 0, nullptr, OPERATOR)));
		}
	}
	void push_var_or_func(List<Lexem>& list, const std::string& str, size_t& i) {
		if (i < str.size() - 2 && str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n') { // sin
			if (str[i + 3] != '(') throw error_in_expr("There should be a bracket after the function.", i);
			list.push_back(*(new Lexem("sin", 0, sine, FUNCTION))); i += 2;
		}
		else if (i < str.size() - 2 && str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's') { // cos
			if (str[i + 3] != '(') throw error_in_expr("There should be a bracket after the function.", i);
			list.push_back(*(new Lexem("cos", 0, cosine, FUNCTION)));  i += 2;
		}
		else if (i < str.size() - 2 && str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n') { // tan
			if (str[i + 3] != '(') throw error_in_expr("There should be a bracket after the function.", i);
			list.push_back(*(new Lexem("tan", 0, tangent, FUNCTION)));  i += 2;
		}
		else { // variable
			std::string var;
			while ((is_letter(str[i]) || is_digit(str[i]) || str[i] == '_') && i < str.size())
				var += str[i++];
			i--;
			if (var[0] == '_') {
				if (var.size() == 1) throw error_in_expr("Invalid variable name.", i);
				for (size_t j = 0; j < var.size(); j++) {
					if (is_letter(var[j])) break;
					if (j == var.size() - 1 && !is_letter(var[j])) throw error_in_expr("Invalid variable name.", i);
				}
			}
			size_t next{ (i == str.size() - 1) ? i : i + 1 };
			size_t prev{ (i - var.size() + 1 == 0) ? i - var.size() + 1 : i - var.size() };
			while (str[next] == ' ' && next < str.size() - 1) next++;
			while (str[prev] == ' ' && prev > 0) prev--;

			if (!findC(str[next], " +-*/^)]}|") && next != i)
				throw error_in_expr("The variable must be followed by a close bracket or an operator.", i);
			if (prev != 0 && list.tail().type != OPEN_B && list.tail().type != OPERATOR) {
				i -= var.size();
				throw error_in_expr("The variable must be preceded by a open bracket or an operator.", i);
			}
			list.push_back(*(new Lexem(var, 0, nullptr, VARIABLE)));
		}
	}
	void push_module(List<Lexem>& list, const std::string& str, size_t& i) {
		size_t next{ (i == str.size() - 1) ? i : i + 1 };
		size_t prev{ (i == 0)			   ? i : i - 1 };
		while (next < str.size() - 1 && str[next] == ' ') next++;
		while (prev > 0				 && str[prev] == ' ') prev--;
		TypeLexem type = (prev == 0) ? OPEN_B : (next == str.size() - 1) ? CLOSE_B : CONSTANT;

		if (!list.is_empty() && list.tail().type == OPERATOR && type == CLOSE_B)
			throw error_in_expr("There is an operator before the closing parenthesis.", i);
		if (type != CONSTANT) list.push_back(*(new Lexem("|", 0, nullptr, type)));
		else {
			if (str[prev] == '|' && str[next] == '|') type = list.tail().type;
			else if (!findC(str[next], ")]}-+/*^") && findC(str[prev], "([{|+-/*^"))
				type = OPEN_B;
			else if (findC(str[next], "-+/*^") && findC(str[prev], "+-/*^"))
				type = OPEN_B;
			else type = CLOSE_B;
			if (!list.is_empty() && list.tail().type == OPERATOR && type == CLOSE_B)
				throw error_in_expr("There is an operator before the closing parenthesis.", i);
			list.push_back(*(new Lexem("|", 0, nullptr, type)));
		}
	}
	void push_brackets(List<Lexem>& list, Stack<char>& stack, const std::string& str, size_t& i) {
		std::string type{ str[i] };

		if (findC(str[i], "([{")) {
			stack.push(str[i]);
			list.push_back(*(new Lexem(type, 0, nullptr, OPEN_B)));
		}
		else if (str[i] == '|' && (stack.is_empty() || stack.top() != '|')) {
			stack.push(str[i]);
			push_module(list, str, i);
		}
		else if (stack.is_empty()) throw std::exception("Incorrect brackets.");
		else {
			if (str[i] != '|') list.push_back(*(new Lexem(type, 0, nullptr, CLOSE_B)));
			else push_module(list, str, i);

			if (stack.top() == '(' && str[i] == ')') stack.pop();
			else if (stack.top() == '[' && str[i] == ']') stack.pop();
			else if (stack.top() == '{' && str[i] == '}') stack.pop();
			else if (stack.top() == '|' && str[i] == '|') stack.pop();
			else throw std::exception("Incorrect brackets.");
		}
	}

	List<Lexem>& parse(std::string str) {
		//Creating a list of lexemes and a stack for checking brackets, as well as a boolean variable for checking emptiness.
		Stack<char> stack(str.size()); bool empty{ true };
		List<Lexem>* list = new List<Lexem>();

		for (size_t i = 0; i < str.size(); i++) {
			if (str[i] == ' ') continue;
			else empty = false;

			if		(findC(str[i], "([{|}])"))			 push_brackets(*list, stack, str, i);
			else if (findC(str[i], "+-*/^~"))			 push_operator(*list, str, i);
			else if (is_digit(str[i]))					 push_const(*list, str, i);
			else if (is_letter(str[i]) || str[i] == '_') push_var_or_func(*list, str, i);
			else throw error_in_expr("Invalid character.", i);
		}

		//Checks: for emptiness, for the correctness of parentheses, for the presence of constants or variables.
		if (empty) throw std::exception("The line is empty!");
		if (!stack.is_empty()) throw std::exception("Incorrect brackets.");
		for (List<Lexem>::iterator it = list->begin(); it != list->end(); ++it)
			if ((*it).type == VARIABLE || (*it).type == CONSTANT) return *list;
		throw std::exception("There are no variables or constants in an arithmetic expression!");
	}
}

//An expression class with all the necessary fields and methods.
class Expression {
private:
	List<Lexem> expression;
	List<Lexem> polish_record;
	List <std::string> variables;
	void init_variables();
	void construct_polish_record();
public:
	Expression(std::string str);

	void set_values();
	double calculate();
	void print_PR();
	List<Lexem>& expr() noexcept;
	List<Lexem>& PR() noexcept;
	List<std::string>& var() noexcept;
	const List<Lexem>& expr() const noexcept;
	const List<Lexem>& PR() const noexcept;
	const List<std::string>& var() const noexcept;
	friend std::ostream& operator<< (std::ostream& out, const Expression& expr);
};

Expression::Expression(std::string str) : expression(Parser::parse(str)) {
	init_variables();
	construct_polish_record();
}
void Expression::init_variables() {
	for (List<Lexem>::iterator it = expr().begin(); it != expr().end(); ++it) {
		if ((*it).type == VARIABLE) {
			bool unique = true;
			for (List<std::string>::iterator inside = variables.begin(); inside != variables.end(); ++inside)
				if ((*it).name == (*inside)) {
					unique = false;
					break;
				}
			if (unique) variables.push_back((*it).name);
		}
	}
}
void Expression::construct_polish_record() {
	Stack<Lexem> stack;
	for (List<Lexem>::iterator it = expr().begin(); it != expr().end(); ++it) {
		//Operators and constants are immediately placed in the record.
		if ((*it).type == VARIABLE || (*it).type == CONSTANT)
			polish_record.push_back(*it);

		//Processing brackets.
		else if ((*it).type == OPEN_B) stack.push(*it);
		else if ((*it).type == CLOSE_B && !stack.is_empty()) {
			while (stack.top().type != OPEN_B) {
				polish_record.push_back(stack.top());
				stack.pop();
			}
			stack.pop();
			if ((*it).name == "|")
				polish_record.push_back(Lexem("abs", 0, module, FUNCTION));
		}

		//Processing operations with priority.
		else {
			while (!stack.is_empty() && stack.top().type != OPEN_B &&
				priority(stack.top().name) >= priority((*it).name)) {
				polish_record.push_back(stack.top());
				stack.pop();
			}
			stack.push(*it);
		}
	}

	//Everything that remains on the stack is added to the end of the record.
	while (!stack.is_empty()) {
		polish_record.push_back(stack.top());
		stack.pop();
	}
}
void Expression::set_values() {
	for (List<std::string>::iterator it = var().begin(); it != var().end(); ++it) {
		double value = get_number(*it);
		for (List<Lexem>::iterator inside = PR().begin(); inside != PR().end(); ++inside)
			if ((*inside).name == *it) (*inside).value = value;
	}
}
double Expression::calculate() {
	double res{ 1 };
	Stack<Lexem> stack;
	for (List<Lexem>::iterator it = PR().begin(); it != PR().end(); ++it) {
		if ((*it).type == CONSTANT || (*it).type == VARIABLE)
			stack.push(*it);
		else if ((*it).type == FUNCTION) {
			double x{ stack.top().value };
			stack.pop();
			res = (*it).function(x);
			stack.push(Lexem("const", res, nullptr, CONSTANT));
		}
		else {
			double y{ stack.top().value };
			stack.pop();
			double x{ stack.top().value };
			stack.pop();
			if		((*it).name == "+") res = x + y;
			else if ((*it).name == "-") res = x - y;
			else if ((*it).name == "*") res = x * y;
			else if ((*it).name == "/") res = x / y;
			else if ((*it).name == "^") res = pow(x, y);
			stack.push(Lexem("const", res, nullptr, CONSTANT));
		}
	}
	res = stack.top().value;
	return res;
}

void Expression::print_PR() {
	for (List<Lexem>::iterator it = PR().begin(); it != PR().end(); ++it) {
		if ((*it).type == CONSTANT) std::cout << (*it).value;
		else if ((*it).type == VARIABLE) std::cout << (*it).value;
		else std::cout << (*it).name;
		std::cout << ' ';
	}
	std::cout << '\n';
}
List<Lexem>& Expression::expr() noexcept { return expression; }
List<Lexem>& Expression::PR() noexcept { return polish_record; }
List<std::string>& Expression::var() noexcept { return variables; }
const List<Lexem>& Expression::expr() const noexcept { return expression; }
const List<Lexem>& Expression::PR() const noexcept { return polish_record; }
const List<std::string>& Expression::var() const noexcept { return variables; }

std::ostream& operator<< (std::ostream& out, const Expression& expr) {
	for (List<Lexem>::iterator it = expr.expr().begin();
		it != expr.expr().end(); ++it)
		out << *it;
	return out;
}

#endif