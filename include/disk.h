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
    void makeDisk(string path, int size, string unit);
    void rmdisk(vector<string> tks);
    void removeDisk(string path);
    void fdisk(vector<string> tks);
};

#endif