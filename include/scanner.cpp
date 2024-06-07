#include "scanner.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <locale>
#include <vector>
#include <cstdlib>

using namespace std;

void Clear(){
    cout << "\x1B[2J\x1B[H"; // Clear console
}

void scanner::start(){
    system("clear"); // Clear console
    std::cout << "Scanner started" << std::endl;
    std::cout << ">>";
    while(true){
        string texto;
        getline(cin, texto);
        if (compare(texto, "exit")){
            break;
        }
    }
}