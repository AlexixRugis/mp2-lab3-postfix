#pragma once

#include <string>
#include "postfix_operation.h"

class PostfixVar : public PostfixOperation {
public:
    PostfixVar(const std::string& name) : PostfixOperation(OpCode::VAR), m_Name(name) {}

    std::string Name() const noexcept { return m_Name; }

private:
    std::string m_Name;
};