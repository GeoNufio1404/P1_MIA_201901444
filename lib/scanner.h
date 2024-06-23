#ifndef SCANNER_H
#define SCANNER_H

#include <vector>
#include <string>

using namespace std;

class Scanner
{
public:
    Scanner(); // Constructor

    void Start();                                     // Funcion para iniciar el scanner
    void Functions(string token, vector<string> tks); // Funcion para ejecutar las funciones
    void Clear();                                     // Funcion para limpiar la consola
    void Mensaje(string mensaje);                     // Funcion para mostrar mensajes
    void Aviso(string mensaje);                       // Funcion para mostrar mensajes
    void Errores(string operacion, string mensaje);   // Funcion para mostrar errores
    void FuncionExec(vector<string> tks);             // Funcion para ejecutar las funciones
    void Excec(string path);                          // Funcion para ejecutar un archivo
    bool Compare(string tk, string token);            // Funcion para comparar los tokens
    string Token(string tk);                          // Funcion para analizar el token
    string Upper(string str);                         // Funcion para convertir a mayusculas
    vector<string> SplitTokens(string texto);         // Funcion para separar los tokens
};

#endif // SCANNER_H