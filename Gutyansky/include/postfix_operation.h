#pragma once

#include "opcodes.h"

class PostfixOperation
{
public:
    PostfixOperation(OpCode opcode) : m_OpCode(opcode) {}
    virtual ~PostfixOperation() {}

    OpCode Op() const noexcept { return m_OpCode; }

private:
    OpCode m_OpCode;
};