#pragma once

#include <stdexcept>
#include "variable_provider.h"

class DummyProvider : public IVariableProvider
{
public:
    bool HasVariable(const std::string& name) const override { return false; }

    double GetVariable(const std::string& name) override
    {
        throw std::runtime_error("No variable found");
    }
};