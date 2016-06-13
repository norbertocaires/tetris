#include <time.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "placar.h"
#include "parametros.h"
#include "string.h"


/** Funcao que transforma um inteiro em string, inclusive incluido um zero a esquerda quando necessario
*   @param number: Esse parametro eh o numero que sera formatado
*	@return Retorna um ponteiro para a string contendo o inteiro formatado.
*/

char* format(int number){
	char *retorno;
	char ret[100];

   if (number < 10){
      snprintf(ret, sizeof(ret), "0%d", number);
	//sprintf(ret,"0%d",number);
      retorno = ret;
   }
   else{
      snprintf(ret, sizeof(ret), "%d", number);
	//sprintf(ret,"%d",number);
      retorno = ret;

   }
   return retorno;
}      

/** Essa funcao retorna a data atual, em que o programa esta sendo executado
*	@return Essa funcao retorna um poteiro para a string contendo a data atual
*
*/
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
   snprintf(strDia, sizeof(strDia), "%s", format(dia));
//   sprintf(strDia,"%s",format(dia));
   snprintf(strMes, sizeof(strMes), "%s", format(mes));
//   sprintf(strMes,"%s",format(mes));
   snprintf(strAno, sizeof(strAno), "%s", format(ano));
//   sprintf(strAno,"%s",format(ano));

   // cria a variavel de retorno dos dados e cria um ponteiro para essa variavel      
   snprintf(strData, sizeof(strData), "%s/%s/%s",strDia,strMes,strAno);
//   sprintf(strData,"%s/%s/%s",strDia,strMes,strAno);
   
   // retorna data no formato dd:MM:yyyy com um ponteiro
   dataPtr = strData;
   return dataPtr;
}




/**
*   Função responsável por inicializar os parâmetros da lista de pontuações com os valores padrão.
*   
*	@param LISTA_PONTUACAO *lista_pontuacao: Ponteiro para uma lista de pontuacões. Ao final da execuçãoo, os campos da
*	lista serao: \n
*	primeira_pontuacao = NULL, ultima_pontuacao = NULL, pontuacao_atual = NULL, qtd_pontuacoes = 0
*		
*   
*/

void inicializa_lista_placar(LISTA_PONTUACAO *lista_pontuacao){

	//Inicialização dos parâmetros da lista
	lista_pontuacao->qtd_pontuacoes = 0;
	lista_pontuacao->primeira_pontuacao = NULL;
	lista_pontuacao->pontuacao_atual = NULL;
	lista_pontuacao->ultima_pontuacao= NULL;

}


/**  Funcao responsável por incluir uma nova pontuação em uma lista de pontuações. A inclusão é sempre feita ordenada.
*	 Uma nova pontuação só é incluída quando ela for maior do que a pontuação que já está em último da lista. O número
*    máximo de pontuações que a lista pode ter, está definido no arquivo "parametros.h", na constante QTD_MAX_PLACAR
*	 
*	 @param lista_pontuacao: Ponteiro para a lista de pontuações que poderá receber uma nova pontuação
*    @param pontuacao: Ponteiro para a pontuação que poderá ser incluída na lista de pontuações
*	 
*/

void adiciona_lista_pontuacao(LISTA_PONTUACAO *lista_pontuacao, PONTUACAO *pontuacao){
	
	pontuacao->proximo = NULL;
	pontuacao->anterior = NULL;

	if (lista_pontuacao->primeira_pontuacao == NULL ){//Caso de a lista estar vazia
		lista_pontuacao->primeira_pontuacao = pontuacao;
	}else if(pontuacao->pontos > lista_pontuacao->primeira_pontuacao->pontos){

		lista_pontuacao->primeira_pontuacao->anterior = pontuacao;
		pontuacao->proximo = lista_pontuacao->primeira_pontuacao;
		lista_pontuacao->primeira_pontuacao = pontuacao;
		
	}else{ 
		//Laço que posiciona o ponteiro pontuacao_atual uma posicao antes do local onde a nova posicao será inserida
		while(lista_pontuacao->pontuacao_atual->pontos > pontuacao->pontos 
		&& lista_pontuacao->pontuacao_atual->proximo != NULL && lista_pontuacao->pontuacao_atual->proximo->pontos > pontuacao->pontos){	
				lista_pontuacao->pontuacao_atual = lista_pontuacao->pontuacao_atual->proximo;	
		}
		pontuacao->anterior = lista_pontuacao->pontuacao_atual;
		pontuacao->proximo = lista_pontuacao->pontuacao_atual->proximo;
		lista_pontuacao->pontuacao_atual->proximo = pontuacao;
		if(pontuacao->proximo != NULL){
			pontuacao->proximo->anterior = pontuacao;
		}

		while(lista_pontuacao->pontuacao_atual->proximo != NULL){
			lista_pontuacao->pontuacao_atual = lista_pontuacao->pontuacao_atual->proximo;
		}
		lista_pontuacao->ultima_pontuacao = lista_pontuacao->pontuacao_atual;
		lista_pontuacao->pontuacao_atual = lista_pontuacao->primeira_pontuacao;		

	}

	lista_pontuacao->qtd_pontuacoes++;
	lista_pontuacao->pontuacao_atual = lista_pontuacao->primeira_pontuacao;
	if(lista_pontuacao->qtd_pontuacoes > QTD_MAX_PLACAR){
		retira_ultima_pontuacao(lista_pontuacao);
	}

	
}

