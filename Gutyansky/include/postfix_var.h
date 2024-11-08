#pragma once

#include <string>
#include "postfix_operation.h"

class PostfixVar : public IPostfixOperation {
public:
    PostfixVar(const std::string& name) : m_Name(name) {}

    std::string Name() const noexcept { return m_Name; }

    void Execute(ExecutionContext& context) override
    {
        context.Push(context.GetVariable(Name()));
    }

    std::string ToString() override
    {
        return Name();
    }

private:
    std::string m_Name;
};