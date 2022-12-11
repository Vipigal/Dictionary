#include <iostream>
#include <string>
#include "msgAssert.h"
#include <fstream>

using std::cout;
using std::string;
using std::endl;


int main(int argc, char const *argv[]){
    
    string nomeArquivoEntrada;
    string nomeArquivoSaida;
    int implementacao;

    for (int i = 1; i < argc; i++){
		std::string buffer = argv[i];
        if (buffer.compare("-i") == 0 && i + 1 <= argc){
			nomeArquivoEntrada = argv[i + 1];
		}
		else if (buffer.compare("-o") == 0 && i + 1 <= argc){
			nomeArquivoSaida = argv[i + 1];
		}
		else if (buffer.compare("-t") == 0 && i + 1 <= argc){
			implementacao = atoi(argv[i + 1]);
		}

        std::ifstream input(nomeArquivoEntrada);
        erroAssert(input, "Nao foi possivel abrir o arquivo de input! Favor inserir entrada valida com a flag -i");
        std::ofstream output(nomeArquivoSaida, std::ios_base::app);
        erroAssert(output, "Nao foi possivel abrir o arquivo de output! Favor inserir entrada valida com a flag -o");

	}

    return 0;
}
