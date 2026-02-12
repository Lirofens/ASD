 //Copyright 2025 Denis P.

#include <gtest/gtest.h>
#include "../lib_expression/expression.h"

TEST(ExpressionLibTest, parser_test_breckets) {
	EXPECT_NO_THROW(Parser::parse("(|x| + y) * [0.25 - sin(y - x)] + {x^2 * (-1.5)}"));
	EXPECT_NO_THROW(Parser::parse("(x)"));
	EXPECT_NO_THROW(Parser::parse("   | x |   "));
	EXPECT_NO_THROW(Parser::parse("  |  y   |  "));
	EXPECT_NO_THROW(Parser::parse("| x + y |"));
	EXPECT_NO_THROW(Parser::parse("{(| x + y |)}()[]"));
	EXPECT_NO_THROW(Parser::parse("{(z - 40) + | x + y |}"));
	EXPECT_NO_THROW(Parser::parse("||x| - |y - x| + |x|| + |y|"));
	EXPECT_NO_THROW(Parser::parse("|-|-x| - y * |y - x| + |x|| - |y|"));
	EXPECT_NO_THROW(Parser::parse("||x|-|y||"));
	EXPECT_NO_THROW(Parser::parse("{(z - 40) + | x + y |}"));

	EXPECT_ANY_THROW(Parser::parse("    "));
	EXPECT_ANY_THROW(Parser::parse("( )"));
	EXPECT_ANY_THROW(Parser::parse("| - |"));
	EXPECT_ANY_THROW(Parser::parse("|y - x| |"));
	EXPECT_ANY_THROW(Parser::parse("| * |"));
	EXPECT_ANY_THROW(Parser::parse("{(z - 40) + | x + y| |}"));
	EXPECT_ANY_THROW(Parser::parse("([x + y)"));
	EXPECT_ANY_THROW(Parser::parse("({[}]x + y)"));
	EXPECT_ANY_THROW(Parser::parse("("));
	EXPECT_ANY_THROW(Parser::parse("  [ {     ]   "));
	EXPECT_ANY_THROW(Parser::parse("{(z - 40) + (| x + y |})"));

}

TEST(ExpressionLibTest, parser_test_operators) {
	EXPECT_ANY_THROW(Parser::parse("1.25 ??? sin(y)"));
	EXPECT_ANY_THROW(Parser::parse("y^"));
	EXPECT_ANY_THROW(Parser::parse("[sin(y - x)^]"));
	EXPECT_ANY_THROW(Parser::parse("([x] + / y)"));
	EXPECT_ANY_THROW(Parser::parse("+"));
	EXPECT_ANY_THROW(Parser::parse("(^)"));
	EXPECT_ANY_THROW(Parser::parse("x +   "));
	EXPECT_ANY_THROW(Parser::parse("x * -y"));
	EXPECT_ANY_THROW(Parser::parse("x - *  -y"));

	EXPECT_NO_THROW(Parser::parse("x - +  -y"));
	EXPECT_NO_THROW(Parser::parse(" -y"));
	EXPECT_NO_THROW(Parser::parse("|-1.25 - 4|"));
	EXPECT_NO_THROW(Parser::parse("| 1.25 - sin(y)|"));
	EXPECT_NO_THROW(Parser::parse("x * (-y)"));
	EXPECT_NO_THROW(Parser::parse("x * (-   -+-y)"));
	EXPECT_NO_THROW(Parser::parse("x + +y"));
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
	EXPECT_NO_THROW(Parser::parse("(0.9) - -   20"));
	EXPECT_NO_THROW(Parser::parse("0.9 /     20"));
	EXPECT_NO_THROW(Parser::parse("x /     20"));
	EXPECT_NO_THROW(Parser::parse("x^20"));
	EXPECT_NO_THROW(Parser::parse("  20  "));
	EXPECT_NO_THROW(Parser::parse("20"));
}

