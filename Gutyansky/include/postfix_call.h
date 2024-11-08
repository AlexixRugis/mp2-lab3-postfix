#pragma once

#include <string>
#include "postfix_operation.h"

class PostfixCall : public PostfixOperation {
public:
    PostfixCall(const std::string& name) : PostfixOperation(OpCode::CALL), m_Name(name) {}

    std::string FuncName() const noexcept { return m_Name; }

private:
    std::string m_Name;
};