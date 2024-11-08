#include "symbol_parser.h"
#include <unordered_map>
#include <string>

namespace Lexer {
    static const std::unordered_map<char, TokenType> symbolsMap{
        { '(', TokenType::LPAR },
        { ')', TokenType::RPAR },
        { '+', TokenType::PLUS },
        { '-', TokenType::MINUS },
        { '*', TokenType::MULT },
        { '/', TokenType::DIV },
    };

    std::optional<Token> SymbolParser::TryParse(LexerContext& context)
    {
        auto iter = symbolsMap.find(context.CurrentChar());
        context.NextChar();

        if (iter == symbolsMap.end())
        {
            return std::nullopt;
        }

        return Token(iter->second);
    }
}