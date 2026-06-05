#include <iostream>
#include <string>

#include "Simulador.h"

using namespace std;

int main(int argc, char* argv[]) {
    Simulador simulador;

    string nome_arquivo = "arquivo_teste.txt";

    if (argc > 1) {
        nome_arquivo = argv[1];
    }

    cout << "Arquivo de entrada: " << nome_arquivo << endl;

    if (!simulador.lerArquivo(nome_arquivo)) {
        return 1;
    }

    simulador.executar();

    return 0;
}