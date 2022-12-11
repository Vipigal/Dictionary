#include "Dicionario.hpp"

struct No{
    int chave;
    No* prox;
};

class Lista{
    public:

    private:
        int tamanho;

};

class HashDic : public Dicionario{
    public:
        int pesquisa(Verbete * it);
        int insere(Verbete * it)=0;
        void imprime()=0;
        int atualiza(Verbete * it)=0;
        int remove(Verbete * it)=0;
    private:
        int Hash(Verbete *it){
            -
        }
};