#include "../lib/scanner.h"

#include "../lib/disk.h"

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
void Scanner::Clear()
{
    cout << "\x1B[2J\x1B[H"; // Limpiar consola
}

// ========================= AVISO =========================
void Scanner::Aviso(string mensaje)
{
    // Mostrar avisos de color amarillo
    cout << endl;
    cout << "\t\033[1;33m AVISO: " << mensaje << "\033[0m" << endl;
    cout << endl;
}

// ========================= MENSAJE =========================
void Scanner::Mensaje(string mensaje)
{
    // Mostrar mensajes de color verde
    cout << "\t\033[1;32m" << mensaje << "\033[0m" << endl;
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
    // Mostrar error de color rojo
    cout << endl;
    cout << "\t\033[1;31m ERROR: " << operacion << " - " << mensaje << "\033[0m" << endl;
    cout << endl;
}

// ========================= START =========================
void Scanner::Start()
{
    system("clear"); // Limpiar consola
    Clear();

    // Mostrar mensaje de bienvenida
    Mensaje("Bienvenido a la consola de comandos de MIA");
    Mensaje("Para salir de la consola escriba 'exit' y presione enter");
    cout << endl;

    // Loop para leer los comandos
    while (true)
    {
        cout << ">> ";

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
        Errores("EXEC", "No se pudo abrir el archivo");
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
        Aviso("PAUSE - Presione enter para continuar...");
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
