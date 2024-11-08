#pragma once

#include <string>
#include <memory>
#include "variable_provider.h"
#include "lexer.h"
#include "stack.h"
#include "postfix_operation.h"

class Postfix final
{
public:
    Postfix(const std::string& infix) : 
        m_Infix(infix), m_Lexer(infix), m_GeneratedPostfix(false) {}

    std::string GetInfix() const { return m_Infix; }
    std::vector<std::shared_ptr<IPostfixOperation>> GetPostfix()
    {
        if (!m_GeneratedPostfix) GeneratePostfix();

        return m_Postfix;
    }

    double Calculate(const std::shared_ptr<IVariableProvider>& variables);

private:
    std::string m_Infix;
    Lexer::Lexer m_Lexer;

    bool m_GeneratedPostfix;
    std::vector<std::shared_ptr<IPostfixOperation>> m_Postfix;

    void GeneratePostfix();
};
