#pragma once
#include <string>

namespace Lexer {
    enum class TokenType
    {
        NUM, ID, LPAR, RPAR,
        PLUS, MINUS, MULT, DIV,
        COMMA, ENDOFFILE
    };

    std::string ToString(TokenType type);

    class Token
    {
    public:
        Token(TokenType type, const std::string& value = "") : m_Type(type), m_Value(value) {}

        TokenType Type() const { return m_Type; }
        std::string Value() const { return m_Value; }

    private:
        TokenType m_Type;
        std::string m_Value;
    };
}