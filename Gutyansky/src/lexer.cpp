#include <iostream>
#include <sstream>
#include <unordered_map>
#include "lexer.h"
#include "number_parser.h"
#include "identifier_parser.h"
#include "symbol_parser.h"

namespace Lexer {
    Lexer::Lexer(const std::string& str) : m_Context(this), m_Text(str), m_TextIndex(0)
    {
        Commit();

        AddParser(std::make_shared<NumberParser>());
        AddParser(std::make_shared<SymbolParser>());
        AddParser(std::make_shared<IdentifierParser>());
    }

    Token Lexer::NextToken()
    {
        std::string val;
        TokenType type;
        bool found = false;

        while (!found)
        {
            if (m_TextIndex >= m_Text.size())
            {
                type = TokenType::ENDOFFILE;
                found = true;
                continue;
            } else if (isspace(m_Context.m_CurrentChar))
            {
                NextChar();
                Commit();
                continue;
            }

            for (auto& parser : m_LexemParsers)
            {
                std::optional<Token> token = parser.get()->TryParse(m_Context);
                if (token.has_value())
                {
                    type = token.value().Type();
                    val = token.value().Value();
                    found = true;
                    break;
                } else
                {
                    Rollback();
                }
            }

            if (!found)
            {
                std::string error = "Unexpected symbol:  ";
                NextChar();
                error.back() = m_Context.m_CurrentChar;
                ThrowError(error);
            }
        }

        Commit();

        return Token(type, std::move(val));
    }

    void Lexer::ThrowError(const std::string& error) const
    {
        std::cout << '(' << m_Context.m_CharNumber << ") " << error << std::endl;
        exit(-1);
    }

    void Lexer::NextChar()
    {
        if (m_TextIndex < m_Text.size() - 1)
        {
            m_Context.m_CurrentChar = m_Text[++m_TextIndex];
        } else
        {
            m_TextIndex = m_Text.size();
            m_Context.m_CurrentChar = EOF;
        }

        ++m_Context.m_CharNumber;
    }

    void Lexer::AddParser(const std::shared_ptr<ILexemParser>&& parser)
    {
        m_LexemParsers.push_back(parser);
    }

    void Lexer::Commit()
    {
        m_LastCharNumber = m_Context.CharNumber();
        m_LastTextIndex = m_TextIndex;
        m_Context.m_CurrentChar = m_Text[m_TextIndex];
    }

    void Lexer::Rollback()
    {
        m_Context.m_CharNumber = m_LastCharNumber;
        m_TextIndex = m_LastTextIndex;
        m_Context.m_CurrentChar = m_Text[m_TextIndex];
    }
}