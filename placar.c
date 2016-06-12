#include <time.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "placar.h"
#include "parametros.h"
#include "string.h"



char *format(int number){      
   char    *retorno,
      ret[100];

   if (number < 10){
      sprintf(ret,"0%d",number);
      retorno = ret;
      return retorno;
   }
   else{
      sprintf(ret,"%d",number);
      retorno = ret;
      return retorno;
   }
}      

// funcao que retorna data
char *data(void){
   int dia,mes,ano;
   char   strDia[100], strMes[100], strAno[100], strData[100],*dataPtr;
   struct tm *local;
   time_t t;

   t = time(NULL);
   local = localtime(&t);

   dia = local->tm_mday;
   mes = local->tm_mon + 1;
   ano = local->tm_year + 1900;

   // por algum motivo precisa converter os valores retornados pelos ponteiros
   // da funcao em variaveis do tipo char      
   sprintf(strDia,"%s",format(dia));
   sprintf(strMes,"%s",format(mes));
   sprintf(strAno,"%s",format(ano));

   // cria a variavel de retorno dos dados e cria um ponteiro para essa variavel      
   sprintf(strData,"%s/%s/%s",strDia,strMes,strAno);
   
   // retorna data no formato dd:MM:yyyy com um ponteiro
   dataPtr = strData;
   return dataPtr;
}




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

		while(listaPontuacao->pontuacaoAtual->proximo != NULL){
			listaPontuacao->pontuacaoAtual = listaPontuacao->pontuacaoAtual->proximo;
		}
		listaPontuacao->ultimaPontuacao = listaPontuacao->pontuacaoAtual;
		listaPontuacao->pontuacaoAtual = listaPontuacao->primeiraPontuacao;		

	}

	listaPontuacao->qtdPontuacoes++;
	listaPontuacao->pontuacaoAtual = listaPontuacao->primeiraPontuacao;
	if(listaPontuacao->qtdPontuacoes > 5){
		retiraUltimaPontuacao(listaPontuacao);
	}

	
}


void retiraUltimaPontuacao(LISTA_PONTUACAO *listaPontuacao){
	listaPontuacao->pontuacaoAtual = listaPontuacao->primeiraPontuacao;
	while(listaPontuacao->pontuacaoAtual->proximo != NULL){
		listaPontuacao->pontuacaoAtual = listaPontuacao->pontuacaoAtual->proximo;
	}

	listaPontuacao->pontuacaoAtual->anterior->proximo = NULL;
	listaPontuacao->ultimaPontuacao = listaPontuacao->pontuacaoAtual->anterior;
	free(listaPontuacao->pontuacaoAtual);
	listaPontuacao->pontuacaoAtual = listaPontuacao->primeiraPontuacao;

}


/**
* Função resp
onsável por carregar, do arquivo cujo nome está em "parametros.h", as pontuacoes anteriores
*
*/


LISTA_PONTUACAO *carrega_placar(){
	char nome[100];
	int pontos;
	char data[100];
	char tempo[100];

	FILE *parquivo;
	LISTA_PONTUACAO *listaPontuacao = malloc(sizeof(LISTA_PONTUACAO));
	inicializaListaPlacar(listaPontuacao);

	parquivo = fopen(ARQUIVO_PLACAR,"r+");

	if (!parquivo){

		return NULL;
	}

	
	while (fscanf(parquivo,"%s %d %s %s",nome, &pontos, data, tempo) != EOF){

		   PONTUACAO *pontuacao = malloc(sizeof(PONTUACAO));
		   strcpy(pontuacao->nome,nome);
		   pontuacao->pontos = pontos;
		   strcpy(pontuacao->data,data);
		   strcpy(pontuacao->tempo,tempo);
		   adicionaListaPontuacao(listaPontuacao,pontuacao);

	}
	if(listaPontuacao->primeiraPontuacao != NULL){
		while(listaPontuacao->pontuacaoAtual->proximo != NULL){
			listaPontuacao->pontuacaoAtual = listaPontuacao->pontuacaoAtual->proximo;
		}
		listaPontuacao->ultimaPontuacao = listaPontuacao->pontuacaoAtual;
		listaPontuacao->pontuacaoAtual = listaPontuacao->primeiraPontuacao;	
	}
	fclose(parquivo);
	return listaPontuacao;
}

void escreve_placar(LISTA_PONTUACAO *listaPontuacao){

	FILE *parquivo;
	parquivo = fopen(ARQUIVO_PLACAR,"w+");
	int rep = VERDADEIRO;

	if (!parquivo){

		return;
	}

	while(rep){
		
		fprintf(parquivo,"%s %d %s %s \n", listaPontuacao->pontuacaoAtual->nome,listaPontuacao->pontuacaoAtual->pontos, listaPontuacao->pontuacaoAtual->data, listaPontuacao->pontuacaoAtual->tempo);

		if(listaPontuacao->pontuacaoAtual->proximo != NULL){
			listaPontuacao->pontuacaoAtual = listaPontuacao->pontuacaoAtual->proximo;
		}else{
			listaPontuacao->pontuacaoAtual = NULL;
			rep = FALSO;
		}
	}
	fclose(parquivo);
}


void mostra_placar(LISTA_PONTUACAO *listaPontuacao){
	listaPontuacao->pontuacaoAtual = listaPontuacao->primeiraPontuacao;
	while(listaPontuacao->pontuacaoAtual->proximo != NULL){
		printf("\n\nNome: %s pontuacao: %d\n\n", listaPontuacao->pontuacaoAtual->nome,listaPontuacao->pontuacaoAtual->pontos);
		listaPontuacao->pontuacaoAtual = listaPontuacao->pontuacaoAtual->proximo;
	}

}
