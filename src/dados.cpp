#include "dados.hpp"

void atualizaSignificado(ListaSignificados<Significado> ls, Verbete* alvo){
	Significado* iterador;
	//funcao insere significado
	for(iterador=ls.getPrimeiro();iterador!=nullptr;iterador=iterador->prox_){
		alvo->significados_.insereFinal(iterador);
	}
}
