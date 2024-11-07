#pragma once

#include "opcodes.h"

class PostfixMember
{
public:
    PostfixMember(OpCode opcode) : m_OpCode(opcode) {}
    virtual ~PostfixMember() {}

    OpCode Op() const noexcept { return m_OpCode; }

private:
    OpCode m_OpCode;
};