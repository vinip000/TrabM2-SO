# Simulador Round Robin com Paginação sob Demanda e LRU

## Autores

- Vinicius Pereira
- Thiago Pacheco

## Descrição

Este projeto implementa um simulador em C++ que integra:

- Escalonamento de CPU com Round Robin;
- Gerenciamento de memória virtual com paginação sob demanda;
- Tratamento de Page Fault;
- Fila de processos prontos;
- Fila de processos bloqueados;
- Penalidade de I/O;
- Substituição de páginas utilizando o algoritmo LRU (Least Recently Used).

O simulador funciona por tempo discreto, ou seja, a execução acontece por tiques de relógio. A cada ciclo, o sistema verifica chegadas de processos, processos bloqueados, acessos à memória e execução na CPU.

## Estrutura dos arquivos

```txt
.
├── arquivo_teste.txt
├── FrameRAM.h
├── main.cpp
├── Processo.h
├── Simulador.cpp
├── Simulador.h
└── README.md
```
## Como compilar

No terminal, dentro da pasta do projeto, execute:

```bash
g++ main.cpp Simulador.cpp -o simulador.exe
```

## Como executar

Após compilar, execute:

### Windows PowerShell

```bash
.\simulador.exe
```

### Linux, WSL ou Git Bash

```bash
./simulador.exe
```