TEST(ExpressionLibTest, parser_test_variable_and_func) {
	switch (0) case 0: default: if (::testing::internal::AlwaysTrue()) {
		bool gtest_caught_any = false; try {
			if (::testing::internal::AlwaysTrue()) {
				Parser::parse("sinU(y - x)");
			}
			else static_assert(true, "");
		}
		catch (const error_in_expr& error) {
			gtest_caught_any = true;
		} if (!gtest_caught_any) {
			goto gtest_label_testanythrow_73;
		}
	}
	else gtest_label_testanythrow_73 : ::testing::internal::AssertHelper(::testing::TestPartResult::kNonFatalFailure, "C:\\Users\\Äåíèñ\\source\\github\\ASD\\tests\\test_expression.cpp", 73, "Expected: " "Parser::parse(\"sinU(y - x)\")" " throws an exception.\n" "  Actual: it doesn't.") = ::testing::Message();

	EXPECT_NO_THROW(Parser::parse("x"));
	EXPECT_NO_THROW(Parser::parse(" x "));
	EXPECT_NO_THROW(Parser::parse(" _3a23 + 20"));

	switch (0) case 0: default: if (::testing::internal::AlwaysTrue()) {
		bool gtest_caught_any = false; try {
			if (::testing::internal::AlwaysTrue()) {
				Parser::parse("x x");
			}
			else static_assert(true, "");
		}
		catch (const error_in_expr& error) {
			gtest_caught_any = true;
		} if (!gtest_caught_any) {
			goto gtest_label_testanythrow_92;
		}
	}
					 else gtest_label_testanythrow_92 : ::testing::internal::AssertHelper(::testing::TestPartResult::kNonFatalFailure, "C:\\Users\\Äåíèñ\\source\\github\\ASD\\tests\\test_expression.cpp", 92, "Expected: " "Parser::parse(\"x x\")" " throws an exception.\n" "  Actual: it doesn't.") = ::testing::Message();
	EXPECT_ANY_THROW(Parser::parse("  x x"));
	EXPECT_ANY_THROW(Parser::parse("x x    "));
	EXPECT_ANY_THROW(Parser::parse(" x ([x] + y)"));
	switch (0) case 0: default: if (::testing::internal::AlwaysTrue()) {
		bool gtest_caught_any = false; try {
			if (::testing::internal::AlwaysTrue()) {
				Parser::parse(" _ + 20");
			}
			else static_assert(true, "");
		}
		catch (const error_in_expr& error) {
			gtest_caught_any = true;
		} if (!gtest_caught_any) {
			goto gtest_label_testanythrow_109;
		}
	}
					 else gtest_label_testanythrow_109 : ::testing::internal::AssertHelper(::testing::TestPartResult::kNonFatalFailure, "C:\\Users\\Äåíèñ\\source\\github\\ASD\\tests\\test_expression.cpp", 109, "Expected: " "Parser::parse(\" _ + 20\")" " throws an exception.\n" "  Actual: it doesn't.") = ::testing::Message();
	switch (0) case 0: default: if (::testing::internal::AlwaysTrue()) {
		bool gtest_caught_any = false; try {
			if (::testing::internal::AlwaysTrue()) {
				Parser::parse(" _323 + 20");
			}
			else static_assert(true, "");
		}
		catch (const error_in_expr& error) {
			gtest_caught_any = true;
		} if (!gtest_caught_any) {
			goto gtest_label_testanythrow_123;
		}
	}
					 else gtest_label_testanythrow_123 : ::testing::internal::AssertHelper(::testing::TestPartResult::kNonFatalFailure, "C:\\Users\\Äåíèñ\\source\\github\\ASD\\tests\\test_expression.cpp", 123, "Expected: " "Parser::parse(\" _323 + 20\")" " throws an exception.\n" "  Actual: it doesn't.") = ::testing::Message();
	EXPECT_ANY_THROW(Parser::parse(" ([x] + y) x"));
}

TEST(ExpressionLibTest, correct_construction_of_the_reverse_Polish_notation_and_calculations_1) {
	Expression ex("|x + y|");
	List<Lexem> polish_record;
	polish_record.push_back(Lexem("x", 0, nullptr, VARIABLE));
	polish_record.push_back(Lexem("y", 0, nullptr, VARIABLE));
	polish_record.push_back(Lexem("+", 0, nullptr, OPERATOR));
	polish_record.push_back(Lexem("abs", 0, module, FUNCTION));

	Node<Lexem>* cur_1 = ex.PR().node(0);
	Node<Lexem>* cur_2 = polish_record.node(0);
	while (cur_1 != cur_2) {
		EXPECT_EQ(cur_1->value.name, cur_2->value.name);
		cur_1 = cur_1->next;
		cur_2 = cur_2->next;
	}
	ex.print_PR();
}

TEST(ExpressionLibTest, correct_construction_of_the_reverse_Polish_notation_and_calculations_2) {
	Expression ex("(|x| + y) * [0.25 - sin(y - x)] + {x^2 * (-1.5)}");
	List<Lexem> polish_record;
	polish_record.push_back(Lexem("x", 0, nullptr, VARIABLE));
	polish_record.push_back(Lexem("abs", 0, module, FUNCTION));
	polish_record.push_back(Lexem("y", 0, nullptr, VARIABLE));
	polish_record.push_back(Lexem("+", 0, nullptr, OPERATOR));
	polish_record.push_back(Lexem("const", 0, module, FUNCTION));
	polish_record.push_back(Lexem("y", 0, nullptr, VARIABLE));
	polish_record.push_back(Lexem("x", 0, nullptr, VARIABLE));
	polish_record.push_back(Lexem("-", 0, nullptr, OPERATOR));
	polish_record.push_back(Lexem("sin", 0, module, FUNCTION));
	polish_record.push_back(Lexem("-", 0, nullptr, OPERATOR));
	polish_record.push_back(Lexem("*", 0, nullptr, OPERATOR));
	polish_record.push_back(Lexem("x", 0, nullptr, VARIABLE));
	polish_record.push_back(Lexem("const", 0, module, FUNCTION));
	polish_record.push_back(Lexem("^", 0, nullptr, OPERATOR));
	polish_record.push_back(Lexem("const", 0, module, FUNCTION));
	polish_record.push_back(Lexem("const", 0, module, FUNCTION));
	polish_record.push_back(Lexem("-", 0, nullptr, OPERATOR));
	polish_record.push_back(Lexem("*", 0, nullptr, OPERATOR));
	polish_record.push_back(Lexem("+", 0, nullptr, OPERATOR));

	Node<Lexem>* cur_1 = ex.PR().node(0);
	Node<Lexem>* cur_2 = polish_record.node(0);
	while (cur_1 != cur_2) {
		EXPECT_EQ(cur_1->value.name, cur_2->value.name);
		cur_1 = cur_1->next;
		cur_2 = cur_2->next;
	}
}

TEST(ExpressionLibTest, correct_calculate) {
	Expression ex1("10 * |-10| + 20");
	EXPECT_EQ(ex1.calculate(), 120);

	Expression ex2("10 / |-10| + 10");
	EXPECT_EQ(ex2.calculate(), 11);

	Expression ex3("sin(120)");
	EXPECT_TRUE(ex3.calculate() - std::sin(120) < 0.001);

	Expression ex4("tan(120)");
	EXPECT_TRUE(ex4.calculate() - std::tan(120) < 0.001);

	Expression ex5("cos(120)");
	EXPECT_TRUE(ex5.calculate() - std::cos(120) < 0.001);
}