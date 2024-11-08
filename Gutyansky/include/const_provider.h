#pragma once

#include <unordered_map>
#include <stdexcept>
#include "variable_provider.h"

class ConstProvider : public IVariableProvider
{
public:
    ConstProvider(std::unordered_map<std::string, double> constants) : m_Constants(constants) {}

    bool HasVariable(const std::string& name) const override { return m_Constants.find(name) != m_Constants.end(); }

    double GetVariable(const std::string& name) override
    {
        if (!HasVariable(name))
        {
            throw std::runtime_error("No variable found");
        }

        return m_Constants.at(name);
    }

private:
    std::unordered_map<std::string, double> m_Constants;
};