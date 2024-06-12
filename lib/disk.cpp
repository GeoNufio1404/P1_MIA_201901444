#include "../include/disk.h"
#include "../include/scanner.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;

scanner Scan;
int ValorInicial;

// ===================== CONSTRUCTOR =====================
Disk::Disk()
{
}

// ===================== MKDISK =====================
void Disk::mkdisk(vector<string> tks)
{
    cout << "Entre " << endl;
    string Path = "";
    int Size = 0;
    string Unit = "";
    bool bandera = false;
    bool error = false;

    for (string token : tks)
    {
        string tk = token.substr(0, token.find("="));
        token.erase(0, tk.length() + 1);
        if (Scan.Compare(tk, "p"))
        {
            // Path
            if (Path.empty())
            {
                Path = token;
            }
            else
            {
                Scan.Errores("MKDISK", "Parametro repetido: " + tk);
                error = true;
            }
        }
        else if (Scan.Compare(tk, "s"))
        {
            // Size
            if (Size == 0)
            {
                Size = atoi(token.c_str());
            }
            else
            {
                Scan.Errores("MKDISK", "Parametro repetido: " + tk);
                error = true;
            }
        }
        else if (Scan.Compare(tk, "u"))
        {
            // Unit
            if (Unit.empty())
            {
                Unit = token;
            }
            else
            {
                Scan.Errores("MKDISK", "Parametro repetido: " + tk);
                error = true;
            }
        }
        else
        {
            Scan.Errores("MKDISK", "Parametro no reconocido: " + tk);
            error = true;
        }

        cout << "Token: " << tk << " Valor: " << token << endl;
    }

    if (Path != "" && Size != 0)
    {
        makeDisk(Path, Size, Unit);
    }
    else
    {
        Scan.Errores("MKDISK", "Faltan parametros obligatorios");
    }
}