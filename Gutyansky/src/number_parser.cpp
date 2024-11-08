#include "number_parser.h"
#include <string>

namespace Lexer {
    std::optional<Token> NumberParser::TryParse(LexerContext& context)
    {
        std::string parsedNumber;
        bool hasPoint = false;
        uint64_t addedDigits = 0;

        while (isdigit(context.CurrentChar()) || (context.CurrentChar() == '.' && !hasPoint))
        {
            if (context.CurrentChar() == '.') hasPoint = true;

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