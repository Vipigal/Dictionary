#ifndef AVLDIC_H
#define AVLDIC_H

#include <iostream>
#include "Dicionario.hpp"

//Retorna o max entre a e b.
int max(int a, int b);

//Declaracao de um No da arvore.
struct No{
	Verbete* ver_;
	No* esq;
	No* dir;
	int altura_;
};

//Dicionario implementado com uma arvore AVL.
class AVLDic : public Dicionario{
	public:
	//Cria uma instancia de arvore AVL. 
	AVLDic(int N) : Dicionario(N){
		raiz = nullptr;
		entradas_=0;
	};
	//Retorna o numero de entradas presentes na arvore.
	int getEntradas() const {return entradas_;}
	//Retorna a altura do no.
	int altura(No* no);
	/*Retorna o fator de balanceio do no. 
	A arvore eh right-heavy. Direita tem mais peso do que a esquerda.*/
	int FatorBalanceio(No* no);
	//RotacaoRR = Rotacao simples a esquerda.
	No* rotacaoRR(No* pai);
	//Rotacao LL = Rotacao simples a direita
	No* rotacaoLL(No* pai);
	//Rotacao RL = rotacao do filho da direita a direita e depois do pai a esquerda.
	No* rotacaoRL(No* pai);
	//Rotacao LR = rotacao do filho da esquerda a esquerda e depois do pai a direita.
	No* rotacaoLR(No* pai);
	//Balanceia um No. Testa o proprio FB e o dos filhos e realiza as rotacoes necessarias.
	No* balanceia(No* no);
	//Insere o conteudo do verbete data no No recebido recursivamente.
	No* insere(No* no, Verbete* data);
	//Retorna o maior no da arvore.
	No* maior(No* no);
	//Retorna o menor no da arvore.
	No* menor(No* no);
	//Deleta um no de acordo com sua chave e seu tipo.
	No* deleta(No* no, std::string chave, char tipo);
	//Imprime a arvore de maneira inordem.
	void inordem(No* no, std::ostream& out);
	//Pesquisa um verbete na arvore e o retorna.
	Verbete* pesquisaNo(No* no, std::string chave, char tipo);

	//funcoes da interface dicionario:

	//Insere um verbete na arvore.
	void insereVerbete(Verbete* it);
	//Pesquisa um verbete na arvore e o retorna.
	Verbete* pesquisa(std::string chave, char tipo);
	//Imprime a arvore de maneira inOrdem.
    void imprime(std::ostream& out);
	//Atualiza a arvore.
    void atualiza(Verbete * it);
	//Remove um verbete da arvore.
    void removeVerbete(std::string chave, char tipo);
	//todo implementar ~tree
	~AVLDic(){}

	private:
		No* raiz;
		int entradas_;

};

#endif