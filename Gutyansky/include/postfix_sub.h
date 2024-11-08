#pragma once

#include "postfix_operation.h"

class PostfixSub : public PostfixOperation {
public:
    PostfixSub() : PostfixOperation(OpCode::SUB) {}

};