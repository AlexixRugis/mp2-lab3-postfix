#pragma once

#include "postfix_operation.h"

class PostfixAdd : public PostfixOperation {
public:
    PostfixAdd() : PostfixOperation(OpCode::ADD) {}

};