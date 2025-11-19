// Copyright 2025 Denis P.

#include <gtest/gtest.h>
#include "../lib_expression/expression.h"

TEST(ExpressionLibTest, parser_test_breckets) {
	EXPECT_NO_THROW(Parser::parse("([x] + y) * [1.25 - sin(y - x)] + {x^2 - 0.9}"));
	EXPECT_NO_THROW(Parser::parse("(x)"));
	EXPECT_NO_THROW(Parser::parse(""));
	EXPECT_NO_THROW(Parser::parse("( )"));
	EXPECT_NO_THROW(Parser::parse("   ~| |~   "));
	EXPECT_NO_THROW(Parser::parse("  ~|     |~  "));
	EXPECT_NO_THROW(Parser::parse("~| x + y |~"));
	EXPECT_NO_THROW(Parser::parse("{(~| x + y |~)}()[]"));
	EXPECT_NO_THROW(Parser::parse("{(z - 40) + ~| x + y |~}"));
	EXPECT_NO_THROW(Parser::parse("~||~"));

	EXPECT_ANY_THROW(Parser::parse("~ || ~"));
	EXPECT_ANY_THROW(Parser::parse("~|    |"));
	EXPECT_ANY_THROW(Parser::parse("| |~"));
	EXPECT_ANY_THROW(Parser::parse("([x + y)"));
	EXPECT_ANY_THROW(Parser::parse("({[}]x + y)"));
	EXPECT_ANY_THROW(Parser::parse("("));
	EXPECT_ANY_THROW(Parser::parse("  [ {     ]   "));
	EXPECT_ANY_THROW(Parser::parse("{(z - 40) + ~| x + y |}"));
	EXPECT_ANY_THROW(Parser::parse("{(z - 40) + (~| x + y |~})"));

}

TEST(ExpressionLibTest, parser_test_operators) {
	EXPECT_ANY_THROW(Parser::parse("1.25 ??? sin(y)"));
	EXPECT_ANY_THROW(Parser::parse(" - y"));
	EXPECT_ANY_THROW(Parser::parse("-y"));
	EXPECT_ANY_THROW(Parser::parse("y^"));
	EXPECT_ANY_THROW(Parser::parse("y +   "));
	EXPECT_ANY_THROW(Parser::parse("~|-1.25 - 4|~"));
	EXPECT_ANY_THROW(Parser::parse("[sin(y - x)^]"));
	EXPECT_ANY_THROW(Parser::parse("([x] + / y)"));
	EXPECT_ANY_THROW(Parser::parse("+"));
	EXPECT_ANY_THROW(Parser::parse("+ x"));
	EXPECT_ANY_THROW(Parser::parse("(^)"));
	EXPECT_ANY_THROW(Parser::parse("x * ~y"));

	EXPECT_NO_THROW(Parser::parse("~| 1.25 - sin(y)|~"));
	EXPECT_NO_THROW(Parser::parse("x + ~y"));
	EXPECT_NO_THROW(Parser::parse("10 + y"));
	EXPECT_NO_THROW(Parser::parse("x+y"));
	EXPECT_NO_THROW(Parser::parse("x/ y"));
	EXPECT_NO_THROW(Parser::parse("x    /       y"));
}

TEST(ExpressionLibTest, parser_test_const) {
	EXPECT_ANY_THROW(Parser::parse("[1.25QQQ - sin(y - x)]"));
	EXPECT_ANY_THROW(Parser::parse("1.25.34 - sin(y - x)"));
	EXPECT_ANY_THROW(Parser::parse(" 1000 ([x] + y)"));
	EXPECT_ANY_THROW(Parser::parse(" ([x] + y) 100"));

	EXPECT_NO_THROW(Parser::parse("0.9+20"));
	EXPECT_NO_THROW(Parser::parse("(0.9) - ~   20"));
	EXPECT_NO_THROW(Parser::parse("0.9 /     20"));
	EXPECT_NO_THROW(Parser::parse("x /     20"));
	EXPECT_NO_THROW(Parser::parse("x^20"));
	EXPECT_NO_THROW(Parser::parse("  20  "));
	EXPECT_NO_THROW(Parser::parse("20"));
}

TEST(ExpressionLibTest, parser_test_variable_and_func) {
	EXPECT_ANY_THROW(Parser::parse("sinU(y - x)"));

	EXPECT_NO_THROW(Parser::parse("x"));
	EXPECT_NO_THROW(Parser::parse(" x "));
	EXPECT_NO_THROW(Parser::parse(" _3a23 + 20"));

	EXPECT_ANY_THROW(Parser::parse(" x ([x] + y)"));
	EXPECT_ANY_THROW(Parser::parse(" _ + 20"));
	EXPECT_ANY_THROW(Parser::parse(" _323 + 20"));
	EXPECT_ANY_THROW(Parser::parse(" ([x] + y) x"));

}