#ifndef HASHDIC_H
#define HASHDIC_H


#include "Dicionario.hpp"

/*Declaracao da implementacao em tabela Hash da interface Dicionario*/
class HashDic : public Dicionario{
public:
	HashDic(int N) : Dicionario(N){
		tabela_ = new ListaVerbetes<Verbete>[N];
		entradas_=0;
	}

	//funcoes especificas do HashDic:
	Verbete* hashParaVetor() const;
	int getEntradas() const {return entradas_;}

	//Cabecalho da implementacao das funcoes virtuais puras do dicionario.
	Verbete* pesquisa(std::string chave, char tipo);
	void insereVerbete(Verbete* it);
	void imprime();
	void atualiza(Verbete* it);
	void removeVerbete(Verbete* it);
	~HashDic();

private:
	//Funcao geradora de hash por strings. Retorna um index da tabela.
	int Hash(std::string chave);
	int entradas_;
	ListaVerbetes<Verbete>* tabela_;
};


#endif