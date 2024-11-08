#include "postfix.h"
#include "const_provider.h"
#include "gtest/gtest.h"

TEST(PostfixTest, can_store_infix)
{
    std::string infix = "a + PI - 123 + 456 * (789 - 10) / 3.14 * E - sin(x)";
    Postfix postfix(infix);
    EXPECT_EQ(postfix.GetInfix(), infix);
}

TEST(PostfixTest, can_parse_single_number)
{
    Postfix postfix("199");
    auto p = postfix.GetPostfix();
    EXPECT_EQ(p.size(), 1);
    EXPECT_EQ(p[0]->ToString(), std::to_string(199.0));
}

TEST(PostfixTest, can_parse_single_variable)
{
    Postfix postfix("my_variable");
    auto p = postfix.GetPostfix();
    EXPECT_EQ(p.size(), 1);
    EXPECT_EQ(p[0]->ToString(), "my_variable");
}

TEST(PostfixTest, can_parse_sum)
{
    Postfix postfix("10 + PI");
    auto p = postfix.GetPostfix();
    EXPECT_EQ(p.size(), 3);
    EXPECT_EQ(p[0]->ToString(), std::to_string(10.0));
    EXPECT_EQ(p[1]->ToString(), "PI");
    EXPECT_EQ(p[2]->ToString(), "+");
}

TEST(PostfixTest, can_parse_unary_minus)
{
    Postfix postfix("-10");
    auto p = postfix.GetPostfix();
    EXPECT_EQ(p.size(), 2);
    EXPECT_EQ(p[0]->ToString(), std::to_string(10.0));
    EXPECT_EQ(p[1]->ToString(), "-u");
}

TEST(PostfixText, can_parse_multiplication)
{
    Postfix postfix("10 * PI");
    auto p = postfix.GetPostfix();
    EXPECT_EQ(p.size(), 3);
    EXPECT_EQ(p[0]->ToString(), std::to_string(10.0));
    EXPECT_EQ(p[1]->ToString(), "PI");
    EXPECT_EQ(p[2]->ToString(), "*");
}

TEST(PostfixText, can_parse_subtraction)
{
    Postfix postfix("10 - PI");
    auto p = postfix.GetPostfix();
    EXPECT_EQ(p.size(), 3);
    EXPECT_EQ(p[0]->ToString(), std::to_string(10.0));
    EXPECT_EQ(p[1]->ToString(), "PI");
    EXPECT_EQ(p[2]->ToString(), "-");
}

TEST(PostfixText, can_parse_division)
{
    Postfix postfix("10 / PI");
    auto p = postfix.GetPostfix();
    EXPECT_EQ(p.size(), 3);
    EXPECT_EQ(p[0]->ToString(), std::to_string(10.0));
    EXPECT_EQ(p[1]->ToString(), "PI");
    EXPECT_EQ(p[2]->ToString(), "/");
}

TEST(PostfixTest, can_parse_sin)
{
    Postfix postfix("sin(10)");
    auto p = postfix.GetPostfix();
    EXPECT_EQ(p.size(), 2);
    EXPECT_EQ(p[0]->ToString(), std::to_string(10.0));
    EXPECT_EQ(p[1]->ToString(), "sin");
}

TEST(PostfixTest, can_parse_cos)
{
    Postfix postfix("cos(10)");
    auto p = postfix.GetPostfix();
    EXPECT_EQ(p.size(), 2);
    EXPECT_EQ(p[0]->ToString(), std::to_string(10.0));
    EXPECT_EQ(p[1]->ToString(), "cos");
}

TEST(PostfixTest, can_parse_exp)
{
    Postfix postfix("exp(10)");
    auto p = postfix.GetPostfix();
    EXPECT_EQ(p.size(), 2);
    EXPECT_EQ(p[0]->ToString(), std::to_string(10.0));
    EXPECT_EQ(p[1]->ToString(), "exp");
}

TEST(PostfixTest, can_perform_simple_calculation)
{
    Postfix postfix("10 + 15");
    EXPECT_EQ(postfix.Calculate(), 25.0);
}

TEST(PostfixTest, can_handle_operator_precedence)
{
    Postfix postfix("10 + 15 * 2");
    EXPECT_EQ(postfix.Calculate(), 40.0);
}

TEST(PostfixTest, can_perform_complex_calculation)
{
    Postfix postfix("sin(3.1415926535 / 6) + cos(3.1415926535 * .25)*((exp(2) - 1)/3) - 5/exp(1) + sin(3.1415926535/3)*cos(3.1415926535/6)");
    EXPECT_LE(abs(postfix.Calculate() - 0.916), 0.01);
}

TEST(Postfix, can_use_variables)
{
    Postfix postfix("sin(PI / 6) + cos(PI * .25)*((exp(2) - 1)/3) - 5/exp(1) + sin(PI/3)*cos(PI/6)");
    auto provider = std::make_shared<ConstProvider>(std::unordered_map<std::string, double>{
        {"PI", 3.1415926535}
    });
    EXPECT_LE(abs(postfix.Calculate(provider) - 0.916), 0.01);
}

TEST(Postfix, exception_on_unclosed)
{
    Postfix postfix("(10 + 20");
    EXPECT_ANY_THROW(postfix.GetPostfix());
}

TEST(Postfix, exception_on_too_many_parentheses)
{
    Postfix postfix("(10 + 20))");
    EXPECT_ANY_THROW(postfix.GetPostfix());
}

TEST(Postfix, exception_on_empty_parentheses)
{
    Postfix postfix("()");
    EXPECT_ANY_THROW(postfix.GetPostfix());
}

TEST(Postfix, exception_on_two_operators_in_a_row)
{
    Postfix postfix("10 + -20");
    EXPECT_ANY_THROW(postfix.GetPostfix());
}

TEST(Postfix, exception_on_binary_operator_without_left_argument)
{
    Postfix postfix("+100");
    EXPECT_ANY_THROW(postfix.GetPostfix());
}

TEST(Postfix, exception_on_binary_operator_without_right_argument)
{
    Postfix postfix("100*");
    EXPECT_ANY_THROW(postfix.GetPostfix());
}

TEST(Postfix, exception_on_function_use_without_parentheses)
{
    Postfix postfix("sin 10");
    EXPECT_ANY_THROW(postfix.GetPostfix());
}

TEST(Postfix, exception_on_zero_division)
{
    Postfix postfix("100 / 0");
    EXPECT_ANY_THROW(postfix.Calculate());
}