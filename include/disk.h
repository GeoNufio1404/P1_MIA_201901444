#ifndef DISK_H
#define DISK_H

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
};

#endif