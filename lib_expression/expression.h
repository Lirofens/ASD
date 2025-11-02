#ifndef EXPRESSION_
#define EXPRESSION_

#include "list.h"
#include "stack.h"
#include "algorithms.h"
#include <string>

// "A—z && _ && 0—9", "0—9", " ", "+-*/", "sin, cos, tan";

enum TypeLexem { OPEN_B, CLOSE_B, VARIABLE, OPERATOR, CONSTANT, FUNCTION };

struct Lexem {
	std::string name;
	double value;
	double(*function);
	TypeLexem type;
};

namespace Parser {

	List<Lexem> parse(std::string str) {
		if (!check_breckets(str)) throw std::exception("sds");
		List<Lexem> list;
		for (size_t i = 0; i < str.size(); ++i) {
			list.push_back();
		}
	}
}



template <class T>
class Expression {
	
};

#endif