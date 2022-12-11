#include "Dicionario.hpp"

struct No{
	Verbete* chave;
	No* prox;
};


class Lista{
	public:
		Lista(){
			primeiro_=nullptr;
			ultimo_=nullptr;
		}

		bool vazia(){
			return !tamanho_;
		}

		/*Procura a chave (verbete em si) na lista de verbetes e retorna seu conteudo.
			Se nao foi encontrado, retorna nullptr.*/
		Verbete* Pesquisa(std::string chave){
			Verbete *aux;
			aux = primeiro_;

			while(aux!=nullptr){
				if(aux->chave_==chave)
					return aux;
				
				aux=aux->prox_;
			}
			return nullptr;
		}

		void insereFinal(Verbete* it){
			if(it==nullptr)
				return;
			
			Verbete* novo;
			novo = it;
			novo->prox_=nullptr;

			if(vazia()){
				primeiro_=novo;
				ultimo_=novo;
				tamanho_++;
			}else{
				ultimo_->prox_ = novo;
				ultimo_=novo;
				tamanho_++;
			}
		}

		void remove(std::string chave){
			Verbete* iterator;
			iterator=primeiro_;
			//testa se o primeiro elemento eh o elemento a ser removido.
			//Se nao, comecamos a testar a partir do proximo elemento.
			if(primeiro_->chave_==chave){
				primeiro_=primeiro_->prox_;
				delete primeiro_;
				tamanho_--;
				return;
			}

			//posiciona o iterador na posicao anterior da chave
			while(iterator->prox_->chave_!=chave && iterator->prox_!=nullptr){
				iterator=iterator->prox_;
			}
			if(iterator->prox_==nullptr){
				throw("Erro: O verbete com a chave recebida nao esta presente no dicionario!");
			}
			Verbete* aux = iterator->prox_;
			iterator->prox_=aux->prox_;
			delete aux;
			tamanho_--;
			if(iterator->prox_==nullptr){
				ultimo_=iterator;
			}
		}



	private:
		Verbete* primeiro_;
		Verbete* ultimo_;
		int tamanho_;
};

class HashDic : public Dicionario{
public:
	HashDic(int N) : Dicionario(N){
		tabela_ = new Lista[N];
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
	Lista* tabela_;
};