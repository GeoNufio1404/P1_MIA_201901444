#ifndef MOUNT_H
#define MOUNT_H

#include <vector>
#include <string>

using namespace std;

class Mount
{
public:
    Mount();

    // Montar
    void mount(vector<string> tks, vector<Structs::ParticionMount> &Mounts);
    void MountPartition(string path, string name);

    // Desmontar
    void umount(vector<string> tks, vector<Structs::ParticionMount> &Mounts);
    void UnmountPartition(string id);
};

#endif // MOUNT_H