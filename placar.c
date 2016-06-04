#include "placar.h"
#include "stdio.h"
#include "parametros.h"
#include "stdlib.h"
#include "string.h"

/**
*   Função responsável por inicializar os parâmetros da lista de pontuações
*/


void inicializaListaPlacar(LISTA_PONTUACAO *listaPontuacao){

	//Inicialização dos parâmetros da lista
	listaPontuacao->qtdPontuacoes = 0;
	listaPontuacao->primeiraPontuacao = NULL;
	listaPontuacao->pontuacaoAtual = NULL;
	listaPontuacao->ultimaPontuacao= NULL;

}


void adicionaListaPontuacao(LISTA_PONTUACAO *listaPontuacao, PONTUACAO *pontuacao){
	if (listaPontuacao->primeiraPontuacao == NULL){

		pontuacao->proximo = NULL;
		pontuacao->anterior = NULL;

		listaPontuacao->primeiraPontuacao = pontuacao;
		listaPontuacao->ultimaPontuacao = pontuacao;
		listaPontuacao->pontuacaoAtual = pontuacao;


	}else{
		listaPontuacao->ultimaPontuacao->proximo = pontuacao;
		pontuacao->anterior = listaPontuacao->ultimaPontuacao;
		listaPontuacao->ultimaPontuacao = pontuacao;

	}
	listaPontuacao->qtdPontuacoes++;
}


/**
* Função responsável por carregar, do arquivo cujo nome está em "parametros.h", as pontuacoes anteriores
*
*/


LISTA_PONTUACAO *carrega_placar(){
	char nome[5];
	int pontos;
	char data[8];
	int tempo;


	FILE *parquivo;
	LISTA_PONTUACAO *listaPontuacao = malloc(sizeof(LISTA_PONTUACAO));
	inicializaListaPlacar(listaPontuacao);

	parquivo = fopen(ARQUIVO_PLACAR,"r");
	if (!parquivo){
		return FALSO;
	}

	while (fscanf(parquivo,"%s %d %s %d",nome, &pontos, data, &tempo) != EOF){
		   PONTUACAO *pontuacao = malloc(sizeof(PONTUACAO));
		   strcpy(pontuacao->nome,nome);
		   pontuacao->pontos = pontos;
		   strcpy(pontuacao->data,data);
		   pontuacao->tempo = tempo;
		   adicionaListaPontuacao(listaPontuacao,pontuacao);

	}
	fclose(parquivo);
	return listaPontuacao;
}





void atualiza_placar( char nome[], int pontuacao ){
	
	LISTA_PONTUACAO *listaPontuacao;
	listaPontuacao = carrega_placar();




}
void mostra_placar(){

}

void main(){

	carrega_placar();

}
