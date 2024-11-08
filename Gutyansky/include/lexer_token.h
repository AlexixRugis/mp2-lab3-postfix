#pragma once
#include <string>

namespace Lexer {
    enum class TokenType
    {
        NONE,
        NUM, ID, LPAR, RPAR,
        PLUS, MINUS, MULT, DIV,
        ENDOFFILE
    };

    std::string ToString(TokenType type);

    class Token
    {
    public:
        Token(TokenType type = TokenType::NONE, const std::string& value = "") : m_Type(type), m_Value(value) {}


        TokenType Type() const { return m_Type; }
        std::string Value() const { return m_Value; }

    private:
        TokenType m_Type;
        std::string m_Value;
    };
}