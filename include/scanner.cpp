#include "../lib/scanner.h"

#include "../lib/disk.h"
#include "../lib/mount.h"

#include <iostream>
#include <stdlib.h>
#include <locale>
#include <cstring>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

Disk Disco;
Mount Montar;
vector<Structs::ParticionMount> Mounts;

// ======================== CONSTRUCTOR ========================
Scanner::Scanner()
{
}

// ========================= CLEAR =========================
void Scanner::Clear()
{
    cout << "\x1B[2J\x1B[H"; // Limpiar consola
}

// ========================= AVISO =========================
void Scanner::Aviso(string mensaje)
{
    // Mostrar avisos de color amarillo
    cout << endl;
    cout << "\t\033[1;33m AVISO: " << mensaje << "\033[0m" << endl;
    cout << endl;
}

// ========================= MENSAJE =========================
void Scanner::Mensaje(string mensaje)
{
    // Mostrar mensajes de color verde
    cout << "\t\033[1;32m" << mensaje << "\033[0m" << endl;
}

// ========================= UPPER =========================
string Scanner::Upper(string str)
{
    string str_upper = str;
    for (int i = 0; i < str_upper.length(); i++)
    {
        str_upper[i] = toupper(str_upper[i]); // Convertir a mayusculas
    }
    return str_upper;
}

// ========================= TOKEN =========================
string Scanner::Token(string tk)
{
    string tkn = "";
    bool Terminar = false;
    for (char &c : tk)
    {
        if (Terminar)
        {
            if (c == ' ' || c == '-')
            {
                break;
            }
            tkn += c;
        }
        else if (c != ' ' && !Terminar)
        {
            if (c == '#')
            {
                tkn = tk;
                break;
            }
            else
            {
                tkn += c;
                Terminar = true;
            }
        }
    }
    return tkn;
}

// ========================= SPLIT TOKENS =========================
vector<string> Scanner::SplitTokens(string text)
{
    vector<string> tokens;
    if (text.empty())
    {
        return tokens;
    }
    text.push_back(' ');
    string token = "";
    int estado = 0;
    for (char &c : text)
    {
        if (c == '\n')
        {
            cout << "Salto de linea" << endl;
        }

        switch (estado)
        {
        case 0:
            if (c == '-')
            {
                estado = 1;
                continue;
            }
            else if (c == '#')
            {
            }
            break;
        case 1:
            if (c == '=')
            {
                estado = 2;
            }
            else if (c == ' ')
            {
                continue;
            }
            break;
        case 2:
            if (c == '\"')
            {
                estado = 3;
            }
            else
            {
                estado = 4;
            }
            break;
        case 3:
            if (c == '\"')
            {
                estado = 4;
            }
            break;
        case 4:
            if (c == ' ')
            {
                estado = 0;
                tokens.push_back(token);
                token = "";
                continue;
            }
            else if (c == '\"')
            {
                tokens.clear();
                continue;
            }
            break;
        default:
            break;
        }

        token += c;
    }
    return tokens;
}

// ========================= COMPARE =========================
bool Scanner::Compare(string tk, string token)
{
    if (Upper(tk) == Upper(token))
    {
        return true;
    } // Comparar los tokens
    return false;
}

// ========================= ERRORES =========================
void Scanner::Errores(string operacion, string mensaje)
{
    // Mostrar error de color rojo
    cout << endl;
    cout << "\t\033[1;31m ERROR: " << operacion << " - " << mensaje << "\033[0m" << endl;
    cout << endl;
}

// ========================= START =========================
void Scanner::Start()
{
    system("clear"); // Limpiar consola
    Clear();

    // Mostrar mensaje de bienvenida
    Mensaje("Bienvenido a la consola de comandos de MIA");
    Mensaje("Para salir de la consola escriba 'exit' y presione enter");
    cout << endl;

    // Loop para leer los comandos
    while (true)
    {
        cout << ">> ";

        string texto;
        getline(cin, texto);

        if (Compare(texto, "exit"))
        {
            break;
        }
        string tk = Token(texto);
        texto.erase(0, tk.length() + 1);
        vector<string> tks = SplitTokens(texto); // Separar los tokens
        Functions(tk, tks);                      // Buscar las funciones
    }
}

// ========================= FUNCION EXEC =========================
void Scanner::FuncionExec(vector<string> tks)
{
    string path = "";
    for (string token : tks)
    {
        string tk = token.substr(0, token.find("="));
        token.erase(0, tk.length() + 1);
        if (Compare(tk, "path"))
        {
            path = token;
        }
    }
    if (path.empty())
    {
        Errores("EXEC", "Se requiere path para este comando");
        return;
    }
    Excec(path);
}

