#include "../lib/mount.h"
#include "../lib/structs.h"

#include <iostream>
#include <vector>

using namespace std;

Mount::Mount()
{
}

void Mount::mount(vector<string> tks, vector<Structs::ParticionMount> &Mounts)
{

}

void Mount::MountPartition(string path, string name)
{
    cout << "Montando particion " << name << " en " << path << endl;
}

void Mount::umount(vector<string> tks, vector<Structs::ParticionMount> &Mounts)
{

}

void Mount::UnmountPartition(string id)
{
    cout << "Desmontando particion " << id << endl;
}