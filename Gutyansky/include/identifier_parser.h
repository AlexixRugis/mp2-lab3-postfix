#pragma once
#include <optional>
#include "lexer_context.h"
#include "lexem_parser.h"

namespace Lexer {
    class IdentifierParser final : public ILexemParser
    {
    public:
        std::optional<Token> TryParse(LexerContext& context);
    };
}
