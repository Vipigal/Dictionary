#include <string>

struct Verbete{
    char tipo;
    std::string chave;
    std::string *significados=nullptr;
};

class Dicionario{
    public:
        Dicionario(int N){
            entradas = new Verbete[N];
        }
        virtual int pesquisa(Verbete * it)=0;
        virtual int insere(Verbete * it)=0;
        virtual void imprime()=0;
        virtual int atualiza(Verbete * it)=0;
        virtual int remove(Verbete * it)=0;

        virtual ~Dicionario()=0;

    private:
        Verbete* entradas;

};