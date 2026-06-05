#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <vector>
#include <queue>
#include <deque>
#include <string>

#include "Processo.h"
#include "FrameRAM.h"

using namespace std;

class Simulador {
private:
    vector<Processo> processos;
    queue<int> fila_prontos;
    deque<int> bloqueados;
    vector<FrameRAM> ram;

    int quantum;
    int tamanho_ram;
    int penalidade_io;
    int tempo;

public:
    Simulador();

    bool lerArquivo(string nome_arquivo);
    void executar();

private:
    vector<int> separarPaginas(string texto);

    bool todosFinalizados();
    int buscarPaginaNaRAM(int id_processo, int pagina);

    void atualizarChegadas();
    void atualizarBloqueados();

    void carregarPaginaNaRAM(Processo& processo, int pagina);
    void imprimirRAM();
    void imprimirRelatorioFinal();
};

#endif