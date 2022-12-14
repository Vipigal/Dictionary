#ifndef DICIONARIO_H
#define DICIONARIO_H

#include "dados.hpp"
#include "recQuicksort.hpp"

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
        virtual void imprime(std::ostream& out)=0;
        virtual void atualiza(Verbete * it)=0;
        virtual void removeVerbete(Verbete * it)=0;
        virtual ~Dicionario(){};

    private:
		int tamanho_;
};


#endif