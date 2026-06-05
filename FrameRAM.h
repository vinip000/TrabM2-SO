#ifndef FRAMERAM_H
#define FRAMERAM_H

#include <string>

using namespace std;

struct FrameRAM {
    int id_processo;
    string nome_processo;
    int numero_pagina;
    int ultimo_uso;
};

#endif