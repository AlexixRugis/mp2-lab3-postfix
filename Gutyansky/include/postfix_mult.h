#pragma once

#include "postfix_operation.h"

class PostfixMult : public PostfixOperation {
public:
    PostfixMult() : PostfixOperation(OpCode::MULT) {}

};