/**  Essa função é responsável por excluir a pontuação que está por último na lista de pontuações. Ela é utilizada
*    para manter o número de pontuações sempre dentro do que foi definido no arquivo "parametros.h"
*	 
*	 @param lista_pontuacao: Ponteiro para a lista de pontuações cujo último nó será exluído.
*	 
*/


void retira_ultima_pontuacao(LISTA_PONTUACAO /*@out@*/ *lista_pontuacao){
	lista_pontuacao->pontuacao_atual = lista_pontuacao->primeira_pontuacao;
	while(lista_pontuacao->pontuacao_atual->proximo != NULL){
		lista_pontuacao->pontuacao_atual = lista_pontuacao->pontuacao_atual->proximo;
	}

	lista_pontuacao->pontuacao_atual->anterior->proximo = NULL;
	lista_pontuacao->ultima_pontuacao = lista_pontuacao->pontuacao_atual->anterior;
	free(lista_pontuacao->pontuacao_atual);
	lista_pontuacao->pontuacao_atual = lista_pontuacao->primeira_pontuacao;

}


/**
* Função responsável por carregar, do arquivo cujo nome está em "parametros.h", as pontuacoes anteriores.
*
* @param debug: Este parâmetro irá definir se o arquivo que será carregado é o de debug ou não.
*  
*/


LISTA_PONTUACAO *carrega_placar(int debug){
	char nome[100];
	int pontos;
	char data[100];
	char tempo[100];

	FILE *parquivo;
	LISTA_PONTUACAO *lista_pontuacao = malloc(sizeof(LISTA_PONTUACAO));
	lista_pontuacao->qtd_pontuacoes = 0;
	lista_pontuacao->primeira_pontuacao = NULL;
	lista_pontuacao->pontuacao_atual = NULL;
	lista_pontuacao->ultima_pontuacao = NULL;


	inicializa_lista_placar(lista_pontuacao);
	if(debug == VERDADEIRO)
		parquivo = fopen(ARQUIVO_PLACAR_TESTE,"a+");
	else
		parquivo = fopen(ARQUIVO_PLACAR,"a+");

	if (!parquivo){

		return NULL;
	}

	
	while (fscanf(parquivo,"%s %d %s %s",nome, &pontos, data, tempo) != EOF){

		   PONTUACAO *pontuacao = malloc(sizeof(PONTUACAO));
		   pontuacao->proximo = NULL;
		   pontuacao->anterior = NULL;
		   strcpy(pontuacao->nome,nome);
		   pontuacao->pontos = pontos;
		   strcpy(pontuacao->data,data);
		   strcpy(pontuacao->tempo,tempo);
		   adiciona_lista_pontuacao(lista_pontuacao,pontuacao);

	}
	if(lista_pontuacao->primeira_pontuacao != NULL){
		while(lista_pontuacao->pontuacao_atual->proximo != NULL){
			lista_pontuacao->pontuacao_atual = lista_pontuacao->pontuacao_atual->proximo;
		}
		lista_pontuacao->ultima_pontuacao = lista_pontuacao->pontuacao_atual;
		lista_pontuacao->pontuacao_atual = lista_pontuacao->primeira_pontuacao;	
	}
	fclose(parquivo);
	return lista_pontuacao;
}

/**  Funcao responsável por escrever no arquivo definido em "parametros.h", o placar que está salvo em memória.
*
*	 @param lista_pontuacao: Ponteiro para a lista de pontuação cujas pontuações serão escritas em disco.
*	 
*/

void escreve_placar(LISTA_PONTUACAO *lista_pontuacao){

	FILE *parquivo;
	int rep = VERDADEIRO;
	parquivo = fopen(ARQUIVO_PLACAR,"w+");

	if (!parquivo){

		return;
	}

	while(rep){
		
		fprintf(parquivo,"%s %d %s %s \n", lista_pontuacao->pontuacao_atual->nome,lista_pontuacao->pontuacao_atual->pontos, lista_pontuacao->pontuacao_atual->data, lista_pontuacao->pontuacao_atual->tempo);

		if(lista_pontuacao->pontuacao_atual->proximo != NULL){
			lista_pontuacao->pontuacao_atual = lista_pontuacao->pontuacao_atual->proximo;
		}else{
			lista_pontuacao->pontuacao_atual = NULL;
			rep = FALSO;
		}
	}
	fclose(parquivo);
}

