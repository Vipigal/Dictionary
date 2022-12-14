#include "HashDic.hpp"


#define TROCA(A,B){Verbete C=A;A=B;B=C;}

int HashDic::Hash(std::string chave){
	int hash = 0;
	int tam = chave.length();
	for (int i = 0; i < tam; i++){
		hash += chave[i] * (i + 1);
	}
	return hash % getTamanho();
}

//Pesquisa o verbete pela sua chave na tabela.
//Se encontrado, retorna o verbete. Se nao, retorna nullptr.
Verbete* HashDic::pesquisa(std::string chave, char tipo){
	int index=Hash(chave);
	Verbete* alvo = tabela_[index].Pesquisa(chave, tipo);
	//Se encontado o item, o retorna
	if(alvo!=nullptr){
		return alvo;
	}
	return nullptr;
}

void HashDic::insereVerbete(Verbete* it){
	int index=Hash(it->chave_);
	Verbete* alvo=tabela_[index].Pesquisa(it->chave_, it->tipo_);
	if(alvo!=nullptr && it->tipo_ == alvo->tipo_){
		throw std::range_error("Erro: O Verbete ja esta presente no dicionario. Se quiser adicionar um significado, utilize a funcao atualiza()!");
	}
	tabela_[index].insereFinal(it);
	entradas_++;
}

void HashDic::removeVerbete(Verbete* it){
	int index = Hash(it->chave_);
	tabela_[index].remove(it->chave_);
	entradas_--;
}

Verbete* HashDic::hashParaVetor() const {
	Verbete* p;
	int j=0;
	int numeroEntradas = getEntradas();
	Verbete* vetor = new Verbete[numeroEntradas];

	for(int i=0;i<getTamanho();i++){
		for(p=tabela_[i].getPrimeiro();p!=nullptr;p=p->prox_){
			vetor[j++] = *p;
		}
	}

	return vetor;
}


void HashDic::imprime(std::ostream& out){
	Verbete* vetorHash = hashParaVetor();
	int numeroEntradas=getEntradas();
	
	recQuickSort(vetorHash,numeroEntradas);

	for(int i=0;i<numeroEntradas;i++){
		if(i+1<=numeroEntradas&&vetorHash[i].chave_==vetorHash[i+1].chave_){
			if(vetorHash[i].tipo_>vetorHash[i+1].tipo_){
				TROCA(vetorHash[i],vetorHash[i+1]);
			}
		}
		out<<vetorHash[i].chave_<<"("<<vetorHash[i].tipo_<<")"<<std::endl;
		vetorHash[i].significados_.imprime(out);
	}
}

void HashDic::atualiza(Verbete* it){
	int index=Hash(it->chave_);
	Verbete* alvo=tabela_[index].Pesquisa(it->chave_,it->tipo_);
	if(alvo==nullptr){
		throw std::range_error("Erro: O Verbete nao esta presente no dicionario. Voce so pode atualizar campos de um verbete existente!");
	}
	//se nao, atualizar o significado do verbete.
	atualizaSignificado(it->significados_, alvo);
}

HashDic::~HashDic(){
		Verbete *temp, *iterador;
		
		for(int i=0;i<getTamanho();i++){
			iterador=tabela_[i].getPrimeiro();
			temp=iterador;
			while(iterador!=nullptr){
				iterador=iterador->prox_;
				delete temp;
				temp=iterador;
			}

		}
	}
