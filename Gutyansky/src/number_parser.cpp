#include "number_parser.h"
#include <string>

namespace Lexer {
    std::optional<Token> NumberParser::TryParse(LexerContext& context)
    {
        std::string parsedNumber;
        uint64_t addedDigits = 0;

        while (isdigit(context.CurrentChar()))
        {
            parsedNumber.push_back(context.CurrentChar());
            context.NextChar();
            addedDigits++;
        }

        if (addedDigits == 0)
        {
            return std::nullopt;
        }

        return Token(TokenType::NUM, parsedNumber);
    }
}