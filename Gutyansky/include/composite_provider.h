#pragma once

#include <unordered_map>
#include <stdexcept>
#include <vector>
#include <initializer_list>
#include <memory>
#include <algorithm>
#include "variable_provider.h"

class CompositeProvider : public IVariableProvider
{
public:
    CompositeProvider(std::initializer_list<std::shared_ptr<IVariableProvider>> providers) : m_Providers(providers.begin(), providers.end()) {}

    bool HasVariable(const std::string& name) const override
    {
        return std::any_of(m_Providers.begin(), m_Providers.end(), [&name](const std::shared_ptr<IVariableProvider>& p) { return p->HasVariable(name); });
    }

    double GetVariable(const std::string& name) override
    {
        auto iter = std::find_if(m_Providers.begin(), m_Providers.end(), [&name](const std::shared_ptr<IVariableProvider>& p) { return p->HasVariable(name); });

        if (iter == m_Providers.end())
        {
            throw std::runtime_error("No variable found");
        }

        return iter->get()->GetVariable(name);
    }

private:
    std::vector<std::shared_ptr<IVariableProvider>> m_Providers;
};