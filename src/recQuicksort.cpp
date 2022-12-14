#include "recQuicksort.hpp"


void Particao(int Esq, int Dir, int *i, int *j, Verbete *A){
	Verbete x, w;
	*i = Esq; *j = Dir;
	x = A[(*i + *j)/2]; /* obtem o pivo x */
	do
	{
		while (x.chave_.compare(A[*i].chave_) > 0){
			(*i)++;
		}
		while (x.chave_.compare(A[*j].chave_) < 0){
			(*j)--;
		}
		if (*i <= *j){
			w = A[*i]; A[*i] = A[*j]; A[*j] = w;
			(*i)++; (*j)--;
		}
	} while (*i <= *j);
}

void Ordena(int Esq, int Dir, Verbete *A){
  	int i, j;
	Particao(Esq, Dir, &i, &j, A);
	if (Esq < j) Ordena(Esq, j, A);
	if (i < Dir) Ordena(i, Dir, A);
}

void recQuickSort(Verbete *A, int n){
	Ordena(0, n-1, A);
}


