#ifndef SCANNER_H
#define SCANNER_H
#include <vector>
#include <string>

using namespace std;

class scanner {
    scanner();
    void start();
    void functions(string token, vector<string> tks); // Function to analyze functions
    string token(string tk); // Function to analyze tokens

    vector<string> split(string texto, string text_split);
    vector<string> split_tokens(string texto);

    bool compare(string tk, string token);
    string upper(string str);
    void errores(string operacion, string mensaje);
    void respuesta(string operacion, string mensaje);
    void funcion_exec(vector<string> tks);
    bool confirmar(string mensaje);
};

#endif // SCANNER_H