#include "lexer_token.h"


std::string Lexer::ToString(Lexer::TokenType tokenType)
{
    switch (tokenType)
    {
    case TokenType::NUM: return "NUM";
    case TokenType::ID: return "ID";
    case TokenType::LPAR: return "LPAR";
    case TokenType::RPAR: return "RPAR";
    case TokenType::PLUS: return "PLUS";
    case TokenType::MINUS: return "MINUS";
    case TokenType::MULT: return "MULT";
    case TokenType::DIV: return "DIV";
    case TokenType::COMMA: return "COMMA";
    case TokenType::ENDOFFILE: return "ENDOFFILE";
    }
    return "UNKNOWN"; // Fallback for any unhandled cases
}