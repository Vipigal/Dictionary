#ifndef HASHDIC_H
#define HASHDIC_H


#include "Dicionario.hpp"
#include <iostream>

/*Declaracao da implementacao em tabela Hash da interface Dicionario*/
class HashDic : public Dicionario{
public:
	//Cria uma instancia de dicionario hash.
	HashDic(int N);

	//Transforma uma tabela hash em um vetor.
	Verbete* hashParaVetor() const;
	//Retorna o numero de entradas da tabela.
	int getEntradas() const {return entradas_;}
	//Remove todos os verbetes que possuam significado.
	void removeVerbetesComSignificado(){
		Verbete* it;

		for(int i=0;i<getTamanho();i++){
			for(it=tabela_[i].getPrimeiro();it!=nullptr;it=it->prox_){
				if(!(it->significados_.vazia())){
					removeVerbete(it->chave_, it->tipo_);
				}
			}
		}
	}

	//funcoes da interface dicionario:

	//Pesquisa um verbete pela sua chave.
	Verbete* pesquisa(std::string chave, char tipo);
	//Insere um verbete it na tabela.
	void insereVerbete(Verbete* it);
	//Imprime a tabela hash de forma ordenada.
	void imprime(std::ostream& out);
	//Atualiza o significado de um verbete ja existente na tabela.
	void atualiza(Verbete* it);
	//Remove um verbete pela sua chave.
	void removeVerbete(std::string chave, char tipo);
	~HashDic();

private:
	//Funcao geradora de hash por strings. Retorna um index da tabela.
	int Hash(std::string chave);
	int entradas_;
	ListaVerbetes<Verbete>* tabela_;
};


#endif