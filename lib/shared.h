#ifndef SHARED_H
#define SHARED_H

#include <string>

using namespace std;

class Shared
{
public:
    Shared(); // Constructor

    string Upper(string str);          // Convierte una cadena a mayúsculas
    string Lower(string str);          // Convierte una cadena a minúsculas
    bool Comparar(string a, string b); // Compara dos cadenas
};

#endif // SHARED_H