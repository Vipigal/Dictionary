#include "AVLDic.hpp"

int max(int a, int b){
	return (a>b)? a : b; 
}

Tree::Tree(){
	raiz=nullptr;
	tamanho_=0;
}

int Tree::altura(No* no){
	if(no==nullptr)
		return 0;

	return 1 + max(altura(no->dir), altura(no->esq));
}

int Tree::FatorBalanceio(No* no){
	if(no==nullptr)
		return 0;

	int balanco = no->dir->altura_ - no->esq->altura_;
	return balanco;
}

No* Tree::rotacaoRR(No* pai){
	No* aux;

	aux = pai->dir;
	pai->dir = aux->esq;
	aux->esq = pai;
	std::cout << "rr rotation" << std::endl;
	return aux;
}

No* Tree::rotacaoLL(No* pai){
	No* aux;

	aux = pai->esq;
	pai->esq = aux->dir;
	aux->dir = pai;
	std::cout << "ll rotation" << std::endl;
	return aux;
}
//to do: testar se sem aux funciona


No* Tree::rotacaoRL(No* pai){
	pai->dir = rotacaoLL(pai->dir);
	std::cout << "rl rotation" << std::endl;
	return rotacaoRR(pai); 
}

No* Tree::rotacaoLR(No* pai){
	pai->esq = rotacaoRR(pai->esq);
	std::cout << "lr rotation" << std::endl;
	return rotacaoLL(pai); 
}

No* Tree::balanceia(No* no){
	int FB = FatorBalanceio(no);
	//testa se o No ta pesado pra direita ou esquerda
	if(FB > 1){
		//se tiver para a direita, testa se o filho da direita esta pesado para direita ou esquerda
		if(FatorBalanceio(no->dir)>0){
			no = rotacaoRR(no);
		}
		//filho esta pesado para esquerda.
		else{
			no = rotacaoRL(no);
		}
	}
	//No esta pesado para a esquerda.
	else{
		//testa se o filho da esquerda esta pesado para a direita ou para a esquerda.
		if(FatorBalanceio(no->esq) < -1){
			no = rotacaoLL(no);
		}
		//Filho esta pesado para a direita.
		else{
			no = rotacaoLR(no);
		}
	}
	return no;
}
No* Tree::insere(No* no, Verbete* data){
	if(data == nullptr)
		throw std::range_error("ERRO: Nao eh possivel inserir um verbete vazio na arvore!");

	if(no==nullptr){
		No* novo = new No;
		no->ver_=data;
		no->dir=nullptr;
		no->esq=nullptr;
		return no;
	}
	//se valor < 0, No deve vir antes no dicionario do que data.
	else if(data->chave_.compare(no->ver_->chave_) < 0){
		no->esq = insere(no->esq, data);
		no = balanceia(no);
	}
	//se valor > 0, No deve vir depois no dicionario do que data.
	else if(data->chave_.compare(no->ver_->chave_) > 0){
		no->dir = insere(no->dir, data);
		no = balanceia(no);
	}
	else if(data->chave_.compare(no->ver_->chave_) == 0){
		if(data->tipo_ > no->ver_->tipo_){
			//insere a direita do no
			no->dir = insere(no->dir, data);
			no = balanceia(no);
		}else if (data->tipo_ < no->ver_->tipo_){
			//insere a esquerda do no
			no->esq = insere(no->esq, data);
			no = balanceia(no);
		}else{
			//atualiza significado do no
			atualizaSignificado(data->significados_, no->ver_);
		}
	}
}

