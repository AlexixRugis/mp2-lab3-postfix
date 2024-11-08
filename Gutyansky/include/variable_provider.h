#pragma once

#include <string>

class IVariableProvider {
public:
    virtual ~IVariableProvider() = 0 {}
    
    virtual bool HasVariable(const std::string& name) const = 0;
    virtual double GetVariable(const std::string& name) = 0;
};