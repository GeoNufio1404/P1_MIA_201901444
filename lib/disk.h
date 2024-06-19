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

    typedef struct _Transition
    {
        string Particion;
        int Start;
        int End;
        int Before;
        int After;
    } Transition;

    void mkdisk(vector<string> tks);
    void CreateDisk(string path, int size, string unit, string fit);

    void rmdisk(vector<string> tks);
    void RemoveDisk(string path);

    void fdisk(vector<string> tks);
    void CreatePartition(int size, string unit, string path, string type, string fit, string name);
    void DeletePartition(string path, string name, string del);
    void AddPartition(string path, string name, int add, string unit);
    vector<Structs::Particion> GetPartitions(Structs::MBR mbr);
};

#endif