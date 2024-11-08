#pragma once

#include "postfix_operation.h"

class PostfixNumber : public PostfixOperation {
public:
    PostfixNumber(double value) : PostfixOperation(OpCode::NUM), m_Value(value) {}

    double Value() const noexcept { return m_Value; }

private:
    double m_Value;
};