#ifndef QUICKSORT_REC
#define QUICKSORT_REC

#include <string>
#include "Dicionario.hpp"


void Particao(int Esq, int Dir, int *i, int *j, Verbete *A);
void Ordena(int Esq, int Dir, Verbete *A);
/*Realiza o procedimento de quicksort padrao com recusividade: */
void recQuickSort(Verbete *A, int n);




#endif