#include "AVLDic.hpp"

int max(int a, int b){
	return (a>b)? a : b; 
}

int AVLDic::altura(No* no){
	if(no==nullptr)
		return 0;

	return 1 + max(altura(no->dir), altura(no->esq));
}

int AVLDic::FatorBalanceio(No* no){
	if(no==nullptr)
		return 0;
	int balanco=0;

	balanco = altura(no->dir) - altura(no->esq);

	return balanco;
}

No* AVLDic::rotacaoRR(No* pai){
	No* aux;

	aux = pai->dir;
	pai->dir = aux->esq;
	aux->esq = pai;
	std::cout << "rr rotation" << std::endl;
	return aux;
}

No* AVLDic::rotacaoLL(No* pai){
	// No* aux;

	// aux = pai->esq;
	// pai->esq = aux->dir;
	// aux->dir = pai;
	// std::cout << "ll rotation" << std::endl;

	No *x = pai->esq;
    No *T2 = x->dir;
    x->dir = pai;
    pai->esq = T2;
	return x;
}
//to do: testar se sem aux funciona


No* AVLDic::rotacaoRL(No* pai){
	No* aux;
	aux=pai->dir;
	pai->dir=rotacaoLL(aux);
	std::cout << "rl rotation" << std::endl;
	return rotacaoRR(pai); 
}

No* AVLDic::rotacaoLR(No* pai){
	No* aux;
	aux = pai->esq;
	pai->esq = rotacaoRR(aux);
	std::cout << "lr rotation" << std::endl;
	return rotacaoLL(pai); 
}

No* AVLDic::balanceia(No* no){
	no->altura_ = altura(no);
	int FB = FatorBalanceio(no);
	//testa se o No ta pesado pra direita ou esquerda
	if(FB > 1){
		//se tiver para a direita, testa se o filho da direita esta pesado para direita ou esquerda
		if(FatorBalanceio(no->dir)>=0){
			no = rotacaoRR(no);
		}
		//filho esta pesado para esquerda.
		else{
			no = rotacaoRL(no);
		}
	}
	//No esta pesado para a esquerda.
	else if(FB < -1){
		//testa se o filho da esquerda esta pesado para a direita ou para a esquerda.
		if(FatorBalanceio(no->esq) <= 0){
			no = rotacaoLL(no);
		}
		//Filho esta pesado para a direita.
		else{
			no = rotacaoLR(no);
		}
	}
	return no;
}
No* AVLDic::insere(No* no, Verbete* data){
	if(data == nullptr)
		throw std::range_error("ERRO: Nao eh possivel inserir um verbete vazio na arvore!");

	if(no==nullptr){
		No* novo = new No;
		novo->ver_=data;
		novo->dir=nullptr;
		novo->esq=nullptr;
		entradas_++;
		return novo;
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
	entradas_++;
	return no;
}

void AVLDic::inordem(No* no, std::ostream& out){
	if(no == nullptr)
		return;
	inordem(no->esq, out);
	out<<no->ver_->chave_<<"("<<no->ver_->tipo_<<")"<<std::endl;
	no->ver_->significados_.imprime(out);
	inordem(no->dir, out);
}
void AVLDic::insereVerbete(Verbete* it){
	if(it == nullptr)
		throw std::range_error("ERRO: Nao eh possivel inserir um verbete vazio no dicionario!");
	raiz = insere(raiz, it);
}

Verbete* AVLDic::pesquisaNo(No* no, std::string chave, char tipo){
	if(no==nullptr)
		return nullptr;
	else if(no->ver_->chave_==chave && no->ver_->tipo_==tipo){
		return no->ver_;
	}
	else if(no->ver_->chave_.compare(chave) < 0){
		Verbete* aux = pesquisaNo(no->dir,chave,tipo);
		return aux;
	}
	else{
		Verbete* aux = pesquisaNo(no->esq,chave,tipo);
		return aux;			
	}
}

Verbete* AVLDic::pesquisa(std::string chave, char tipo){
	return pesquisaNo(raiz, chave, tipo);
}

void AVLDic::imprime(std::ostream& out){

	inordem(raiz,out);
}
//funcao nao sera implementada pois esta imbutida na insere.
void AVLDic::atualiza(Verbete * it){}

No* AVLDic::deleta(No* no, std::string chave, char tipo){
	if (no == nullptr){
		return no;
	}
	No* aux;
	if(no->ver_->chave_.compare(chave) < 0){
		no->dir = deleta(no->dir, chave, tipo);
	}
	else if(no->ver_->chave_.compare(chave) > 0){
		no->esq = deleta(no->esq, chave, tipo);
	}
	//Testa se o no tem a chave e o tipo igual ao que se deve deletar.
	else if(no->ver_->chave_.compare(chave) == 0 && no->ver_->tipo_ == tipo){
		//No com um filho ou nenhum.
		if(no->dir == nullptr || no->dir == nullptr){
			aux = no->esq ? no->esq : no->dir;
			//Nao ha filhos
			if(aux == nullptr){
				aux = no;
				no = nullptr;
			}else{
				//ha um filho, copia o conteudo dele para o no.
				*no = *aux;
			}
			delete aux;
		}
		else{
			aux = menor(no->dir);
			no->ver_=aux->ver_;
			no->dir = deleta(no->dir, aux->ver_->chave_, aux->ver_->tipo_);
		}
	}
	if (no == nullptr){
		return no;
	}

	no=balanceia(no);
	return no;

}

void AVLDic::removeVerbete(std::string chave, char tipo){
	raiz = deleta(raiz, chave, tipo);
}

//Retorna o maior no da arvore.
No* AVLDic::maior(No* no){
	while(no->dir!=nullptr)
		no = no->dir;

	return no;
}
//Retorna o menor no da arvore.
No* AVLDic::menor(No* no){
	while(no->esq!=nullptr)
		no = no->esq;

	return no;
}

