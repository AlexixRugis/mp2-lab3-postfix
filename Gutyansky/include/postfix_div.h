#pragma once

#include "postfix_operation.h"

class PostfixDiv : public PostfixOperation {
public:
    PostfixDiv() : PostfixOperation(OpCode::DIV) {}

};