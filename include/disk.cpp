#include "../lib/disk.h"

#include "../lib/scanner.h"
#include "../lib/shared.h"
#include "../lib/structs.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <filesystem>

using namespace std;

Scanner Scan;
Shared Compartido;
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
                // Si el path tiene comillas, se las quitamos
                if (token[0] == '\"' && token[token.length() - 1] == '\"')
                {
                    token = token.substr(1, token.length() - 2);
                }
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
                // Revisar si el valor es negativo
                if (Size < 0)
                {
                    Scan.Errores("MKDISK", "El valor del size no puede ser negativo");
                    Error = true;
                }
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

                if (!Scan.Compare(token, "k") && !Scan.Compare(token, "m"))
                {
                    Scan.Errores("MKDISK", "Unidad no reconocida");
                    Error = true;
                }
                Unit = token;
            }
            else
            {
                Scan.Errores("MKDISK", "Parametro repetido: " + tk);
                Error = true;
            }
        }
        else if (Scan.Compare(tk, "f"))
        {
            // fit
            if (Fit.empty())
            {
                if (!Scan.Compare(token, "bf") && !Scan.Compare(token, "ff") && !Scan.Compare(token, "wf"))
                {
                    Scan.Errores("MKDISK", "Ajuste no reconocido: " + Fit);
                    Error = true;
                }
                Fit = token;
            }
            else
            {
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

    if (Error)
    {
        Scan.Errores("MKDISK", "Existen errores en los parametros de mkdisk");
        return;
    }

    // Verificar parametros obligatorios
    if (Path != "" && Size != 0)
    {
        CreateDisk(Path, Size, Unit, Fit);
    }
    else
    {
        Scan.Errores("MKDISK", "Faltan parametros obligatorios");
    }
}

void Disk::CreateDisk(string path, int size, string unit, string fit)
{
    // Datos default
    if (unit.empty())
    {
        unit = "m";
    }
    if (fit.empty())
    {
        fit = "ff";
    }

    // Unit
    if (unit == "k")
    {
        size = size * 1024;
    }
    else if (unit == "m")
    {
        size = size * 1024 * 1024;
    }

    cout << "Path: " << path << " Size: " << size << " Unit: " << unit << " Fit: " << fit << endl;

    // usar filesystem para crear la ruta/carpeta si este no existe
    filesystem::create_directories(filesystem::path(path).parent_path());

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

// ====================== FDISK ======================
void Disk::rmdisk(vector<string> tks)
{
    string Path = "";
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
                // Si el path tiene comillas, se las quitamos
                if (token[0] == '\"' && token[token.length() - 1] == '\"')
                {
                    token = token.substr(1, token.length() - 2);
                }
                Path = token;
            }
            else
            {
                Scan.Errores("RMDISK", "Parametro repetido: " + tk);
                Error = true;
                return;
            }
        }
        else
        {
            Scan.Errores("RMDISK", "Parametro no reconocido: " + tk);
            Error = true;
            return;
        }
    }

    if (Error)
    {
        Scan.Errores("RMDISK", "Existen errores en los parametros de rmdisk");
        return;
    }

    if (Path != "")
    {
        RemoveDisk(Path);
    }
    else
    {
        Scan.Errores("RMDISK", "Faltan parametros obligatorios");
    }
}

void Disk::RemoveDisk(string path)
{
    // Eliminar disco
    cout << "¿Desea eliminar el disco ubicado en:" << path << " ? (S/N): ";
    string Confirmacion;
    cin >> Confirmacion;
    if (Compartido.Comparar(Confirmacion, "S"))
    {
        if (remove(path.c_str()) != 0)
        {
            Scan.Errores("RMDISK", "Error al eliminar el disco");
        }
        else
        {
            Scan.Respuesta("RMDISK", "Disco eliminado correctamente");
        }
    }
    else
    {
        Scan.Respuesta("RMDISK", "Operacion cancelada");
    }
}

