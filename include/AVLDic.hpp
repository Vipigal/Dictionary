#ifndef AVLDIC_H
#define AVLDIC_H

#include <iostream>
#include "Dicionario.hpp"

int max(int a, int b){
	return (a>b)? a : b; 
}

struct No{
	Verbete* ver_;
	No* esq;
	No* dir;
	int altura_;
};

class Tree{
	public:
	//Cria uma instancia de arvore AVL. 
	Tree();
	//Retorna a altura do no.
	int altura(No* no);
	//Retorna o fator de balanceio do no.
	//A arvore eh right-heavy. Direita tem mais peso do que a esquerda.
	int FatorBalanceio(No* no);
	//RotacaoRR = Rotacao simples a esquerda.
	No* rotacaoRR(No* pai);
	//Rotacao LL = Rotacao simples a direita
	No* rotacaoLL(No* pai);
	//to do: testar se sem aux funciona

	//Rotacao RL = rotacao do filho da direita a direita e depois do pai a esquerda.
	No* rotacaoRL(No* pai);
	//Rotacao LR = rotacao do filho da esquerda a esquerda e depois do pai a direita.
	No* rotacaoLR(No* pai);
	//Balanceia um No. Testa o proprio FB e o dos filhos e realiza as rotacoes necessarias.
	No* balanceia(No* no);
	//Insere o conteudo do verbete data no No recebido recursivamente.
	No* insere(No* no, Verbete* data);
	//todo implementar ~tree
	~Tree(){}

	private:
		No* raiz;
		int tamanho_;

};

#endif