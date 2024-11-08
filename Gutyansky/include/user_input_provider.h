#pragma once

#include <unordered_map>
#include <iostream>
#include "variable_provider.h"

class UserInputProvider : public IVariableProvider
{
public:
    bool HasVariable(const std::string& name) const override { return true; }
    double GetVariable(const std::string& name) override
    {
        if (m_Cached.find(name) == m_Cached.end())
        {
            double v;
            std::cout << "Введите значение переменной '" << name << "': ";
            std::cin >> v;
            m_Cached[name] = v;
        }

        return m_Cached[name];
    }

private:
    std::unordered_map<std::string, double> m_Cached;
};