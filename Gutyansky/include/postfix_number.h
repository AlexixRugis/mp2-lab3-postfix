#pragma once

#include "postfix_operation.h"

class PostfixNumber : public IPostfixOperation
{
public:
    PostfixNumber(double value) : m_Value(value) {}

    double Value() const noexcept { return m_Value; }

    void Execute(ExecutionContext& context) override
    {
        context.Push(Value());
    }

    std::string ToString() override
    {
        return std::to_string(Value());
    }

private:
    double m_Value;
};