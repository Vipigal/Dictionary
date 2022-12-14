#include <iostream>
#include <string>
#include "msgAssert.h"
#include <fstream>
#include "HashDic.hpp"
#include <sstream>

using std::cout;
using std::string;
using std::endl;


int main(int argc, char const *argv[]){

    //loop para salvar as flags de comando.
    string nomeArquivoEntrada, nomeArquivoSaida, implementacao;

    for (int i = 1; i < argc; i++){
		std::string buffer = argv[i];
        if (buffer.compare("-i") == 0 && i + 1 <= argc){
			nomeArquivoEntrada = argv[i + 1];
		}
		else if (buffer.compare("-o") == 0 && i + 1 <= argc){
			nomeArquivoSaida = argv[i + 1];
		}
		else if (buffer.compare("-t") == 0 && i + 1 <= argc){
			implementacao = argv[i + 1];
		}
	}
	//testar se as flags de comando sao validas.
	std::ifstream input(nomeArquivoEntrada);
	erroAssert(input, "Nao foi possivel abrir o arquivo de input! Favor inserir entrada valida com a flag -i");
	std::ofstream output(nomeArquivoSaida, std::ios_base::app);
	erroAssert(output, "Nao foi possivel abrir o arquivo de output! Favor inserir entrada valida com a flag -o");

	string buffer;
	int numeroLinhas=0;
	while(getline(input,buffer)){
		numeroLinhas++;
	}
	//O fator de carga usado sera de 50%, pois costuma trazer bons resultados segundo esses amigo ai: W. Celes e J. L. Rangel
	int tamanhoTabelaHash = numeroLinhas * 2;
	HashDic dic(tamanhoTabelaHash);
	input.clear();             //clear the buffer
	input.seekg(0, std::ios::beg);

	char tipo;
	string verbete;

	while(getline(input,buffer)){
		try{
			Verbete *temp = new Verbete;
			Significado* significado = new Significado;
			//declara buffers para guardar pedacos do input
			std::stringstream s(buffer);
			//pega o tipo do verbete
			s>>tipo;
			//pega os indices dos delimitadores []
			unsigned first = buffer.find('[');
			unsigned last = buffer.find(']');
			//acha o verbete entre os delimitadores
			verbete = buffer.substr(first+1, last-first-1);
			//acha o significado, se houver um
			if(last+2 > buffer.length()){
				significado->significado_ = "";
			}else{
				significado->significado_ = buffer.substr(last+2);
			}
			//cout<<verbete<<" "<<tipo<<" "<<significado->significado_<<endl;

			temp->chave_=verbete;
			temp->tipo_=tipo;
			temp->significados_.insereFinal(significado);
			
			if(dic.pesquisa(temp->chave_, temp->tipo_)==nullptr){
				dic.insereVerbete(temp);
			}else{
				dic.atualiza(temp);
			}

		}
		catch( const std::exception& e){
			std::cout << e.what() << '\n';
		}
	}


	dic.imprime();
	cout<<dic.getEntradas()<<endl;

	input.close();
	
    return 0;
}
