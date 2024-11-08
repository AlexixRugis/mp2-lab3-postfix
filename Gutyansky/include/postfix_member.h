#pragma once

#include "lexer_token.h"

class PostfixMember {
public:
    explicit PostfixMember(Lexer::Token token = {}, int precedence = 0, bool unary = false) :
        m_Token(token), m_Precedence(precedence), m_Unary(unary) {}

    Lexer::Token Token() const noexcept { return m_Token; }
    Lexer::TokenType Type() const noexcept { return m_Token.Type(); }
    int Precedence() const noexcept { return m_Precedence; }
    bool IsUnary() const noexcept { return m_Unary; }

private:
    Lexer::Token m_Token;
    int m_Precedence;
    bool m_Unary;

};