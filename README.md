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

## Formato do arquivo de teste

O arquivo `arquivo_teste.txt` deve seguir o seguinte formato:

```txt
quantum tamanho_da_ram penalidade_io
tempo_chegada nome_processo sequencia_de_paginas
tempo_chegada nome_processo sequencia_de_paginas
```

Exemplo:

```txt
3 2 4
0 P1 1,2,1
1 P2 2,3
```

Neste exemplo:

- O quantum do Round Robin é `3`;
- A memória RAM possui `2` frames;
- A penalidade de I/O é de `4` tiques;
- O processo `P1` chega no tempo `0` e acessa as páginas `1,2,1`;
- O processo `P2` chega no tempo `1` e acessa as páginas `2,3`.

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

## Saída esperada

O programa imprime no console:

- Configurações da simulação;
- Chegada dos processos;
- Entrada de processos na CPU;
- Acessos às páginas;
- Ocorrências de RAM Hit;
- Ocorrências de Page Fault;
- Movimentação para fila de bloqueados;
- Retorno para fila de prontos;
- Substituições de página usando LRU;
- Estado atual da RAM;
- Relatório final.

Exemplo de eventos exibidos:

```txt
[Tempo 0] P1 chegou e entrou na fila de prontos.
[Tempo 0] P1 entrou na CPU.
[Tempo 0] P1 solicitou pagina 1.
[Tempo 0] PAGE FAULT: pagina 1 de P1 nao esta na RAM.
[Tempo 0] Pagina 1 de P1 carregada em um frame livre da RAM.
```

## Relatório final

Ao final da execução, o simulador apresenta:

- Tempo de chegada;
- Tempo de retorno;
- Total de Page Faults de cada processo;
- Tempo total da simulação.

Exemplo:

```txt
===================================
 RELATORIO FINAL
===================================
Processo: P1
Tempo de chegada: 0
Tempo de retorno: 15
Total de Page Faults: 3
-----------------------------------
Processo: P2
Tempo de chegada: 1
Tempo de retorno: 20
Total de Page Faults: 4
-----------------------------------
Tempo total da simulacao: 21
```

## Observações

O arquivo `arquivo_teste.txt` deve estar na mesma pasta do executável para que o programa consiga realizar a leitura corretamente.

Caso o programa apresente erro ao abrir o arquivo, verifique se o nome do arquivo está correto e se ele está na mesma pasta do projeto.

## Comandos Git úteis

Para adicionar o README e os demais arquivos ao repositório, use:

```bash
git status
git add .
git commit -m "Adiciona simulador Round Robin com paginacao LRU"
git push
```

Caso seja o primeiro envio para o repositório remoto, use:

```bash
git push -u origin main
```

Se sua branch principal for `master`, use:

```bash
git push -u origin master
```
