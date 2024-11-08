#pragma once

#include <cmath>
#include "postfix_operation.h"

class PostfixSin : public IPostfixOperation {
public:
    void Execute(ExecutionContext& context) override
    {
        double a = context.Pop();
        context.Push(sin(a));
    }

    std::string ToString() override
    {
        return "sin";
    }
};