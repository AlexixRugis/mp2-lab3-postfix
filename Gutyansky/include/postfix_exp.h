#pragma once

#include <cmath>
#include "postfix_operation.h"

class PostfixExp : public IPostfixOperation {
public:
    void Execute(ExecutionContext& context) override
    {
        double a = context.Pop();
        context.Push(exp(a));
    }

    std::string ToString() override
    {
        return "exp";
    }

};