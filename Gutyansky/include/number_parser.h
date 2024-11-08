#pragma once
#include <optional>
#include "lexer_context.h"
#include "lexem_parser.h"

namespace Lexer {
    class NumberParser final : public ILexemParser
    {
    public:
        std::optional<Token> TryParse(LexerContext& context);

    };
}