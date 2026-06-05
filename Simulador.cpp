#include "Simulador.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Simulador::Simulador() {
    quantum = 0;
    tamanho_ram = 0;
    penalidade_io = 0;
    tempo = 0;
}

vector<int> Simulador::separarPaginas(string texto) {
    vector<int> paginas;
    stringstream ss(texto);
    string item;

    while (getline(ss, item, ',')) {
        paginas.push_back(stoi(item));
    }

    return paginas;
}

bool Simulador::lerArquivo(string nome_arquivo) {
    ifstream arquivo(nome_arquivo);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo: " << nome_arquivo << endl;
        return false;
    }

    arquivo >> quantum >> tamanho_ram >> penalidade_io;

    int chegada;
    string nome;
    string sequencia;

    int id = 0;

    while (arquivo >> chegada >> nome >> sequencia) {
        Processo processo;

        processo.id = id;
        processo.nome = nome;
        processo.tempo_chegada = chegada;
        processo.paginas = separarPaginas(sequencia);

        processos.push_back(processo);

        id++;
    }

    arquivo.close();
    return true;
}

bool Simulador::todosFinalizados() {
    for (const auto& processo : processos) {
        if (!processo.finalizado) {
            return false;
        }
    }

    return true;
}

int Simulador::buscarPaginaNaRAM(int id_processo, int pagina) {
    for (int i = 0; i < ram.size(); i++) {
        if (
            ram[i].id_processo == id_processo &&
            ram[i].numero_pagina == pagina
        ) {
            return i;
        }
    }

    return -1;
}

void Simulador::atualizarChegadas() {
    for (int i = 0; i < processos.size(); i++) {
        if (!processos[i].chegou && processos[i].tempo_chegada <= tempo) {
            processos[i].chegou = true;
            fila_prontos.push(i);

            cout << "[Tempo " << tempo << "] "
                 << processos[i].nome
                 << " chegou e entrou na fila de prontos."
                 << endl;
        }
    }
}

void Simulador::atualizarBloqueados() {
    int quantidade = bloqueados.size();

    for (int i = 0; i < quantidade; i++) {
        int id = bloqueados.front();
        bloqueados.pop_front();

        processos[id].tempo_bloqueado_restante--;

        if (processos[id].tempo_bloqueado_restante <= 0) {
            processos[id].bloqueado = false;
            fila_prontos.push(id);

            cout << "[Tempo " << tempo << "] "
                 << processos[id].nome
                 << " saiu da fila de bloqueados e voltou para a fila de prontos."
                 << endl;
        } else {
            bloqueados.push_back(id);
        }
    }
}

void Simulador::carregarPaginaNaRAM(Processo& processo, int pagina) {
    if (ram.size() < tamanho_ram) {
        FrameRAM novo_frame;

        novo_frame.id_processo = processo.id;
        novo_frame.nome_processo = processo.nome;
        novo_frame.numero_pagina = pagina;
        novo_frame.ultimo_uso = tempo;

        ram.push_back(novo_frame);

        cout << "[Tempo " << tempo << "] "
             << "Pagina " << pagina << " de " << processo.nome
             << " carregada em um frame livre da RAM."
             << endl;

        return;
    }

    int indice_lru = 0;

    for (int i = 1; i < ram.size(); i++) {
        if (ram[i].ultimo_uso < ram[indice_lru].ultimo_uso) {
            indice_lru = i;
        }
    }

    cout << "[Tempo " << tempo << "] "
         << "RAM cheia. LRU removeu pagina "
         << ram[indice_lru].numero_pagina
         << " de " << ram[indice_lru].nome_processo
         << "."
         << endl;

    ram[indice_lru].id_processo = processo.id;
    ram[indice_lru].nome_processo = processo.nome;
    ram[indice_lru].numero_pagina = pagina;
    ram[indice_lru].ultimo_uso = tempo;

    cout << "[Tempo " << tempo << "] "
         << "Pagina " << pagina << " de " << processo.nome
         << " carregada na RAM."
         << endl;
}

void Simulador::imprimirRAM() {
    cout << "RAM: ";

    if (ram.empty()) {
        cout << "[vazia]";
    }

    for (const auto& frame : ram) {
        cout << "[" << frame.nome_processo
             << " Pag:" << frame.numero_pagina
             << " UltUso:" << frame.ultimo_uso
             << "] ";
    }

    cout << endl;
}

