#pragma once

#include <memory>
#include <string>
#include "stack.h"
#include "variable_provider.h"

class ExecutionContext
{
public:
    ExecutionContext(const std::shared_ptr<IVariableProvider>& variables) : m_Variables(variables) {}

    bool HasVariable(const std::string& name)
    {
        return m_Variables->HasVariable(name);
    }

    double GetVariable(const std::string& name)
    {
        return m_Variables->GetVariable(name);
    }

    void Push(double v)
    {
        m_Stack.push(v);
    }

    double Pop()
    {
        double tmp = m_Stack.top();
        m_Stack.pop();
        return tmp;
    }

    double Result()
    {
        if (m_Stack.size() == 0)
        {
            throw std::runtime_error("No result");
        }

        return Pop();
    }

private:
    Stack<double> m_Stack;
    std::shared_ptr<IVariableProvider> m_Variables;
};