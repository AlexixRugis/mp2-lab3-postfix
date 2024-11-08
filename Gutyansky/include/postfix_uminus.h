#pragma once

#include "postfix_operation.h"

class PostfixUMinus : public IPostfixOperation
{
public:
    void Execute(ExecutionContext& context) override
    {
        double a = context.Pop();
        context.Push(-a);
    }

    std::string ToString() override
    {
        return "-u";
    }
};