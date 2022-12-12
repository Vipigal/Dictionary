#include <string>

//Implementacao de uma lista encadeada base para ser instanciada com tipos diversos.
template <typename T>
class ListaBase{
	public:
		ListaBase(){
			primeiro_=nullptr;
			ultimo_=nullptr;
		}

		bool vazia(){
			return !tamanho_;
		}

		/*Procura a chave (verbete em si) na lista de verbetes e retorna seu conteudo.
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

		void insereFinal(T* it){
			if(it==nullptr)
				return;
			
			T* novo;
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
			T* iterator;
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
			T* aux = iterator->prox_;
			iterator->prox_=aux->prox_;
			delete aux;
			tamanho_--;
			if(iterator->prox_==nullptr){
				ultimo_=iterator;
			}
		}

	private:
		T* primeiro_;
		T* ultimo_;
		int tamanho_;
};

struct Verbete{
    char tipo_;
    std::string chave_;
    std::string *significados_=nullptr; //TODO: IMPLEMENTAR TAD PARA SIGNIFICADOS
	Verbete* prox_;
};

class Dicionario{
    public:
        Dicionario(int N){
			tamanho_=N;
        }

        virtual Verbete* pesquisa(std::string chave)=0;
        virtual void insereVerbete(Verbete * it)=0;
        // virtual void imprime()=0;
        // virtual void atualiza(Verbete * it)=0;
        virtual void removeVerbete(Verbete * it)=0;

		int getTamanho() const {return tamanho_;}

        // virtual ~Dicionario()=0;

    private:
		int tamanho_;

};