#ifndef DADOS_H
#define DADOS_H

#include "lista.hpp"
#include <fstream>

/*Declaracao do Significado:*/
struct Significado{
	std::string significado_;
	Significado* prox_;
};

/*Declaracao de uma Lista encadeada de Significados herdada da classe Template ListaBase*/
template <typename T>
class ListaSignificados : public ListaBase<T>{
	public:
		//Funcao para imprimir os significados na ordem em que foram inseridos na lista.
		void imprime(std::ostream& out){
			int i=1;
			Significado* iterator;
			for(iterator=this->getPrimeiro();iterator!=nullptr;iterator=iterator->prox_){
				if(iterator->significado_==""){
					continue;
				}
				out<<i++<<". "<<iterator->significado_<<std::endl;
			}
		}

};

/*Declaracao do verbete. Cada verbete possui uma lista encadeada de significados proprios*/
struct Verbete{
    char tipo_;
    std::string chave_;
    ListaSignificados<Significado> significados_;
	Verbete* prox_;
};


/*Declaracao de uma Lista encadeada de Verbetes herdada da classe Template ListaBase*/
template <typename T>
class ListaVerbetes : public ListaBase<T>{
	public:
		Verbete* Pesquisa(std::string chave, char tipo){
			Verbete *aux;
			aux = this->getPrimeiro();

			while(aux!=nullptr){
				if(aux->chave_==chave && aux->tipo_==tipo)
					return aux;
				
				aux=aux->prox_;
			}
			return nullptr;
		}
		


};

void atualizaSignificado(ListaSignificados<Significado> ls, Verbete* alvo);

#endif

