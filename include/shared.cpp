#include "../lib/shared.h"

#include <iostream>
#include <stdlib.h>
#include <string>
#include <locale>

using namespace std;

Shared::Shared()
{
}

string Shared::Upper(string str)
{
    locale loc;
    string result = "";
    for (string::size_type i = 0; i < str.length(); ++i)
    {
        result += toupper(str[i], loc);
    }
    return result;
}

string Shared::Lower(string str)
{
    locale loc;
    string result = "";
    for (string::size_type i = 0; i < str.length(); ++i)
    {
        result += tolower(str[i], loc);
    }
    return result;
}

bool Shared::Comparar(string a, string b)
{
    string A = Upper(a);
    string B = Upper(b);
    return A == B;
}
