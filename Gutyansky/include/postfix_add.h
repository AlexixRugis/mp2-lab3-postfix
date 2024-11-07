#pragma once

#include "postfix_member.h"

class PostfixAdd : public PostfixMember {
public:
    PostfixAdd() : PostfixMember(OpCode::ADD) {}

};