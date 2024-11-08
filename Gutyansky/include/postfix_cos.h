#pragma once

#include <cmath>
#include "postfix_operation.h"

class PostfixCos : public IPostfixOperation
{
public:
    void Execute(ExecutionContext& context) override
    {
        double a = context.Pop();
        context.Push(cos(a));
    }

    std::string ToString() override
    {
        return "cos";
    }

};