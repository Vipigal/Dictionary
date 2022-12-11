#include <iostream>
#include <string>
#include "msgAssert.h"
#include <fstream>
#include "HashDic.hpp"

using std::cout;
using std::string;
using std::endl;


int main(int argc, char const *argv[]){
    
    // string nomeArquivoEntrada;
    // string nomeArquivoSaida;
    // int implementacao;

    // for (int i = 1; i < argc; i++){
	// 	std::string buffer = argv[i];
    //     if (buffer.compare("-i") == 0 && i + 1 <= argc){
	// 		nomeArquivoEntrada = argv[i + 1];
	// 	}
	// 	else if (buffer.compare("-o") == 0 && i + 1 <= argc){
	// 		nomeArquivoSaida = argv[i + 1];
	// 	}
	// 	else if (buffer.compare("-t") == 0 && i + 1 <= argc){
	// 		implementacao = atoi(argv[i + 1]);
	// 	}
	// }
	// std::ifstream input(nomeArquivoEntrada);
	// erroAssert(input, "Nao foi possivel abrir o arquivo de input! Favor inserir entrada valida com a flag -i");
	// std::ofstream output(nomeArquivoSaida, std::ios_base::app);
	// erroAssert(output, "Nao foi possivel abrir o arquivo de output! Favor inserir entrada valida com a flag -o");

	HashDic dic(30);
	Verbete teste[5];
	teste[0].chave_="almoco";
	teste[0].tipo_='s';
	teste[1].chave_="rua";
	teste[1].tipo_='s';
	teste[2].chave_="comer";
	teste[2].tipo_='v';
	teste[3].chave_="amar";
	teste[3].tipo_='v';
	teste[4].chave_="burro";
	teste[4].tipo_='a';
	try
	{
		for(int i=0;i<5;i++){
			dic.insereVerbete(&teste[i]);
		}
		// dic.insereVerbete(&teste[1]);
	}
	catch(const string& e)
	{
		std::cerr << e << '\n';
	}
	
	
	Verbete* teste2=dic.pesquisa("almoco");
	if(teste2==nullptr){
		cout<<"falhou"<<endl;
		return -1;
	}
	

	cout<<dic.getEntradas()<<endl;

    return 0;
}
