#ifndef _placar_h
#define _placar_h

#include "parametros.h"

/** Struct que modela as pontuações*/
struct pontuacao{
    
	char nome[TAM_NOME]; /**< representa o nome do jogador que fez a pontuacao*/
	int pontos; /**< representa quantos pontos o jogador fez*/
	char data[100]; /**< representa a data em que o jogador fez a pontuacao*/
	char tempo[100]; /**< representa o tempo que o jogador permaneceu em jogo para fazer a pontuacao*/
	struct pontuacao *proximo; /**< representa o próximo nó em uma lista de pontuações*/
	struct pontuacao *anterior; /**< representa o nó anterior, em uma lista de pontuações*/

};
typedef struct pontuacao PONTUACAO;

/** Struct que modela a lista com as pontuações gravadas em arquivo */
struct lista_pontuacao{

	int qtd_pontuacoes; /**< representa quantas pontuações estão armazenadas na lista de pontuações*/
 
	struct pontuacao *primeira_pontuacao; /**< ponteiro que aponta para o primeiro nó da lista de pontuações*/
	struct pontuacao *pontuacao_atual; /**< ponteiro que aponta para um dos nós da lista. Utilizado em iterações sobre a lista*/
	struct pontuacao *ultima_pontuacao;/**< aponta para o último nó da lista*/


}; typedef struct lista_pontuacao LISTA_PONTUACAO;


void inicializa_lista_placar(LISTA_PONTUACAO *lista_pontuacao);
LISTA_PONTUACAO *carrega_placar(int debug);  
void retira_ultima_pontuacao(LISTA_PONTUACAO *lista_pontuacao);
void adiciona_lista_pontuacao(LISTA_PONTUACAO *lista_pontuacao,PONTUACAO *pontuacao);
char *data();
char *format(int number);
void escreve_placar(LISTA_PONTUACAO *lista_pontuacao);

#endif
