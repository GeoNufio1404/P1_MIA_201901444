#include "../include/scanner.h"
#include "../lib/disk.cpp"

#include <iostream>
#include <stdlib.h>
#include <locale>
#include <cstring>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

Disk Disco;
bool logued = false; // Variable para saber si el usuario esta logueado

// ======================== CONSTRUCTOR ========================
Scanner::Scanner()
{
}

// ========================= CLEAR =========================
void Clear()
{
    cout << "\x1B[2J\x1B[H"; // Limpiar consola
}

// ========================= UPPER =========================
string Scanner::Upper(string str)
{
    string str_upper = str;
    for (int i = 0; i < str_upper.length(); i++)
    {
        str_upper[i] = toupper(str_upper[i]); // Convertir a mayusculas
    }
    return str_upper;
}

// ========================= TOKEN =========================
string Scanner::Token(string tk)
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
vector<string> Scanner::Split(string texto, string text_split)
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
vector<string> Scanner::SplitTokens(string text)
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
        if (c == '\n')
        {
            cout << "Salto de linea" << endl;
        }

        switch (estado)
        {
        case 0:
            if (c == '-')
            {
                estado = 1;
                continue;
            }
            else if (c == '#')
            {
            }
            break;
        case 1:
            if (c == '=')
            {
                estado = 2;
            }
            else if (c == ' ')
            {
                continue;
            }
            break;
        case 2:
            if (c == '\"')
            {
                estado = 3;
            }
            else
            {
                estado = 4;
            }
            break;
        case 3:
            if (c == '\"')
            {
                estado = 4;
            }
            break;
        case 4:
            if (c == ' ')
            {
                estado = 0;
                tokens.push_back(token);
                token = "";
                continue;
            }
            else if (c == '\"')
            {
                tokens.clear();
                continue;
            }
            break;
        default:
            break;
        }

        token += c;
    }
    return tokens;
}

// ========================= COMPARE =========================
bool Scanner::Compare(string tk, string token)
{
    if (Upper(tk) == Upper(token))
    {
        return true;
    } // Comparar los tokens
    return false;
}

// ========================= ERRORES =========================
void Scanner::Errores(string operacion, string mensaje)
{
    cout << "Error: " << operacion << " - " << mensaje << endl;
}

// ========================= RESPUESTA =========================
void Scanner::Respuesta(string operacion, string mensaje)
{
    cout << "Respuesta: " << operacion << " - " << mensaje << endl;
}

// ========================= CONFIRMAR =========================
bool Scanner::Confirmar(string mensaje)
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
void Scanner::Start()
{
    system("clear"); // Limpiar consola
    Clear();

    // Loop para leer los comandos
    while (true)
    {
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
    }
}

// ========================= FUNCION EXEC =========================
void Scanner::FuncionExec(vector<string> tks)
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
void Scanner::Excec(string path)
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
        lines.push_back(line); // Leer las lineas del archivo
    }

    for (const auto &i : lines)
    {
        string texto = i;
        string tk = Token(texto);
        if (texto != "")
        {
            texto.erase(0, tk.length() + 1);
            vector<string> tks = SplitTokens(texto);
            Functions(tk, tks);
        }
    }
    input_file.close();
    return;
}

// ========================= FUNCTIONS =========================
void Scanner::Functions(string token, vector<string> tks)
{
    if (Compare(token, "mkdisk"))
    {
        Disco.mkdisk(tks);
    }
    else if (Compare(token, "rmdisk"))
    {
        Disco.rmdisk(tks);
    }
    else if (Compare(token, "fdisk"))
    {
        Disco.fdisk(tks);
    }
    else if (Compare(token, "pause"))
    {
        Respuesta("PAUSE", "Presione enter para continuar...");
        string pause;
        getline(cin, pause);
    }
    else if (Compare(token, "exec"))
    {
        FuncionExec(tks);
    }
    else
    {
        Errores("FUNCTIONS", "Comando no reconocido");
    }
}
