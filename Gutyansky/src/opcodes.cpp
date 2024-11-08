#include "opcodes.h"

std::string ToString(OpCode opcode)
{
    switch (opcode)
    {
    case OpCode::NUM: return "NUM";
    case OpCode::VAR: return "VAR";
    case OpCode::ADD: return "ADD";
    case OpCode::SUB: return "SUB";
    case OpCode::MULT: return "MULT";
    case OpCode::DIV: return "DIV";
    case OpCode::CALL: return "CALL";
    case OpCode::UMINUS: return "UMINUS";
    default: return "UNKNOWN";
    }
}