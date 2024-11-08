#pragma once

#include "postfix_operation.h"

class PostfixMult : public IPostfixOperation {
public:
    void Execute(ExecutionContext& context) override
    {
        double b = context.Pop();
        double a = context.Pop();
        context.Push(a * b);
    }

    std::string ToString() override
    {
        return "*";
    }

};