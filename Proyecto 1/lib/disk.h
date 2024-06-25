#ifndef DISK_H
#define DISK_H

#include "./structs.h"

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Disk
{
public:
    Disk();

    // Crear disco
    void mkdisk(vector<string> tks);
    void CreateDisk(string path, int size, string unit, string fit);

    // Remover disco
    void rmdisk(vector<string> tks);
    void RemoveDisk(string path);

    // Particiones
    void fdisk(vector<string> tks);
    void CreatePartition(int size, string unit, string path, string type, string fit, string name);
    void DeletePartition(string path, string name, string del);
    void AddPartition(string path, string name, int add, string unit);

    // Auxiliares
    Structs::MBR ObtenerMBR(string path);
    int ContarTipoParticion(vector<Structs::Particion> particiones, string type);
    vector<Structs::Particion> ObtenerParticiones(Structs::MBR mbr);
    vector<Structs::EBR> ObtenerParticionesLogicas(Structs::Particion particion, string path);
};

#endif