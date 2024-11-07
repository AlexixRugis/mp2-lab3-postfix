#pragma once

#include "postfix_member.h"

class PostfixDiv : public PostfixMember {
public:
    PostfixDiv() : PostfixMember(OpCode::DIV) {}

};