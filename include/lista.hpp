#ifndef LISTA_H
#define LISTA_H

#include <string>

template <class T>
class ListaBase{
	public:
		ListaBase(){
			primeiro_=nullptr;
			ultimo_=nullptr;
			tamanho_=0;
		}

		bool vazia(){
			return !tamanho_;
		}

		T* getPrimeiro() const {return primeiro_;}

		/*Procura a chave na lista e retorna seu conteudo.
			Se nao foi encontrado, retorna nullptr.*/
		T* Pesquisa(std::string chave){
			T *aux;
			aux = primeiro_;

			while(aux!=nullptr){
				if(aux->chave_==chave)
					return aux;
				
				aux=aux->prox_;
			}
			return nullptr;
		}

		//Insere o objeto no final da lista.
		//Se a lista esta vazia, ele eh inserido como o primeiro elemento.
		void insereFinal(T* it){
			if(it==nullptr)
				return;
			
			T* novo;
			novo = it;
			novo->prox_=nullptr;

			if(this->vazia()){
				primeiro_=novo;
				ultimo_=novo;
				tamanho_++;
			}else{
				ultimo_->prox_ = novo;
				ultimo_=novo;
				tamanho_++;
			}
		}

		//remove um elemento pela sua chave.
		void remove(std::string chave, char tipo){
			T* iterator;
			iterator=primeiro_;
			//testa se o primeiro elemento eh o elemento a ser removido.
			//Se nao, comecamos a testar a partir do proximo elemento.
			if(primeiro_->chave_==chave && primeiro_->tipo_==tipo){
				T* aux = primeiro_;
				primeiro_=primeiro_->prox_;
				delete aux;
				tamanho_--;
				return;
			}

			//posiciona o iterador na posicao anterior da chave
			while(iterator->prox_->chave_!=chave&& iterator->prox_!=nullptr){
				iterator=iterator->prox_;
			}
			if(iterator->prox_->chave_==chave&&iterator->prox_->tipo_!=tipo){
				iterator=iterator->prox_;
			}
			if(iterator->prox_==nullptr){
				throw("Erro: O verbete com a chave recebida nao esta presente no dicionario!");
			}
			T* aux = iterator->prox_;
			iterator->prox_=aux->prox_;
			delete aux;
			tamanho_--;
			if(iterator->prox_==nullptr){
				ultimo_=iterator;
			}
		}

		void removeTudo(){
			T* iterator = primeiro_;
			while(iterator!=nullptr){
				T* aux=iterator->prox_;
				delete iterator;
				iterator=aux;
				tamanho_--;
			}
		}

		~ListaBase(){
			// removeTudo();
		}


	//ATENCAO: O TIPO T DEVE TER UM ATRIBUTO T* PROX_ !!!!
	private:
		T* primeiro_;
		T* ultimo_;
		int tamanho_;
};



#endif