// ========================= EXEC =========================
void Scanner::Excec(string path)
{
    string filename(path);
    vector<string> lines;
    string line;
    ifstream input_file(filename);

    if (!input_file.is_open())
    {
        Errores("EXEC", "No se pudo abrir el archivo");
        return;
    }

    while (getline(input_file, line))
    {
        lines.push_back(line); // Leer las lineas del archivo
    }

    for (const auto &i : lines)
    {
        string texto = i;
        string tk = Token(texto);
        if (texto != "")
        {
            texto.erase(0, tk.length() + 1);
            vector<string> tks = SplitTokens(texto);
            Functions(tk, tks);
        }
    }
    input_file.close();
    return;
}

// ========================= FUNCTIONS =========================
void Scanner::Functions(string token, vector<string> tks)
{
    if (Compare(token, "mkdisk"))
    {
        Disco.mkdisk(tks);
    }
    else if (Compare(token, "rmdisk"))
    {
        Disco.rmdisk(tks);
    }
    else if (Compare(token, "fdisk"))
    {
        Disco.fdisk(tks);
    }
    else if (Compare(token, "mount"))
    {
        Montar.mount(tks, Mounts);
    }
    else if (Compare(token, "umount"))
    {
        Montar.umount(tks, Mounts);
    }
    else if (Compare(token, "rep"))
    {
        rep(tks);
    }
    else if (Compare(token, "pause"))
    {
        Aviso("PAUSE - Presione enter para continuar...");
        string pause;
        getline(cin, pause);
    }
    else if (Compare(token, "exec"))
    {
        FuncionExec(tks);
    }
    else
    {
        Errores("FUNCTIONS", "Comando no reconocido");
    }
}

// ========================= REPORTES =========================
void Scanner::rep(vector<string> tks)
{
    string nombre = "";
    string path = "";
    string id = "";
    string ruta = "";
    bool Error = false;

    for (string token : tks)
    {
        string tk = token.substr(0, token.find("="));
        token.erase(0, tk.length() + 1);

        if (Compare(tk, "path"))
        {
            if (path.empty())
            {
                // Si el path tiene comillas, se las quitamos
                if (token[0] == '\"' && token[token.length() - 1] == '\"')
                {
                    token = token.substr(1, token.length() - 2);
                }
                path = token;
            }
            else
            {
                Errores("REP", "Parametro path duplicado: " + tk);
                Error = true;
                break;
            }
        }
        else if (Compare(tk, "name"))
        {
            if (nombre.empty())
            {
                if (!Compare(token, "mbr") && !Compare(token, "disk"))
                {
                    Errores("REP", "Nombre de reporte no reconocido: " + token);
                    Error = true;
                }
                nombre = token;
            }
            else
            {
                Errores("REP", "Parametro name duplicado: " + tk);
                Error = true;
                break;
            }
        }
        else if (Compare(tk, "id"))
        {
            if (id.empty())
            {
                id = token;
            }
            else
            {
                Errores("REP", "Parametro id duplicado: " + tk);
                Error = true;
                break;
            }
        }
        else if (Compare(tk, "ruta"))
        {
            if (ruta.empty())
            {
                ruta = token;
            }
            else
            {
                Errores("REP", "Parametro ruta duplicado: " + tk);
                Error = true;
                break;
            }
        }
        else
        {
            Errores("REP", "Parametro no reconocido: " + tk);
            Error = true;
            break;
        }
    }

    if (!Error)
    {
        string dot = "";
        // Obtener el disco
        Structs::MBR mbr = Disco.ObtenerMBR(path);

        if (Compare(nombre, "mbr"))
        {
            dot = ReporteMBR(path, mbr);
        }
        CrearDot(ruta, dot);
    }
}

