#include <iostream>

#include "Simulador.h"

using namespace std;

int main() {
    Simulador simulador;

    string nome_arquivo = "arquivo_teste.txt";

    if (!simulador.lerArquivo(nome_arquivo)) {
        return 1;
    }

    simulador.executar();

    return 0;
}