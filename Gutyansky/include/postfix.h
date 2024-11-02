#pragma once

#include <string>
#include "stack.h"

using namespace std;

class TPostfix
{
    string infix;
    string postfix;
public:
    TPostfix()
    {
        infix = "a + b";
    }
    string GetInfix() { return infix; }
    string GetPostfix() { return postfix; }
    string ToPostfix();
    double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};
