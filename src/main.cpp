#include <iostream>
#include <string>
#include "msgAssert.h"
#include <fstream>
#include "HashDic.hpp"
#include "AVLDic.hpp"
#include <sstream>

using std::cout;
using std::string;
using std::endl;

string transformaEmMinuscula(string s){
	int tam = s.length();
	for(int i=0;i<tam;i++){
		s[i]=tolower(s[i]);
	}
	return s;
}


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
	std::ofstream output(nomeArquivoSaida);
	erroAssert(output, "Nao foi possivel abrir o arquivo de output! Favor inserir entrada valida com a flag -o");
	erroAssert(implementacao=="arv" || implementacao == "hash", "A implementacao desejada deve ser selecionada com a flag -t. Valores validos: hash, arv");

	//Pega o numero de linhas total do arquivo de entrada
	string buffer;
	int numeroLinhas=0;
	while(getline(input,buffer)){
		numeroLinhas++;
	}
	
	//Instancia os dicionarios.
	int tamanhoTabelaHash = numeroLinhas * 2; //O fator de carga usado sera de 50%, pois costuma trazer bons resultados segundo esses amigo ai: W. Celes e J. L. Rangel
	HashDic hashDic(tamanhoTabelaHash);

	AVLDic avlDic(numeroLinhas);
	

	input.clear();             //clear the buffer
	input.seekg(0, std::ios::beg);

	//loop principal de captura de dados do input
	char tipo;
	string verbete;
	while(getline(input,buffer)){
		try{
			//instancia novos verbetes e significados para serem preenchidos com o input
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
			verbete=transformaEmMinuscula(verbete);

			//acha o significado, se houver um
			if(last+2 < buffer.length()){
				significado->significado_ = buffer.substr(last+2);
				temp->significados_.insereFinal(significado);
			}
			
			//Preenche o verbete temporario com seus atributos
			temp->chave_=verbete;
			temp->tipo_=tipo;
			

			//Insere o verbete no dicionario dependendo de sua implementacao
			if(implementacao=="hash"){
				if(hashDic.pesquisa(temp->chave_, temp->tipo_)==nullptr){
					hashDic.insereVerbete(temp);
				}else{
					hashDic.atualiza(temp);
				}
			}else
			if(implementacao=="arv"){
				avlDic.insereVerbete(temp);
			}

		}
		catch(const std::exception& e){
			std::cout << e.what() << '\n';
		}
	} 

	//Imprime o dicionario completo.
	if(implementacao=="hash"){
		hashDic.imprime(output);
		hashDic.removeVerbetesComSignificado();
		hashDic.imprime(output);
	}else if(implementacao=="arv"){
		avlDic.imprime(output);
		avlDic.imprimeSemSig(output);
	}



	input.close();
	output.close();
    return 0;
}
