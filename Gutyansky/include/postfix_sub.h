#pragma once

#include "postfix_member.h"

class PostfixSub : public PostfixMember {
public:
    PostfixSub() : PostfixMember(OpCode::SUB) {}

};