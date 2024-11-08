#pragma once

#include "postfix_operation.h"

class PostfixUMinus : public PostfixOperation {
public:
    PostfixUMinus() : PostfixOperation(OpCode::UMINUS) {}

};