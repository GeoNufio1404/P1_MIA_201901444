#include "../lib/disk.h"

#include "../lib/scanner.h"
#include "../lib/structs.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <filesystem>
#include <cstring>

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
    Structs::MBR mbr;

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

    // Inicializar MBR
    mbr.Mbr_tamano = size;
    mbr.Mbr_disk_signature = rand() % 9999 + 100;
    mbr.Disk_fit = fit.substr(0, 1).c_str()[0];
    mbr.Mbr_fecha_creacion = time(nullptr);

    mbr.Mbr_Particion1 = Structs::Particion();
    mbr.Mbr_Particion2 = Structs::Particion();
    mbr.Mbr_Particion3 = Structs::Particion();
    mbr.Mbr_Particion4 = Structs::Particion();

    // usar filesystem para crear la ruta/carpeta si este no existe
    filesystem::create_directories(filesystem::path(path).parent_path());

    // Verificar si el archivo que se va a crear termina en .dsk
    if (path.substr(path.length() - 4) != ".dsk")
    {
        Scan.Aviso("MKDISK - Se le agregara la extension .dsk al archivo");
        path += ".dsk";
    }

    try
    {
        FILE *file = fopen(path.c_str(), "w+b");
        if (file != NULL)
        {
            // Si el archivo no existe, se crea
            fwrite("\0", 1, 1, file);
            fseek(file, size - 1, SEEK_SET);
            fwrite("\0", 1, 1, file);
            rewind(file);
            fwrite(&mbr, sizeof(Structs::MBR), 1, file);
            fclose(file);
        }
        else
        {
            // Si el archivo ya existe, se sobreescribe
            string comando1 = "mkdir -p \"" + path + "\"";
            string comando2 = "rmdir \"" + path + "\"";
            system(comando1.c_str());
            system(comando2.c_str());
            FILE *file = fopen(path.c_str(), "w+b");
            fwrite("\0", 1, 1, file);
            fseek(file, size - 1, SEEK_SET);
            fwrite("\0", 1, 1, file);
            rewind(file);
            fwrite(&mbr, sizeof(Structs::MBR), 1, file);
            fclose(file);
        }

        // Leer el MBR del disco e imprimirlo
        FILE *imprimir = fopen(path.c_str(), "r");
        if (imprimir != NULL)
        {
            Structs::MBR discoI;
            fseek(imprimir, 0, SEEK_SET);                      // Regresar al inicio del archivo
            fread(&discoI, sizeof(Structs::MBR), 1, imprimir); // Leer el MBR del disco
            struct tm *tm;                                     // Estructura para la fecha
            tm = localtime(&discoI.Mbr_fecha_creacion);
            char mostrar_fecha[20];
            strftime(mostrar_fecha, 20, "%Y/%m/%d %H:%M:%S", tm);
            Scan.Aviso("MKDISK - Disco creado correctamente");
            cout << endl;
            Scan.Mensaje("========== MBR ==========");
            Scan.Mensaje("Size: " + to_string(discoI.Mbr_tamano) + " Bs");
            Scan.Mensaje("Fecha: " + string(mostrar_fecha));
            Scan.Mensaje("Fit: " + string(1, discoI.Disk_fit));
            Scan.Mensaje("Disk_Signature: " + to_string(discoI.Mbr_disk_signature));
            Scan.Mensaje("Bits del MBR: " + to_string(sizeof(Structs::MBR)));
            Scan.Mensaje("Path: " + path);
            cout << endl;
        }
        fclose(imprimir);
    }
    catch (const exception &e)
    {
        Scan.Errores("MKDISK", "Error al crear el disco");
    }
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
    // Revisar que sea un archivo .dsk
    if (path.substr(path.length() - 4) != ".dsk")
    {
        Scan.Errores("RMDISK", "El archivo no es un disco .dsk");
        return;
    }

    // Eliminar disco
    Scan.Mensaje("¿Desea eliminar el disco ubicado en:" + path + " ? (S/N): ");
    string Confirmacion;
    cout << ">> ";
    getline(cin, Confirmacion);
    if (Scan.Compare(Confirmacion, "S"))
    {
        if (remove(path.c_str()) != 0)
        {
            Scan.Errores("RMDISK", "Error al eliminar el disco");
        }
        else
        {
            Scan.Aviso("RMDISK - Disco eliminado correctamente");
        }
    }
    else
    {
        Scan.Aviso("RMDISK - Operacion cancelada");
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

vector<Structs::Particion> Disk::ObtenerParticiones(Structs::MBR mbr)
{
    vector<Structs::Particion> particiones;
    particiones.push_back(mbr.Mbr_Particion1);
    particiones.push_back(mbr.Mbr_Particion2);
    particiones.push_back(mbr.Mbr_Particion3);
    particiones.push_back(mbr.Mbr_Particion4);
    return particiones;
}

Structs::MBR Disk::ObtenerMBR(string path)
{
    Structs::MBR mbr;
    FILE *archivo;
    archivo = fopen(path.c_str(), "r");
    if (archivo == NULL)
    {
        Scan.Errores("FDISK", "Error - No se pudo localizar el disco");
        return mbr;
    }
    rewind(archivo);                      // Regresar al inicio del archivo
    fread(&mbr, sizeof(mbr), 1, archivo); // Leer el MBR del disco
    fclose(archivo);                      // Cerrar el archivo
    return mbr;
}

int Disk::ContarTipoParticion(vector<Structs::Particion> particiones, string tipo)
{
    // Convertir el tipo a char
    char tipoChar = tipo.c_str()[0];

    int contador = 0;
    for (Structs::Particion particion : particiones)
    {
        if (particion.Part_type == tipoChar)
        {
            contador++;
        }
    }
    return contador;
}

int Disk::ContarParticiones(vector<Structs::Particion> particiones)
{
    int contador = 0;
    for (Structs::Particion particion : particiones)
    {
        if (particion.Part_status == '1')
        {
            contador++;
        }
    }
    return contador;
}

vector<Structs::EBR> Disk::ObtenerParticionesLogicas(Structs::Particion particion, string path)
{
    vector<Structs::EBR> logicas;
    FILE *archivo;
    archivo = fopen(path.c_str(), "rb+");
    if (archivo == NULL)
    {
        Scan.Errores("FDISK", "Error - No se pudo localizar el disco");
        return logicas;
    }
    rewind(archivo);
    fseek(archivo, particion.Part_start, SEEK_SET);
    Structs::EBR ebr;
    fread(&ebr, sizeof(ebr), 1, archivo);
    while (ebr.Part_next != -1)
    {
        logicas.push_back(ebr);
        fseek(archivo, ebr.Part_next, SEEK_SET);
        fread(&ebr, sizeof(ebr), 1, archivo);
    }
    fclose(archivo);
    return logicas;
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
    if (type.empty())
    {
        type = "p";
    }
    ValorInicial = 0;

    if (Scan.Compare(unit, "k"))
    {
        size = size * 1024;
    }
    else if (Scan.Compare(unit, "m"))
    {
        size = size * 1024 * 1024;
    }

    Structs::MBR mbr;
    mbr = ObtenerMBR(path);

    // Comprobar si hay espacio en el disco
    if (mbr.Mbr_tamano - sizeof(mbr) < size)
    {
        Scan.Aviso("FDISK - No hay suficiente espacio en el disco");
        Scan.Mensaje("Disco - Espacio disponible: " + to_string(mbr.Mbr_tamano - sizeof(mbr)) + " Bytes");
        Scan.Mensaje(name + " - Espacio requerido: " + to_string(size) + " Bytes");
        return;
    }

    // Obtener las particiones del disco
    vector<Structs::Particion> particiones = ObtenerParticiones(mbr);

    if (ContarParticiones(particiones) == 4)
    {
        Scan.Errores("FDISK", "Ya existen 4 particiones en el disco, abortando operacion");
        return;
    }

    if (type == "p")
    {
        cout << "Primaria" << endl;

        ValorInicial = sizeof(mbr);

        // Crear particion primaria
        for (Structs::Particion particion : particiones)
        {

            if (particion.Part_status == '0')
            {
                // Si la particion es la ultima, se crea
                particion.Part_status = '1';
                particion.Part_type = 'p';
                particion.Part_fit = fit.substr(0, 1).c_str()[0];
                particion.Part_size = size;
                strcpy(particion.Part_name, name.c_str());
                particion.Part_start = ValorInicial;
                break;
            }
            else
            {
                // Si la particion no es la ultima, se suma el tamaño de la particion
                ValorInicial = particion.Part_start + particion.Part_size;
            }
        }

        // Actualizar el MBR
        mbr.Mbr_Particion1 = particiones[0];
        mbr.Mbr_Particion2 = particiones[1];
        mbr.Mbr_Particion3 = particiones[2];
        mbr.Mbr_Particion4 = particiones[3];

        // Escribir el MBR en el disco
        FILE *archivo;
        archivo = fopen(path.c_str(), "rb+");
        if (archivo == NULL)
        {
            Scan.Errores("FDISK", "Error - No se pudo localizar el disco al momento de actulizar el MBR");
            return;
        }
        rewind(archivo);
        fwrite(&mbr, sizeof(mbr), 1, archivo);
        fclose(archivo);
    }
    else if (type == "e")
    {
        cout << "Extendida" << endl;
        // Crear particion extendida
        if (ContarTipoParticion(particiones, "e") > 0)
        {
            Scan.Errores("FDISK", "Ya existe una particion extendida en el disco");
            return;
        }
    }
    else if (type == "l")
    {
        cout << "Logica" << endl;
        // Crear particion logica
        if (ContarTipoParticion(particiones, "e") == 0)
        {
            Scan.Errores("FDISK", "No existe una particion extendida en el disco, no es posible crear una particion logica");
            return;
        }
    }
}

void Disk::DeletePartition(string path, string name, string del)
{
    Scan.Mensaje("FDISK - ¿Desea eliminar la particion " + name + " del disco " + path + "? (S/N): ");
    string Confirmacion;
    cout << ">> ";
    getline(cin, Confirmacion);
    if (Scan.Compare(Confirmacion, "s"))
    {
        Scan.Aviso("FDISK - Particion eliminada correctamente");
    }
    else
    {
        Scan.Aviso("FDISK - Operacion cancelada");
    }
}

void Disk::AddPartition(string path, string name, int add, string unit)
{
    Scan.Aviso("FDISK - Se ha agregado " + to_string(add) + " " + unit + " a la particion " + name);
}