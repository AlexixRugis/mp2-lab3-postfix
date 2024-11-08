#include <iostream>
#include <memory>
#include <string>
#include <cmath>

#include "postfix.h"
#include "composite_provider.h"
#include "const_provider.h"
#include "user_input_provider.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    setlocale(LC_NUMERIC, "C");

    std::shared_ptr<ConstProvider> constProvider = std::make_shared<ConstProvider>(std::unordered_map<std::string, double>{
            {"PI", 3.14159265358979323846},
            {"E", 2.718281828459}
        });

    std::shared_ptr<UserInputProvider> userInputProvider = std::make_shared<UserInputProvider>();

    std::shared_ptr<IVariableProvider> provider = std::make_shared<CompositeProvider>(std::initializer_list<std::shared_ptr<IVariableProvider>>{
        constProvider,
        userInputProvider
        });

    std::string expression;
    std::cout << "Введите арифметическое выражение: ";
    std::getline(std::cin, expression);
    Postfix postfix(expression);
    std::cout << "Арифметическое выражение: " << postfix.GetInfix() << std::endl;
    auto p = postfix.GetPostfix();
    std::cout << "Постфиксная форма: ";
    for (auto& op : p)
    {
        std::cout << op->ToString() << " ";
    }
    std::cout << std::endl;
    double res = postfix.Calculate(provider);
    std::cout << "Результат: " << res << std::endl;

    return 0;
}
