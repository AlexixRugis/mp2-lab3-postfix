#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    setlocale(LC_NUMERIC, "C");

    string expression;
    cout << "Введите арифметическое выражение: ";
    getline(cin, expression);
    Postfix postfix(expression);
    cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
    auto p = postfix.GetPostfix();
    //cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
    double res = postfix.Calculate();
    cout << "Результат: " << res << endl;

    return 0;
}
