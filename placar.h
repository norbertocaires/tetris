#ifndef _placar_h
#define _placar_h

#include "parametros.h"

/** Struct que modela as pontuações*/
struct pontuacao{
    
	char nome[TAM_NOME];
	int pontos;
	char data[8];
	int tempo;
	struct pontuacao *proximo;
	struct pontuacao *anterior;

};
typedef struct pontuacao PONTUACAO;

/** Struct que modela a lista com as pontuações gravadas em arquivo */
struct listaPontuacao{

	int qtdPontuacoes;

	struct pontuacao *primeiraPontuacao;
	struct pontuacao *pontuacaoAtual;
	struct pontuacao *ultimaPontuacao;


}; typedef struct listaPontuacao LISTA_PONTUACAO;


void inicializaListaPlacar(LISTA_PONTUACAO *listaPontuacao);
LISTA_PONTUACAO *carrega_placar();
void atualiza_placar( char nome[], int pontuacao );
void mostra_placar();   


#endif
