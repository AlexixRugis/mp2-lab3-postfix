#pragma once

#include <string>
#include "lexer.h"
#include "stack.h"

class Postfix final
{
public:
    Postfix(const std::string& infix) : m_Infix(infix), m_Lexer(infix) {}

    std::string GetInfix() const noexcept { return m_Infix; }

    double Calculate();

private:
    std::string m_Infix;
    Lexer::Lexer m_Lexer;
};
