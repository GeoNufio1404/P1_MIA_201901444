#include "../include/disk.h"
#include "../include/scanner.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;

Scanner Scan;
int ValorInicial;

// ===================== CONSTRUCTOR =====================
Disk::Disk()
{
}

// ===================== MKDISK =====================
void Disk::mkdisk(vector<string> tks)
{
    string Path = "";
    int Size = 0;
    string Unit = "";
    string Fit = "";
    bool Bandera = false;
    bool Error = false;

    for (string token : tks)
    {
        string tk = token.substr(0, token.find("="));
        token.erase(0, tk.length() + 1);
        if (Scan.Compare(tk, "path"))
        {
            // Path
            if (Path.empty())
            {
                Path = token;
            }
            else
            {
                Scan.Errores("MKDISK", "Parametro repetido: " + tk);
                Error = true;
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
                Error = true;
            }
        }
        else if (Scan.Compare(tk, "u"))
        {
            // Unit
            if (Unit.empty())
            {

                if (!Scan.Compare(tk,"k") && !Scan.Compare(tk,"m"))
                {
                    Scan.Errores("MKDISK", "Unidad no reconocida: " + Unit);
                    Error = true;
                }
                Unit = token;
            }
            else
            {
                Scan.Errores("MKDISK", "Parametro repetido: " + tk);
                Error = true;
            }
        } else if (Scan.Compare(tk, "f")) {
            // fit
            if (Fit.empty()){
                if (!Scan.Compare(tk,"bf") && !Scan.Compare(tk,"ff") && !Scan.Compare(tk,"wf")){
                    Scan.Errores("MKDISK", "Ajuste no reconocido: " + Fit);
                    Error = true;
                }
                Fit = token;
            } else {
                Scan.Errores("MKDISK", "Parametro repetido: " + tk);
                Error = true;
            }
        }
        else
        {
            Scan.Errores("MKDISK", "Parametro no reconocido: " + tk);
            Error = true;
        }
    }

    if (Path != "" && Size != 0)
    {
        makeDisk(Path, Size, Unit, Fit);
    }
    else
    {
        Scan.Errores("MKDISK", "Faltan parametros obligatorios");
    }
}

// ===================== MAKE DISK =====================
void Disk::makeDisk(string path, int size, string unit, string fit)
{
    cout << "Path: " << path << " Size: " << size << " Unit: " << unit << endl;
    if (unit.empty())
    {
        unit = "k";
    }

    if (unit == "k")
    {
        size = size * 1024;
    }
    else if (unit == "m")
    {
        size = size * 1024 * 1024;
    }
    else
    {
        Scan.Errores("MKDISK", "Unidad no reconocida: " + unit);
        return;
    }

    cout << "Size: " << size << endl;
    FILE *archivo;
    archivo = fopen(path.c_str(), "wb");
    if (archivo == NULL)
    {
        Scan.Errores("MKDISK", "Error al crear el archivo");
        return;
    }

    char buffer = '\0';
    for (int i = 0; i < size; i++)
    {
        fwrite(&buffer, sizeof(buffer), 1, archivo);
    }

    fclose(archivo);
    Scan.Respuesta("MKDISK", "Disco creado correctamente");
}