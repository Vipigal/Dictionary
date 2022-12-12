#include "Dicionario.hpp"


template <typename T>
class ListaVerbete : public ListaBase<T>{};

class HashDic : public Dicionario{
public:
	HashDic(int N) : Dicionario(N){
		tabela_ = new ListaVerbete<Verbete>[N];
		entradas_=0;
	}

	Verbete* pesquisa(std::string chave);
	void insereVerbete(Verbete* it);
	void imprime();
	void atualiza(Verbete* it);
	void removeVerbete(Verbete* it);

	int getEntradas() const {return entradas_;}

	~HashDic() {}

private:
	//Funcao geradora de hash por strings. Retorna um index da tabela.
	int Hash(std::string chave);
	int entradas_;
	ListaVerbete<Verbete>* tabela_;
};