// Copyright 2025 Denis O.

#define ADD_SPACES 17
#include <iostream>
#include <string>
#include "expression.h"

int main() {
	std::string string;
	try {
		while (true) {
			//Reading the line entered by the user.
			std::cout << "\nEnter your expression. Available operations and functions: +, -, *, /, ^, sin, cos, tan, |x|."
					  << "\nExample: (|x| + y) * |0.25 - sin(y - x)| +{y / |x ^ 2 * (-1.5)|}\n" << std::endl;
			std::cout << "Enter your expression: ";
			std::getline(std::cin, string);

			//String parsing and exception handling.
			std::cout << "\nYour expression: ";
			Expression expr(string);
			std::cout << expr;

			bool choice = true;
			while (choice) {
				//Choosing a further action with verification of the correctness of the input.
				std::cout << "\nWhat's next? Overwrite an expression (0), set values for the variables (1)?" << std::endl;
				std::string s;
				std::cin >> s;
				if (s.size() != 1 || (s[0] != '1' && s[0] != '0')) continue;
				choice = (s[0] == '1') ? true : false;
				if (!choice) break;

				//Setting values for variables.
				if (!expr.var().size()) std::cout << "There are no variables in your expression." << std::endl;
				else std::cout << "Set values for your variables:" << std::endl;
				expr.set_values();

				//Performing calculations based on reverse Polish notation.
				std::cout << "\nPolish notation: ";
				expr.print_PR();
				std::cout << "Answer: " << expr.calculate() << std::endl;
				
				//Program termination or change of variable values.
				while (true) {
					std::cout << "\nWhat's next? End the program (0) or go back a step (1)?" << std::endl;
					std::string s;
					std::cin >> s;
					if (s.size() != 1 || (s[0] != '1' && s[0] != '0')) continue;
					choice = (s[0] == '1') ? true : false;
					break;
				}
				if (!choice) { choice = true;  break; }
				std::cin.ignore(32767, '\n');
			}
			std::cin.ignore(32767, '\n');
			if (choice) break;
		}
	}
	//Exception Handlers.
	catch (error_in_expr& error) {
		std::cout << string << std::endl;
		for (size_t j = 0; j < error.where() + ADD_SPACES; j++) std::cout << ' ';
		std::cout << '^' << std::endl;
		for (size_t j = 0; j < error.where() + ADD_SPACES; j++) std::cout << ' ';
		std::cout << '|' << std::endl;
		std::cout << error.what();
	}
	catch (std::exception& error) {
		std::cout << string << std::endl;
		std::cout << error.what();
	}
}