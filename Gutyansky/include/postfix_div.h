#pragma once

#include "postfix_operation.h"

class PostfixDiv : public IPostfixOperation
{
public:
    void Execute(ExecutionContext& context) override
    {
        double b = context.Pop();
        double a = context.Pop();

        if (b == 0.0)
        {
            throw std::runtime_error(__FUNCTION__ ": Division by zero!");
        }

        context.Push(a / b);
    }

    std::string ToString() override
    {
        return "/";
    }

};