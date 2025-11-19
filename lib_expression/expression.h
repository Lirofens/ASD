#ifndef EXPRESSION_
#define EXPRESSION_

#include <iostream>
#include <string>
#include "list.h"
#include "stack.h"
#include "algorithms.h"

enum TypeLexem { OPEN_B, CLOSE_B, VARIABLE, OPERATOR, CONSTANT, FUNCTION };

struct Lexem {
	std::string name;
	double value;
	double (*function)(double);
	TypeLexem type;
	Lexem(std::string n, double v, double (*f)(double), TypeLexem t)
		: name(n), value(v), function(f), type(t) {}

	friend std::ostream& operator<< (std::ostream& out, const Lexem& lexem);
	};

std::ostream& operator<< (std::ostream& out, const Lexem& lexem) {
	if (lexem.type == CONSTANT) out << lexem.value;
	else if (lexem.type == OPERATOR) out << ' ' << lexem.name << ' ';
	else out << lexem.name;
	return out;
}

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
			throw std::logic_error("The constant must be followed by a closing bracket or an operator.");
		j = (i - number.size() == 0) ? i - number.size() : i - number.size() - 1;
		while (str[j] == ' ' && j > 0) j--;
		if (!(findC(str[j], "([{|+-*/^~")) && j != 0) {
			i -= number.size();
			throw std::logic_error("A constant must be preceded by a open bracket or an operator.");
		}
		double value = std::stod(number);
		list.push_back(*(new Lexem("const", value, nullptr, CONSTANT)));
		i--;
	}
	void push_operator(List<Lexem>& list, const std::string& str, size_t& i) {
		size_t j{ (i == str.size() - 1) ? i : i + 1};
		while (str[j] == ' ' && j < str.size() - 1) j++;
		if (str[j] == ' ' && j == str.size() - 1) throw std::logic_error("The expression ends with an operator");
		if (findC(str[j], ")]}|+-*/^") || (str[i] == '~' && str[j] == '~'))
			throw std::logic_error("There cannot be a opening bracket or another operator before the operator.");
		if (str[i] == '~') {
			j = (i == 0) ? i : i - 1;
			while (str[j] == ' ' && j > 0) j--;
			if (findC(str[j], "*/^"))
				throw std::logic_error("There cannot be another operator after the operator.");
			list.push_back(*(new Lexem("~", 0, nullptr, OPERATOR)));
			return;
		}
		j = (i == 0) ? i : i - 1;
		while (str[j] == ' ' && j > 0) j--;
		if (str[j] == ' ' && j == 0) throw std::logic_error("The expression begins with an operator");
		if (findC(str[j], "([{|+-*/^"))
			throw std::logic_error("There cannot be a closing bracket or another operator after the operator.");

		if		(str[i] == '+') list.push_back(*(new Lexem("+", 0, nullptr, OPERATOR)));
		else if (str[i] == '-') list.push_back(*(new Lexem("-", 0, nullptr, OPERATOR)));
		else if (str[i] == '*') list.push_back(*(new Lexem("*", 0, nullptr, OPERATOR)));
		else if (str[i] == '/') list.push_back(*(new Lexem("/", 0, nullptr, OPERATOR)));
		else					list.push_back(*(new Lexem("^", 0, nullptr, OPERATOR)));

	}
	void push_var_or_func(List<Lexem>& list, const std::string& str, size_t& i) {
		if (i < str.size() - 2 && str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n') { // sin
			if (str[i + 3] != '(') throw std::logic_error("There should be a bracket after the function.");
			list.push_back(*(new Lexem("sin", 0, sine, FUNCTION))); i += 2;
		}
		else if (i < str.size() - 2 && str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's') { // cos
			if (str[i + 3] != '(') throw std::logic_error("There should be a bracket after the function.");
			list.push_back(*(new Lexem("cos", 0, cosine, FUNCTION)));  i += 2;
		}
		else if (i < str.size() - 2 && str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n') { // tan
			if (str[i + 3] != '(') throw std::logic_error("There should be a bracket after the function.");
			list.push_back(*(new Lexem("tan", 0, tangent, FUNCTION)));  i += 2;
		}
		else { // variable
			std::string var;
			while ((is_letter(str[i]) || is_digit(str[i]) || str[i] == '_') && i < str.size())
				var += str[i++];
			if (var[0] == '_') {
				if (var.size() == 1) {
					i--;
					throw std::invalid_argument("Invalid variable name.");
				}
				for (size_t j = 0; j < var.size(); j++) {
					if (is_letter(var[j])) break;
					if (j == var.size() - 1 && !is_letter(var[j])) throw std::invalid_argument("Invalid variable name.");
				}
			}
			size_t j{ (i == str.size()) ? i - 1 : i };
			while (str[j] == ' ' && j < str.size() - 1) j++;
			if ((!findC(str[j], "+-*/^)]}|")) && j != str.size() - 1)
				throw std::logic_error("The variable must be followed by a space or an operator.");
			j = (i - var.size() == 0) ? i - var.size() : i - var.size() - 1;
			while (str[j] == ' ' && j > 0) j--;
			if (!(findC(str[j], "([{|+-*/^~")) && j != 0) {
				i -= var.size();
				throw std::logic_error("A variable must be preceded by a open bracket or an operator.");
			}
			list.push_back(*(new Lexem(var, 0, nullptr, VARIABLE)));
			i--;
		}
	}

	List<Lexem>& parse(std::string str) {
		std::string brackets;
		for (size_t j = 0; j < str.size(); ++j)
			if (findC(str[j], "([{}])|") || (str[j] == '~' && str[j + 1] == '|')
				|| (j > 0 && str[j] == '~' && str[j - 1] == '|')) brackets.push_back(str[j]);
		if (!check_brackets(brackets)) throw std::exception("Incorrect brackets.");

		List<Lexem> *list = new List<Lexem>();
		size_t i;
		//try {
			for (i = 0; i < str.size(); i++) {
				if (str[i] == ' ') continue;
				else if (str[i] == '(') list->push_back(*(new Lexem("(", 0, nullptr, OPEN_B)));
				else if (str[i] == '[') list->push_back(*(new Lexem("[", 0, nullptr, OPEN_B)));
				else if (str[i] == '{') list->push_back(*(new Lexem("{", 0, nullptr, OPEN_B)));
				else if (str[i] == ')') list->push_back(*(new Lexem(")", 0, nullptr, CLOSE_B)));
				else if (str[i] == ']') list->push_back(*(new Lexem("]", 0, nullptr, CLOSE_B)));
				else if (str[i] == '}') list->push_back(*(new Lexem("}", 0, nullptr, CLOSE_B)));

				else if (str[i] == '~' && str[i + 1] == '|') { list->push_back(*(new Lexem("|", 0, nullptr, OPEN_B))); i++; }
				else if (str[i] == '|' && str[i + 1] == '~') { list->push_back(*(new Lexem("|", 0, nullptr, CLOSE_B))); i++; }

				else if (findC(str[i], "+-*/^~"))			 push_operator(*list, str, i);
				else if (is_digit(str[i]))					 push_const(*list, str, i);
				else if (is_letter(str[i]) || str[i] == '_') push_var_or_func(*list, str, i);
				else throw std::logic_error("Error in writing an arithmetic expression.");
			}
			return *list;
		/*}
		catch (...) {
			std::cout << str << std::endl;
			for (size_t j = 0; j < i; j++) std::cout << ' ';
			std::cout << '^' << std::endl;
			for (size_t j = 0; j < i; j++) std::cout << ' ';
			std::cout << '|' << std::endl;
			throw std::logic_error("Error in writing an arithmetic expression.");
		}*/
	}
}



template <class T>
class Expression {
	
};

#endif