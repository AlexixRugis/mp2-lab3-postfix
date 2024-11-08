#pragma once
#include <string>

enum class OpCode {
    NUM, VAR, ADD, SUB, MULT, DIV, CALL, UMINUS
};

std::string ToString(OpCode opcode);