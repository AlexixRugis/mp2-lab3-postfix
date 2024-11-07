#pragma once
#include <string>

enum class OpCode {
    NUM, VAR, ADD, SUB, MULT, DIV, CALL
};

std::string ToString(OpCode opcode);