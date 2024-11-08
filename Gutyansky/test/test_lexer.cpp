#include <gtest/gtest.h>
#include "lexer.h"

TEST(LexerTest, empty_string_returns_eof)
{
    Lexer::Lexer lexer("");
    EXPECT_EQ(lexer.NextToken().Type(), Lexer::TokenType::ENDOFFILE);
}

TEST(LexerTest, can_parse_numbers)
{
    Lexer::Lexer lexer("1 2.2 0.0 .02 03.02.22");
    Lexer::Token tok = lexer.NextToken();
    EXPECT_EQ(tok.Type(), Lexer::TokenType::NUM);
    EXPECT_EQ(tok.Value(), "1");

    tok = lexer.NextToken();
    EXPECT_EQ(tok.Type(), Lexer::TokenType::NUM);
    EXPECT_EQ(tok.Value(), "2.2");

    tok = lexer.NextToken();
    EXPECT_EQ(tok.Type(), Lexer::TokenType::NUM);
    EXPECT_EQ(tok.Value(), "0.0");

    tok = lexer.NextToken();
    EXPECT_EQ(tok.Type(), Lexer::TokenType::NUM);
    EXPECT_EQ(tok.Value(), ".02");

    tok = lexer.NextToken();
    EXPECT_EQ(tok.Type(), Lexer::TokenType::NUM);
    EXPECT_EQ(tok.Value(), "03.02");
}

TEST(LexerTest, can_parse_symbols)
{
    Lexer::Lexer lexer("+ - * / ( )");

    Lexer::Token tok = lexer.NextToken();
    EXPECT_EQ(tok.Type(), Lexer::TokenType::PLUS);

    tok = lexer.NextToken();
    EXPECT_EQ(tok.Type(), Lexer::TokenType::MINUS);

    tok = lexer.NextToken();
    EXPECT_EQ(tok.Type(), Lexer::TokenType::MULT);

    tok = lexer.NextToken();
    EXPECT_EQ(tok.Type(), Lexer::TokenType::DIV);

    tok = lexer.NextToken();
    EXPECT_EQ(tok.Type(), Lexer::TokenType::LPAR);

    tok = lexer.NextToken();
    EXPECT_EQ(tok.Type(), Lexer::TokenType::RPAR);
}

TEST(LexerTest, can_parse_identifiers)
{
    Lexer::Lexer lexer("a ab AB aB _ABB PI E exp gbg765");
    Lexer::Token tok = lexer.NextToken();
    EXPECT_EQ(tok.Type(), Lexer::TokenType::ID);
    EXPECT_EQ(tok.Value(), "a");

    tok = lexer.NextToken();
    EXPECT_EQ(tok.Type(), Lexer::TokenType::ID);
    EXPECT_EQ(tok.Value(), "ab");

    tok = lexer.NextToken();
    EXPECT_EQ(tok.Type(), Lexer::TokenType::ID);
    EXPECT_EQ(tok.Value(), "AB");

    tok = lexer.NextToken();
    EXPECT_EQ(tok.Type(), Lexer::TokenType::ID);
    EXPECT_EQ(tok.Value(), "aB");

    tok = lexer.NextToken();
    EXPECT_EQ(tok.Type(), Lexer::TokenType::ID);
    EXPECT_EQ(tok.Value(), "_ABB");

    tok = lexer.NextToken();
    EXPECT_EQ(tok.Type(), Lexer::TokenType::ID);
    EXPECT_EQ(tok.Value(), "PI");

    tok = lexer.NextToken();
    EXPECT_EQ(tok.Type(), Lexer::TokenType::ID);
    EXPECT_EQ(tok.Value(), "E");

    tok = lexer.NextToken();
    EXPECT_EQ(tok.Type(), Lexer::TokenType::ID);
    EXPECT_EQ(tok.Value(), "exp");

    tok = lexer.NextToken();
    EXPECT_EQ(tok.Type(), Lexer::TokenType::ID);
    EXPECT_EQ(tok.Value(), "gbg765");
}

TEST(LexerTest, can_perform_lexical_analysis)
{
    Lexer::Lexer lexer("a + PI - 123 + 456 * (789 - 10) / 3.14 * E - sin(x)");

    std::vector<Lexer::TokenType> expectedTypes = {
        Lexer::TokenType::ID, Lexer::TokenType::PLUS, Lexer::TokenType::ID, Lexer::TokenType::MINUS,
        Lexer::TokenType::NUM, Lexer::TokenType::PLUS, Lexer::TokenType::NUM,
        Lexer::TokenType::MULT, Lexer::TokenType::LPAR, Lexer::TokenType::NUM, Lexer::TokenType::MINUS,
        Lexer::TokenType::NUM, Lexer::TokenType::RPAR, Lexer::TokenType::DIV,
        Lexer::TokenType::NUM, Lexer::TokenType::MULT, Lexer::TokenType::ID, Lexer::TokenType::MINUS,
        Lexer::TokenType::ID, Lexer::TokenType::LPAR, Lexer::TokenType::ID,
        Lexer::TokenType::RPAR, Lexer::TokenType::ENDOFFILE
    };

    for (auto expectedType : expectedTypes)
    {
        auto token = lexer.NextToken();
        EXPECT_EQ(token.Type(), expectedType);
    }
}

TEST(LexerTest, can_ignore_whitespace)
{
    Lexer::Lexer lexer("    123     + 456    ");

    auto token = lexer.NextToken();
    EXPECT_EQ(token.Type(), Lexer::TokenType::NUM);
    EXPECT_EQ(token.Value(), "123");

    token = lexer.NextToken();
    EXPECT_EQ(token.Type(), Lexer::TokenType::PLUS);

    token = lexer.NextToken();
    EXPECT_EQ(token.Type(), Lexer::TokenType::NUM);
    EXPECT_EQ(token.Value(), "456");
}

TEST(LexerTest, throw_on_unexpected_symbol)
{
    Lexer::Lexer lexer("123 + ?");
    lexer.NextToken();
    lexer.NextToken();
    EXPECT_ANY_THROW(lexer.NextToken());
}
