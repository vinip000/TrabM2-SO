#ifndef PROCESSO_H
#define PROCESSO_H

#include <string>
#include <vector>

using namespace std;

struct Processo {
    int id;
    string nome;
    int tempo_chegada;
    vector<int> paginas;

    int indice_pagina_atual = 0;
    int page_faults = 0;
    int tempo_retorno = -1;
    int tempo_bloqueado_restante = 0;

    bool finalizado = false;
    bool chegou = false;
    bool bloqueado = false;
};

#endif