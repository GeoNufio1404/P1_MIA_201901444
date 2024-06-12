#include "../include/scanner.h"
//#include "../include/disk.cpp"

#include <iostream>
#include <stdlib.h>
#include <locale>
#include <cstring>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

//Disk Disco;
bool logued = false; // Variable para saber si el usuario esta logueado

// ======================== CONSTRUCTOR ========================
scanner::scanner()
{
}

// ========================= CLEAR =========================
void Clear()
{
    cout << "\x1B[2J\x1B[H"; // Limpiar consola
}

// ========================= UPPER =========================
string scanner::Upper(string str)
{
    string str_upper = str;
    for (int i = 0; i < str_upper.length(); i++)
    {
        str_upper[i] = toupper(str_upper[i]); // Convertir a mayusculas
    }
    return str_upper;
}

// ========================= TOKEN =========================
string scanner::Token(string tk)
{
    string tkn = "";
    bool Terminar = false;
    for (char &c : tk)
    {
        if (Terminar)
        {
            if (c == ' ' || c == '-')
            {
                break;
            }
            tkn += c;
        }
        else if (c != ' ' && !Terminar)
        {
            if (c == '#')
            {
                tkn = tk;
                break;
            }
            else
            {
                tkn += c;
                Terminar = true;
            }
        }
    }
    return tkn;
}

// ========================= SPLIT =========================
vector<string> scanner::Split(string texto, string text_split)
{
    vector<string> Cadena;
    if (texto.empty())
    {
        return Cadena;
    }

    int n = texto.length();
    char char_array[n + 1];
    strcpy(char_array, texto.c_str());
    char *point = strtok(char_array, text_split.c_str());
    while (point != NULL)
    {
        Cadena.push_back(string(point));
        point = strtok(NULL, text_split.c_str());
    }
    return Cadena;
}

// ========================= SPLIT TOKENS =========================
vector<string> scanner::SplitTokens(string text)
{
    vector<string> tokens;
    if (text.empty())
    {
        return tokens;
    }
    text.push_back(' ');
    string token = "";
    int estado = 0;
    for (char &c : text)
    {
        if (estado == 0 && c == '-')
        {
            estado = 1;
        }
        else if (estado == 0 && c == '#')
        {
            continue;
        }
        else if (estado != 0)
        {
            if (estado == 1)
            {
                if (c == '=')
                {
                    estado = 2;
                }
                else if (c == ' ')
                {
                    continue;
                }
            }
            else if (estado == 2)
            {
                if (c == '\"')
                {
                    estado = 3;
                }
                else
                {
                    estado = 4;
                }
            }
            else if (estado == 3)
            {
                if (c == '\"')
                {
                    estado = 4;
                }
            }
            else if (estado == 4 && c == '\"')
            {
                tokens.clear();
                continue;
            }
            else if (estado == 4 && c == ' ')
            {
                estado = 0;
                tokens.push_back(token);
                token = "";
                continue;
            }
            token += c;
        }
    }
    return tokens;
}

// ========================= COMPARE =========================
bool scanner::Compare(string tk, string token)
{
    if (Upper(tk) == Upper(token))
    {
        return true;
    } // Comparar los tokens
    return false;
}

// ========================= ERRORES =========================
void scanner::Errores(string operacion, string mensaje)
{
    cout << "Error: " << operacion << " - " << mensaje << endl;
}

// ========================= RESPUESTA =========================
void scanner::Respuesta(string operacion, string mensaje)
{
    cout << "Respuesta: " << operacion << " - " << mensaje << endl;
}

// ========================= CONFIRMAR =========================
bool scanner::Confirmar(string mensaje)
{
    string respuesta;
    cout << mensaje << " (S/N): ";
    getline(cin, respuesta);
    if (Compare(respuesta, "S"))
    {
        return true;
    }
    return false;
}

// ========================= START =========================
void scanner::Start()
{
    system("clear"); // Limpiar consola

    // Loop para leer los comandos
    while (true)
    {
        Clear();
        std::cout << ">>";

        string texto;
        getline(cin, texto);

        if (Compare(texto, "exit"))
        {
            break;
        }
        string tk = Token(texto);
        texto.erase(0, tk.length() + 1);
        vector<string> tks = SplitTokens(texto); // Separar los tokens
        Functions(tk, tks);                      // Buscar las funciones

        cout << "\nPresione enter para continuar..." << endl;
        getline(cin, texto);
    }
}

// ========================= FUNCION EXEC =========================
void scanner::FuncionExec(vector<string> tks)
{
    string path = "";
    for (string token : tks)
    {
        string tk = token.substr(0, token.find("="));
        token.erase(0, tk.length() + 1);
        if (Compare(tk, "path"))
        {
            path = token;
        }
    }
    if (path.empty())
    {
        Errores("EXEC", "Se requiere path para este comando");
        return;
    }
    Excec(path);
}

// ========================= EXEC =========================
void scanner::Excec(string path)
{
    string filename(path);
    vector<string> lines;
    string line;
    ifstream input_file(filename);
    if (!input_file.is_open())
    {
        cerr << "No se puede abrir el archivo" << filename << endl;
        return;
    }
    while (getline(input_file, line))
    {
        lines.push_back(line);
    }
    for (const auto &i : lines)
    {
        string texto = i;
        string tk = Token(texto);
        if (texto != "")
        {
            if (Compare(texto, "PAUSE"))
            {
                string pause;
                Respuesta("PAUSE", "Presione enter para continuar...");
                getline(cin, pause);
                continue;
            }
            texto.erase(0, tk.length() + 1);
            vector<string> tks = SplitTokens(texto);
            Functions(tk, tks);
        }
    }
    input_file.close();
    return;
}

// ========================= FUNCTIONS =========================
void scanner::Functions(string token, vector<string> tks)
{
    if (Compare(token, "MKDISK"))
    {
        cout << "MKDISK" << endl;
        //Disco.mkdisk(tks);
    }
}