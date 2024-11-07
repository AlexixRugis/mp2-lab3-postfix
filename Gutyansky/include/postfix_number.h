#pragma once

#include "postfix_member.h"

class PostfixNumber : public PostfixMember {
public:
    PostfixNumber(double value) : PostfixMember(OpCode::NUM), m_Value(value) {}

    double Value() const noexcept { return m_Value; }

private:
    double m_Value;
};