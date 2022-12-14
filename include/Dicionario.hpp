#ifndef DICIONARIO_H
#define DICIONARIO_H

#include <iostream>
#include <string>
#include "lista.hpp"

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
		void imprime(){
			int i=1;
			Significado* iterator;
			for(iterator=this->getPrimeiro();iterator!=nullptr;iterator=iterator->prox_){
				if(iterator->significado_==""){
					continue;
				}
				std::cout<<i++<<". "<<iterator->significado_<<std::endl;
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


/*Declaracao da classe abstrata Dicionario que implementa uma interface para a criacao dos dicionarios*/
class Dicionario{
    public:
        Dicionario(int N){
			tamanho_=N;
        }
		int getTamanho() const {return tamanho_;}
		//funcoes virtuais puras:
        virtual Verbete* pesquisa(std::string chave, char tipo)=0;
        virtual void insereVerbete(Verbete * it)=0;
        virtual void imprime()=0;
        virtual void atualiza(Verbete * it)=0;
        virtual void removeVerbete(Verbete * it)=0;
        virtual ~Dicionario(){};

    private:
		int tamanho_;
};


#endif