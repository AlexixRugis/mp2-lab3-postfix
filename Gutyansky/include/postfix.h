#pragma once

#include <string>
#include <memory>
#include "lexer.h"
#include "stack.h"
#include "postfix_operation.h"

class Postfix final
{
public:
    Postfix(const std::string& infix) : m_Infix(infix), m_Lexer(infix), m_GeneratedPostfix(false) {}

    std::string GetInfix() const { return m_Infix; }
    std::vector<std::shared_ptr<PostfixOperation>> GetPostfix()
    {
        if (!m_GeneratedPostfix) GeneratePostfix();

        return m_Postfix;
    }

    double Calculate();

private:
    std::string m_Infix;
    Lexer::Lexer m_Lexer;

    bool m_GeneratedPostfix;
    std::vector<std::shared_ptr<PostfixOperation>> m_Postfix;

    void GeneratePostfix();
};
