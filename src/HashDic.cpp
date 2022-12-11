#include "HashDic.hpp"

int HashDic::Hash(std::string chave){
	int hash = 0;
	int tam = chave.length();
	for (int i = 0; i < tam; i++){
		hash += chave[i] * (i + 1);
	}
	return hash % getTamanho();
}

Verbete* HashDic::pesquisa(std::string chave){
	int index=Hash(chave);
	Verbete* alvo = tabela_[index].Pesquisa(chave);
	//Se encontado o item, o retorna
	if(alvo!=nullptr){
		return alvo;
	}
	return nullptr;
}

void HashDic::insereVerbete(Verbete* it){
	int index=Hash(it->chave_);
	if(tabela_[index].Pesquisa(it->chave_)!=nullptr){
		throw("O Verbete ja esta presente no dicionario. Se quiser adicionar um significado, utilize a funcao InsereSignificado!");
	}
	tabela_[index].insereFinal(it);
	entradas_++;
}

void HashDic::removeVerbete(Verbete* it){
	int index = Hash(it->chave_);
	tabela_[index].remove(it->chave_);
	entradas_--;
}

// void HashDic::imprime(){

// }

