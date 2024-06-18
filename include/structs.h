#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
#include <ctime>

class Structs
{
public:
    Structs(); // Constructor

    typedef struct _Particion // Estructura de una partición
    {
        char part_status = '0'; // Estado de la partición
        char part_type;         // Tipo de partición
        char part_fit;          // Ajuste de la partición
        int part_start = -1;    // Byte de inicio de la partición
        int part_size = 0;      // Tamaño de la partición
        char part_name[16];     // Nombre de la partición
    } Particion;

    typedef struct _MBR // Estructura de un MBR
    {
        int mbr_tamano = 0;         // Tamaño del disco
        time_t mbr_fecha_creacion;  // Fecha de creación del disco
        int mbr_disk_signature = 0; // Número de identificación del disco
        char disk_fit;              // Ajuste del disco
        Particion mbr_Particion1;   // Partición 1
        Particion mbr_Particion2;   // Partición 2
        Particion mbr_Particion3;   // Partición 3
        Particion mbr_Particion4;   // Partición 4
    } MBR;

    typedef struct _EBR // Estructura de un EBR
    {
        char Part_status = '0'; // Estado de la partición
        char Part_fit;          // Ajuste de la partición
        int Part_start = -1;    // Byte de inicio de la partición
        int Part_size = 0;      // Tamaño de la partición
        int Part_next = -1;     // Byte de inicio del siguiente EBR
        char Part_name[16];     // Nombre de la partición
    } EBR;

    typedef struct _Inodos
    {
        int I_uid = 1;                                                                  // Identificador del usuario propietario del archivo o carpeta
        int I_gid = 1;                                                                  // Identificador del grupo al que pertenece el archivo o carpeta
        int I_size = 0;                                                                 // Tamaño del archivo en bytes
        time_t I_atime;                                                                 // Fecha y hora del último acceso al archivo o carpeta
        time_t I_ctime;                                                                 // Fecha y hora de la última modificación al inodo
        time_t I_mtime;                                                                 // Fecha y hora de la última modificación al archivo o carpeta
        int I_block[15] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; // Bloques de punteros
        char I_type = -1;                                                               // Tipo de inodo
        int I_perm = -1;
    } Inodos;

    typedef struct _Content
    {
        char B_name[12];  // Nombre del archivo o carpeta
        int B_inodo = -1; // Apuntador al inodo del archivo o carpeta
    } Content;

    typedef struct _FolderBlock
    {
        Content B_content[4]; // Bloques de contenido
    } FolderBlock;

    typedef struct _SuperBlock
    {
        int S_filesystem_type = -1;             // Tipo de sistema de archivos
        int S_inodes_count = -1;                // Cantidad de inodos
        int S_blocks_count = -1;                // Cantidad de bloques
        int S_free_blocks_count = -1;           // Cantidad de bloques libres
        int S_free_inodes_count = -1;           // Cantidad de inodos libres
        time_t S_mtime;                         // Última fecha y hora en la que se montó el sistema de archivos
        time_t S_umtime;                        // Última fecha y hora en la que se desmontó el sistema de archivos
        int S_mnt_count = -1;                   // Cantidad de veces que se ha montado el sistema de archivos
        int S_magic = 0xEF53;                   // Número mágico que identifica al sistema de archivos
        int S_inode_size = sizeof(Inodos);      // Tamaño del inodo
        int S_block_size = sizeof(FolderBlock); // Tamaño del bloque
        int S_first_ino = 0;                    // Primer inodo libre
        int S_first_blo = 0;                    // Primer bloque libre
        int S_bm_inode_start = -1;              // Inicio del bitmap de inodos
        int S_bm_block_start = -1;              // Inicio del bitmap de bloques
        int S_inode_start = -1;                 // Inicio de la tabla de inodos
        int S_block_start = -1;                 // Inicio de la tabla de bloques
    } SuperBlock;

    typedef struct _FileBlock
    {
        char b_content[64]; // Contenido del archivo
    } FileBlock;

    typedef struct _PointerBlock
    {
        int b_pointers[16] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; // Punteros a bloques de contenido
    } PointerBlock;

    typedef struct _Journaling
    {
        char Operation = -1; // Operación realizada
        char Type = -1;      // Tipo de operación
        char Path[100];      // Nombre del archivo o carpeta
        char Content[60];    // Contenido del archivo
        time_t Date;         // Fecha y hora de la operación
        int Size = -1;       // Tamaño del archivo
    } Journaling;
};

#endif // STRUCTS_H