#pragma once

#include <string>
#include "postfix_member.h"

class PostfixVar : public PostfixMember {
public:
    PostfixVar(const std::string& name) : PostfixMember(OpCode::VAR), m_Name(name) {}

    std::string Name() const noexcept { return m_Name; }

private:
    std::string m_Name;
};