void Simulador::executar() {
    cout << "===================================" << endl;
    cout << " SIMULADOR RR + PAGINACAO + LRU" << endl;
    cout << "===================================" << endl;
    cout << "Quantum: " << quantum << endl;
    cout << "Tamanho da RAM: " << tamanho_ram << " frames" << endl;
    cout << "Penalidade de I/O: " << penalidade_io << " ticks" << endl;
    cout << "===================================" << endl;

    int id_processo_cpu = -1;
    int quantum_usado = 0;

    while (!todosFinalizados()) {
        cout << endl;
        cout << "----------- CLOCK " << tempo << " -----------" << endl;

        atualizarChegadas();
        atualizarBloqueados();

        if (id_processo_cpu == -1) {
            if (fila_prontos.empty()) {
                cout << "[Tempo " << tempo << "] CPU ociosa." << endl;
                imprimirRAM();
                tempo++;
                continue;
            }

            id_processo_cpu = fila_prontos.front();
            fila_prontos.pop();
            quantum_usado = 0;

            cout << "[Tempo " << tempo << "] "
                 << processos[id_processo_cpu].nome
                 << " entrou na CPU."
                 << endl;
        }

        Processo& processo = processos[id_processo_cpu];

        if (processo.finalizado || processo.bloqueado) {
            id_processo_cpu = -1;
            quantum_usado = 0;
            tempo++;
            continue;
        }

        int pagina_solicitada = processo.paginas[processo.indice_pagina_atual];

        cout << "[Tempo " << tempo << "] "
             << processo.nome
             << " solicitou pagina " << pagina_solicitada << "."
             << endl;

        int indice_ram = buscarPaginaNaRAM(
            processo.id,
            pagina_solicitada
        );

        if (indice_ram != -1) {
            cout << "[Tempo " << tempo << "] "
                 << "RAM HIT: pagina " << pagina_solicitada
                 << " de " << processo.nome
                 << " ja esta na RAM."
                 << endl;

            ram[indice_ram].ultimo_uso = tempo;

            processo.indice_pagina_atual++;
            quantum_usado++;

            if (processo.indice_pagina_atual >= processo.paginas.size()) {
                processo.finalizado = true;
                processo.tempo_retorno = tempo + 1;

                cout << "[Tempo " << tempo + 1 << "] "
                     << processo.nome
                     << " finalizou sua execucao."
                     << endl;

                id_processo_cpu = -1;
                quantum_usado = 0;
            } else if (quantum_usado == quantum) {
                fila_prontos.push(processo.id);

                cout << "[Tempo " << tempo + 1 << "] "
                     << processo.nome
                     << " sofreu preempcao por fim de Quantum e voltou para a fila de prontos."
                     << endl;

                id_processo_cpu = -1;
                quantum_usado = 0;
            }
        } else {
            cout << "[Tempo " << tempo << "] "
                 << processo.nome
                 << " sofreu Page Fault na pagina "
                 << pagina_solicitada << "."
                 << endl;

            processo.page_faults++;

            carregarPaginaNaRAM(processo, pagina_solicitada);

            processo.tempo_bloqueado_restante = penalidade_io;
            processo.bloqueado = true;
            bloqueados.push_back(processo.id);

            cout << "[Tempo " << tempo << "] "
                 << processo.nome
                 << " foi para a fila de bloqueados por "
                 << penalidade_io << " ticks."
                 << endl;

            id_processo_cpu = -1;
            quantum_usado = 0;
        }

        imprimirRAM();
        tempo++;
    }

    imprimirRelatorioFinal();
}

void Simulador::imprimirRelatorioFinal() {
    cout << endl;
    cout << "===================================" << endl;
    cout << " RELATORIO FINAL" << endl;
    cout << "===================================" << endl;

    for (const auto& processo : processos) {
        cout << "Processo: " << processo.nome << endl;
        cout << "Tempo de chegada: " << processo.tempo_chegada << endl;
        cout << "Tempo de retorno: "
             << processo.tempo_retorno - processo.tempo_chegada
             << endl;
        cout << "Total de Page Faults: "
             << processo.page_faults
             << endl;
        cout << "-----------------------------------" << endl;
    }

    cout << "Tempo total da simulacao: " << tempo << endl;
}