#include "identifier_parser.h"
#include <unordered_map>
#include <string>

namespace Lexer {
    std::optional<Token> IdentifierParser::TryParse(LexerContext& context)
    {
        if (context.CurrentChar() != '_' && !isalpha(context.CurrentChar()))
        {
            return std::nullopt;
        }

        std::string ident;

        while (context.CurrentChar() == '_' || isalnum(context.CurrentChar()))
        {
            ident.push_back(context.CurrentChar());
            context.NextChar();
        }

        return Token(TokenType::ID, ident);
    }
}