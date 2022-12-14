#include <iostream>
#include <string>

using namespace std;

class Significado
{
public:
    string significado;
    Significado *proximo;
};

class Verbete
{
public:
    string palavra;
    string tipo;
    Significado *significadoEsq;
    Significado *significadoDir;
    int significados;
    Verbete *Esq;
    Verbete *Dir;
    int altura;
};

int max(int a, int b);

// Calcula altura
int Altura(Verbete *N)
{
    if (N == NULL)
        return 0;
    return N->altura;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

Significado *novoSignificado(string significado)
{
    Significado *aux = new Significado{significado, NULL};
    return aux;
}

// Cria novo verbete
Verbete *novoVerbete(string palavra, string tipo)
{
    Verbete *verbete = new Verbete();
    verbete->palavra = palavra;
    verbete->Esq = NULL;
    verbete->Dir = NULL;
    verbete->altura = 1;
    verbete->tipo = tipo;
    verbete->significadoEsq = NULL;
    verbete->significadoDir = NULL;
    verbete->significados = 0;
    return (verbete);
}

// Rotaciona a direita
Verbete *rotacaoDireita(Verbete *y)
{
    Verbete *x = y->Esq;
    Verbete *T2 = x->Dir;
    x->Dir = y;
    y->Esq = T2;
    y->altura = max(Altura(y->Esq),
                    Altura(y->Dir)) +
                1;
    x->altura = max(Altura(x->Esq),
                    Altura(x->Dir)) +
                1;
    return x;
}

// Rotaciona a esquerda
Verbete *rotacaoEsquerda(Verbete *x)
{
    Verbete *y = x->Dir;
    Verbete *T2 = y->Esq;
    y->Esq = x;
    x->Dir = T2;
    x->altura = max(Altura(x->Esq),
                    Altura(x->Dir)) +
                1;
    y->altura = max(Altura(y->Esq),
                    Altura(y->Dir)) +
                1;
    return y;
}

// Obtem o fator de balanceamento do verbete de entrada
int fatorBalanco(Verbete *N)
{
    if (N == NULL)
        return 0;
    return Altura(N->Esq) -
           Altura(N->Dir);
}

// Insere um verbete
Verbete *insereDic(Verbete *verbete, string palavra, string tipo)
{
    // Encontra a posicao correta e insere o verbete
    if (verbete == NULL)
        return (novoVerbete(palavra, tipo));
    else if (verbete->palavra == palavra)
        return verbete;
    if (palavra < verbete->palavra)
        verbete->Esq = insereDic(verbete->Esq, palavra, tipo);
    else if (palavra > verbete->palavra)
        verbete->Dir = insereDic(verbete->Dir, palavra, tipo);
    else
        return verbete;

    // Atualiza o fator de balanceamento de cada verbete e balanceia a arvore
    verbete->altura = 1 + max(Altura(verbete->Esq),
                              Altura(verbete->Dir));
    int balanco = fatorBalanco(verbete);
    if (balanco > 1)
    {
        if (palavra < verbete->Esq->palavra)
        {
            return rotacaoDireita(verbete);
        }
        else if (palavra > verbete->Esq->palavra)
        {
            verbete->Esq = rotacaoEsquerda(verbete->Esq);
            return rotacaoDireita(verbete);
        }
    }
    if (balanco < -1)
    {
        if (palavra > verbete->Dir->palavra)
        {
            return rotacaoEsquerda(verbete);
        }
        else if (palavra < verbete->Dir->palavra)
        {
            verbete->Dir = rotacaoDireita(verbete->Dir);
            return rotacaoEsquerda(verbete);
        }
    }
    return verbete;
}

// Verbete com valor minimo
Verbete *Minimo(Verbete *verbete)
{
    Verbete *current = verbete;
    while (current->Esq != NULL)
        current = current->Esq;
    return current;
}

// Apaga um verbete
Verbete *removeDic(Verbete *raiz, string palavra)
{
    // Encontra o verbete e o apaga
    if (raiz == NULL)
        return raiz;
    if (palavra < raiz->palavra)
        raiz->Esq = removeDic(raiz->Esq, palavra);
    else if (palavra > raiz->palavra)
        raiz->Dir = removeDic(raiz->Dir, palavra);
    else
    {
        if ((raiz->Esq == NULL) ||
            (raiz->Dir == NULL))
        {
            Verbete *temp = raiz->Esq ? raiz->Esq : raiz->Dir;
            if (temp == NULL)
            {
                temp = raiz;
                raiz = NULL;
            }
            else
                *raiz = *temp;
            free(temp);
        }
        else
        {
            Verbete *temp = Minimo(raiz->Dir);
            raiz->palavra = temp->palavra;
            raiz->Dir = removeDic(raiz->Dir,
                                  temp->palavra);
        }
    }

    if (raiz == NULL)
        return raiz;

    // Atualiza o fator de balanceamento de cada verbete e balanceia a arvore
    raiz->altura = 1 + max(Altura(raiz->Esq),
                           Altura(raiz->Dir));
    int balanco = fatorBalanco(raiz);
    if (balanco > 1)
    {
        if (fatorBalanco(raiz->Esq) >= 0)
        {
            return rotacaoDireita(raiz);
        }
        else
        {
            raiz->Esq = rotacaoEsquerda(raiz->Esq);
            return rotacaoDireita(raiz);
        }
    }
    if (balanco < -1)
    {
        if (fatorBalanco(raiz->Dir) <= 0)
        {
            return rotacaoEsquerda(raiz);
        }
        else
        {
            raiz->Dir = rotacaoDireita(raiz->Dir);
            return rotacaoEsquerda(raiz);
        }
    }
    return raiz;
}

Verbete *pesquisaDic(Verbete *raiz, string palavra)
{
    if (raiz == NULL)
        return 0;

    else if (raiz->palavra == palavra)
        return raiz;

    else if (palavra < raiz->palavra)
        return pesquisaDic(raiz->Esq, palavra);

    return pesquisaDic(raiz->Dir, palavra);
}

Verbete *atualizaDic(Verbete *raiz, string palavra, string significado)
{
    Verbete *aux = pesquisaDic(raiz, palavra);

    if (aux->significadoEsq == NULL)
    {
        aux->significadoEsq = novoSignificado(significado);
        aux->significadoDir = aux->significadoEsq;
        aux->significados += 1;
    }

    else
    {
        aux->significadoDir->proximo = novoSignificado(significado);
        aux->significadoDir = aux->significadoDir->proximo;
        aux->significados += 1;
    }

    return aux;
}

// Print the tree
void imprimeArvore(Verbete *raiz, string identacao, bool ultimo)
{
    if (raiz != nullptr)
    {
        cout << identacao;
        if (ultimo)
        {
            cout << "R----";
            identacao += "   ";
        }
        else
        {
            cout << "L----";
            identacao += "|  ";
        }

        cout << raiz->tipo << " ";
        cout << raiz->palavra << " ";
        while (raiz->significadoEsq != NULL)
        {
            cout << raiz->significadoEsq->significado << " / ";
            raiz->significadoEsq = raiz->significadoEsq->proximo;
        }

        cout << endl;

        imprimeArvore(raiz->Esq, identacao, false);
        imprimeArvore(raiz->Dir, identacao, true);
    }
}

void imprimeDic(Verbete *raiz)
{
    if (raiz == NULL)
        return;

    imprimeDic(raiz->Esq);

    cout << raiz->palavra << endl;

    imprimeDic(raiz->Dir);
}

int main(int argc, char *argv[])
{
    Verbete *raiz = NULL;
    raiz = insereDic(raiz, "[bad]", "a");
    raiz = atualizaDic(raiz, "[bad]", "evil");
    raiz = insereDic(raiz, "[bad]", "a");
    raiz = atualizaDic(raiz, "[bad]", "not goot, worse");
    raiz = insereDic(raiz, "[artistic]", "a");
    raiz = insereDic(raiz, "[ashamed]", "a");
    raiz = insereDic(raiz, "[asleep]", "a");
    raiz = insereDic(raiz, "[applied]", "a");
    raiz = insereDic(raiz, "[car]", "n");

    // raiz = insereDic(raiz, 61);
    // raiz = insereDic(raiz, 8);
    // raiz = insereDic(raiz, 11);
    imprimeArvore(raiz, "", true);
    imprimeDic(raiz);
    // imprimeArvore(raiz, "", true);
    // raiz = removeDic(raiz, 13);
    // cout << "After deleting " << endl;
    // imprimeDic(raiz, "", true);
    return 0;
}