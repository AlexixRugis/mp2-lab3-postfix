#pragma once

#include <string>
#include "execution_context.h"

class IPostfixOperation
{
public:
    virtual ~IPostfixOperation() = 0 {}
    virtual void Execute(ExecutionContext& context) = 0;
    virtual std::string ToString() = 0;
};