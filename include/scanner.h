#ifndef SCANNER_H
#define SCANNER_H

#include <vector>
#include <string>

using namespace std;

class Scanner
{
public:
    Scanner(); // Constructor

    void Start();                                          // Funcion para iniciar el scanner
    void Functions(string token, vector<string> tks);      // Funcion para ejecutar las funciones
    void Errores(string operacion, string mensaje);        // Funcion para mostrar errores
    void Respuesta(string operacion, string mensaje);      // Funcion para mostrar respuestas
    void FuncionExec(vector<string> tks);                  // Funcion para ejecutar las funciones
    bool Confirmar(string mensaje);                        // Funcion para confirmar una accion
    void Excec(string path);                               // Funcion para ejecutar un archivo
    bool Compare(string tk, string token);                 // Funcion para comparar los tokens
    string Token(string tk);                               // Funcion para analizar el token
    string Upper(string str);                              // Funcion para convertir a mayusculas
    vector<string> Split(string texto, string text_split); // Funcion para separar los tokens
    vector<string> SplitTokens(string texto);              // Funcion para separar los tokens
};

#endif // SCANNER_H