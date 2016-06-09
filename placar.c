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
	
	pontuacao->proximo = NULL;
	pontuacao->anterior = NULL;

	if (listaPontuacao->primeiraPontuacao == NULL ){//Caso de a lista estar vazia
		listaPontuacao->primeiraPontuacao = pontuacao;
	}else if(pontuacao->pontos > listaPontuacao->primeiraPontuacao->pontos){

		listaPontuacao->primeiraPontuacao->anterior = pontuacao;
		pontuacao->proximo = listaPontuacao->primeiraPontuacao;
		listaPontuacao->primeiraPontuacao = pontuacao;
		
	}else{ 
		//Laço que posiciona o ponteiro pontuacaoAtual uma posicao antes do local onde a nova posicao será inserida
		while(listaPontuacao->pontuacaoAtual->pontos > pontuacao->pontos 
		&& listaPontuacao->pontuacaoAtual->proximo != NULL && listaPontuacao->pontuacaoAtual->proximo->pontos > pontuacao->pontos){	
				listaPontuacao->pontuacaoAtual = listaPontuacao->pontuacaoAtual->proximo;	
		}
		pontuacao->anterior = listaPontuacao->pontuacaoAtual;
		pontuacao->proximo = listaPontuacao->pontuacaoAtual->proximo;
		listaPontuacao->pontuacaoAtual->proximo = pontuacao;
		if(pontuacao->proximo != NULL){
			pontuacao->proximo->anterior = pontuacao;
		}

	}

	listaPontuacao->qtdPontuacoes++;
	listaPontuacao->pontuacaoAtual = listaPontuacao->primeiraPontuacao;
	if(listaPontuacao->qtdPontuacoes > 5)
		retiraUltimaPontuacao(listaPontuacao);

	
}


void retiraUltimaPontuacao(LISTA_PONTUACAO *listaPontuacao){

	while(listaPontuacao->pontuacaoAtual->proximo != NULL){
		listaPontuacao->pontuacaoAtual = listaPontuacao->pontuacaoAtual->proximo;
	}

	free(listaPontuacao->pontuacaoAtual);
	listaPontuacao->pontuacaoAtual = listaPontuacao->primeiraPontuacao;

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
		return NULL;
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


void mostra_placar(LISTA_PONTUACAO *listaPontuacao){
	listaPontuacao->pontuacaoAtual = listaPontuacao->primeiraPontuacao;
	while(listaPontuacao->pontuacaoAtual->proximo != NULL){
		printf("\n\nNome: %s pontuacao: %d\n\n", listaPontuacao->pontuacaoAtual->nome,listaPontuacao->pontuacaoAtual->pontos);
		listaPontuacao->pontuacaoAtual = listaPontuacao->pontuacaoAtual->proximo;
	}

}