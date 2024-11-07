#pragma once

#include <string>
#include "postfix_member.h"

class PostfixCall : public PostfixMember {
public:
    PostfixCall(const std::string& name) : PostfixMember(OpCode::CALL), m_Name(name) {}

    std::string FuncName() const noexcept { return m_Name; }

private:
    std::string m_Name;
};