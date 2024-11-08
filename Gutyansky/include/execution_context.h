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
        m_Stack.Push(v);
    }

    double Pop()
    {
        double tmp = m_Stack.Top();
        m_Stack.Pop();
        return tmp;
    }

    double Result()
    {
        if (m_Stack.Size() == 0)
        {
            throw std::runtime_error("No result");
        }

        return Pop();
    }

private:
    Stack<double> m_Stack;
    std::shared_ptr<IVariableProvider> m_Variables;
};