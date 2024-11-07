#include "lexer_context.h"
#include "lexer.h"

namespace Lexer {
    void LexerContext::NextChar()
    {
        m_Lexer->NextChar();
    }
}