string Scanner::DotParticion(Structs::Particion particion)
{
    string Dot = "";

    // Titulo
    Dot += "    <TR>\n";
    Dot += "      <TD colspan=\"2\" bgcolor=\"#71B340\">Particion</TD>\n";
    Dot += "    </TR>\n";

    // Detalles de la particion
    Dot += "    <TR>\n";
    Dot += "        <TD bgcolor=\"#669D31\">part_status</TD>\n";
    Dot += "        <TD bgcolor=\"#598B2C\">" + to_string(particion.Part_status) + "</TD>\n";
    Dot += "    </TR>\n";
    Dot += "    <TR>\n";
    Dot += "        <TD bgcolor=\"#669D31\">part_type</TD>\n";
    Dot += "        <TD bgcolor=\"#598B2C\">" + to_string(particion.Part_type) + "</TD>\n";
    Dot += "    </TR>\n";
    Dot += "    <TR>\n";
    Dot += "        <TD bgcolor=\"#669D31\">part_fit</TD>\n";
    Dot += "        <TD bgcolor=\"#598B2C\">" + to_string(particion.Part_fit) + "</TD>\n";
    Dot += "    </TR>\n";
    Dot += "    <TR>\n";
    Dot += "        <TD bgcolor=\"#669D31\">part_start</TD>\n";
    Dot += "        <TD bgcolor=\"#598B2C\">" + to_string(particion.Part_start) + "</TD>\n";
    Dot += "    </TR>\n";
    Dot += "    <TR>\n";
    Dot += "        <TD bgcolor=\"#669D31\">part_size</TD>\n";
    Dot += "        <TD bgcolor=\"#598B2C\">" + to_string(particion.Part_size) + "</TD>\n";
    Dot += "    </TR>\n";
    Dot += "    <TR>\n";
    Dot += "        <TD bgcolor=\"#669D31\">part_name</TD>\n";
    string nombre = particion.Part_name;
    Dot += "        <TD bgcolor=\"#598B2C\">" + nombre + "</TD>\n";
    Dot += "    </TR>\n";

    return Dot;
}

string Scanner::ReporteMBR(string path, Structs::MBR mbr)
{
    string Titulo = "Reporte_MBR";
    string Dot = "digraph G {\n";
    Dot += "  fontname=\"Helvetica,Arial,sans-serif\"\n";
    Dot += "  node [fontname=\"Helvetica,Arial,sans-serif\"]\n";
    Dot += "  edge [fontname=\"Helvetica,Arial,sans-serif\"]\n";
    Dot += "  a0 [shape=none label=<<TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" bgcolor=\"#293132\" gradientangle=\"315\">\n";

    // Titulo
    Dot += "    <TR>\n";
    Dot += "      <TD colspan=\"2\" bgcolor=\"#388697\">" + Titulo + "</TD>\n";
    Dot += "    </TR>\n";

    // Detalles del MBR
    Dot += "    <TR>\n";
    Dot += "        <TD bgcolor=\"#35717E\">Mbr_tamano</TD>\n";
    Dot += "        <TD bgcolor=\"#315C65\">" + to_string(mbr.Mbr_tamano) + "</TD>\n";
    Dot += "    </TR>\n";
    struct tm *tm; // Estructura para la fecha
    tm = localtime(&mbr.Mbr_fecha_creacion);
    char mostrar_fecha[20];
    Dot += "    <TR>\n";
    Dot += "        <TD bgcolor=\"#35717E\">Mbr_fecha_creacion</TD>\n";
    Dot += "        <TD bgcolor=\"#315C65\">" + string(mostrar_fecha) + "</TD>\n";
    Dot += "    </TR>\n";
    Dot += "    <TR>\n";
    Dot += "        <TD bgcolor=\"#35717E\">Mbr_disk_signature</TD>\n";
    Dot += "        <TD bgcolor=\"#315C65\">" + to_string(mbr.Mbr_disk_signature) + "</TD>\n";
    Dot += "    </TR>\n";

    // Particiones
    vector<Structs::Particion> particiones = Disco.ObtenerParticiones(mbr);
    for (Structs::Particion particion : particiones)
    {
        if (particion.Part_status == '1')
        {
            Dot += DotParticion(particion);
        }
    }

    Dot += "  </TABLE>> color=\"#FF0000\"];\n";
    Dot += "}";

    return Dot;
}

void Scanner::CrearDot(string Nombre, string dot)
{
    ofstream Archivo;
    if (Nombre.empty())
    {
        Nombre = "../reports/ReporteMbr";
    }

    // si no termina en .dot, se lo agregamos
    if (Nombre.find(".dot") == string::npos)
    {
        Archivo.open(Nombre + ".dot", ios::out);
    }
    else
    {
        Archivo.open(Nombre, ios::out);
    }

    if (Archivo.fail())
    {
        Errores("REP", "Error al crear el archivo .dot");
    }
    else
    {
        Archivo << dot;
        Archivo.close();
        CrearImagen(Nombre);
    }
}

void Scanner::CrearImagen(string ruta)
{
    // Crear la imagen
    string comando = "dot -Tpng " + ruta + ".dot -o " + ruta + ".png";
    system(comando.c_str());
    // Borrar el archivo .dot
    comando = "rm " + ruta + ".dot";
    system(comando.c_str());
}