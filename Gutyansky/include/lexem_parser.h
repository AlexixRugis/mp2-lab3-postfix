#pragma once
#include <optional>
#include "lexer_context.h"
#include "lexer_token.h"

namespace Lexer {
    class ILexemParser
    {
    public:
        virtual std::optional<Token> TryParse(LexerContext& context) = 0;
        virtual ~ILexemParser() {};
    };
}
