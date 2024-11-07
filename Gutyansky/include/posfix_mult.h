#pragma once

#include "postfix_member.h"

class PostfixMult : public PostfixMember {
public:
    PostfixMult() : PostfixMember(OpCode::MULT) {}

};