// ====================== FDISK ======================
void Disk::fdisk(vector<string> tks)
{
    int Size = 0;
    string Unit = "";
    string Path = "";
    string Type = "";
    string Fit = "";
    string Del = "";
    string Name = "";
    int Add = 0;
    bool Error = false;

    for (string token : tks)
    {
        string tk = token.substr(0, token.find("="));
        token.erase(0, tk.length() + 1);

        if (Scan.Compare(tk, "s"))
        {
            // Size
            if (Size == 0)
            {
                Size = atoi(token.c_str());
                if (Size <= 0)
                {
                    Scan.Errores("FDISK", "El tamaño de la partición debe ser mayor a 0");
                    Error = true;
                    return;
                }
            }
            else
            {
                Scan.Errores("FDISK", "Parametro repetido: size");
                Error = true;
                return;
            }
        }
        else if (Scan.Compare(tk, "u"))
        {
            // Unit
            if (Unit.empty())
            {
                if (!Scan.Compare(token, "k") && !Scan.Compare(token, "m") && !Scan.Compare(token, "b"))
                {
                    Scan.Errores("FDISK", "Unidad no reconocida");
                    Error = true;
                    return;
                }
                Unit = token;
            }
            else
            {
                Scan.Errores("FDISK", "Parametro repetido: unit");
                Error = true;
                return;
            }
        }
        else if (Scan.Compare(tk, "path"))
        {
            // Path
            if (Path.empty())
            {
                // Si el path tiene comillas, se las quitamos
                if (token[0] == '\"' && token[token.length() - 1] == '\"')
                {
                    token = token.substr(1, token.length() - 2);
                }
                Path = token;
            }
            else
            {
                Scan.Errores("FDISK", "Parametro repetido: path");
                Error = true;
                return;
            }
        }
        else if (Scan.Compare(tk, "t"))
        {
            // Type
            if (Type.empty())
            {
                if (!Scan.Compare(token, "p") && !Scan.Compare(token, "e") && !Scan.Compare(token, "l"))
                {
                    Scan.Errores("FDISK", "Tipo no reconocido");
                    Error = true;
                    return;
                }
                Type = token;
            }
            else
            {
                Scan.Errores("FDISK", "Parametro repetido: type");
                Error = true;
                return;
            }
        }
        else if (Scan.Compare(tk, "f"))
        {
            // Fit
            if (Fit.empty())
            {
                if (!Scan.Compare(token, "bf") && !Scan.Compare(token, "ff") && !Scan.Compare(token, "wf"))
                {
                    Scan.Errores("FDISK", "Ajuste no reconocido");
                    Error = true;
                    return;
                }
                Fit = token;
            }
            else
            {
                Scan.Errores("FDISK", "Parametro repetido: fit");
                Error = true;
                return;
            }
        }
        else if (Scan.Compare(tk, "delete"))
        {
            // Delete
            if (Del.empty())
            {
                if (!Scan.Compare(token, "full") && !Scan.Compare(token, "fast"))
                {
                    Scan.Errores("FDISK", "Tipo de borrado no reconocido");
                    Error = true;
                    return;
                }
                Del = token;
            }
            else
            {
                Scan.Errores("FDISK", "Parametro repetido: delete");
                Error = true;
                return;
            }
        }
        else if (Scan.Compare(tk, "name"))
        {
            // Name
            if (Name.empty())
            {
                Name = token;
            }
            else
            {
                Scan.Errores("FDISK", "Parametro repetido: name");
                Error = true;
                return;
            }
        }
        else if (Scan.Compare(tk, "add"))
        {
            // Add
            if (Add == 0)
            {
                Add = atoi(token.c_str());
            }
            else
            {
                Scan.Errores("FDISK", "Parametro repetido: add");
                Error = true;
                return;
            }
        }
        else
        {
            Scan.Errores("FDISK", "Parametro no reconocido: " + tk);
            Error = true;
            return;
        }
    }

    if (Error)
    {
        Scan.Errores("FDISK", "Existen errores en los parametros de fdisk");
        return;
    }

    // Obligatorios size, path, name
    if (Size != 0 && !Path.empty() && !Name.empty())
    {
        if (Add != 0 && !Del.empty())
        {
            Scan.Errores("FDISK", "No se pueden usar los parametros add y delete al mismo tiempo");
            return;
        }

        if (Add != 0)
        {
            // Agregar a particion existente
            AddPartition(Path, Name, Add, Unit);
        }
        else if (!Del.empty())
        {
            // Eliminar particion
            DeletePartition(Path, Name, Del);
        }
        else
        {
            // Crear particion
            CreatePartition(Size, Unit, Path, Type, Fit, Name);
        }
    }
    else
    {
        Scan.Errores("FDISK", "Faltan parametros obligatorios: (s, path, name)");
    }
}

vector<Structs::Particion> Disk::GetPartitions(Structs::MBR mbr)
{
    vector<Structs::Particion> particiones;
    particiones.push_back(mbr.mbr_Particion1);
    particiones.push_back(mbr.mbr_Particion2);
    particiones.push_back(mbr.mbr_Particion3);
    particiones.push_back(mbr.mbr_Particion4);
    return particiones;
}

void Disk::CreatePartition(int size, string unit, string path, string type, string fit, string name)
{
    // Datos default
    if (unit.empty())
    {
        unit = "k";
    }
    if (fit.empty())
    {
        fit = "wf";
    }
    if (type.empty()) // p + e <= 4 | solo 1 extendida | si no hay e, no hay l
    {
        type = "p";
    }
    ValorInicial = 0;

    if (Compartido.Comparar(unit, "k"))
    {
        size = size * 1024;
    }
    else if (Compartido.Comparar(unit, "m"))
    {
        size = size * 1024 * 1024;
    }

    Structs::MBR mbr;
    FILE *archivo;
    archivo = fopen(path.c_str(), "rb+");
    if (archivo == NULL)
    {
        Scan.Errores("FDISK", "Error - No se pudo localizar el disco");
        return;
    }
    rewind(archivo);
    fread(&mbr, sizeof(mbr), 1, archivo);
    fclose(archivo);

    vector<Structs::Particion> particiones = GetPartitions(mbr);
}

void Disk::DeletePartition(string path, string name, string del)
{
}

void Disk::AddPartition(string path, string name, int add, string unit)
{
}