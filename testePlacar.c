#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "parametros.h"
#include "testePecas.h"
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "placar.h"

/**
*   Função que teste se a inicialização da lista foi feita corretamente pela função "inicializa_lista_placar()".
*/

void teste_inicializa_lista_placar(void){
	int passou = FALSO;
	LISTA_PONTUACAO *lista;
	lista = malloc(sizeof(LISTA_PONTUACAO));
	inicializa_lista_placar(lista);


	if( lista->qtd_pontuacoes == 0 &&
		lista->primeira_pontuacao == NULL &&
		lista->pontuacao_atual == NULL &&
		lista->ultima_pontuacao == NULL
		){
		passou = VERDADEIRO;
	}

		CU_ASSERT_TRUE(passou);

}

/** Teste da funcao carrega_placar*/

void teste_carrega_placar(void){

	LISTA_PONTUACAO *lista;
	int i,aux_string,passou;

	lista = carrega_placar(VERDADEIRO);

	for(i=1;i<6;i++){		
		passou = VERDADEIRO;

		aux_string = strcmp(lista->pontuacao_atual->data,"11/06/2016");
		aux_string = strcmp(lista->pontuacao_atual->tempo,"0:0:4");
		switch (i){
			case 1:


				aux_string = strcmp(lista->pontuacao_atual->nome,"nome1");
				if(aux_string==0 || lista->pontuacao_atual->pontos == 500){
					passou = VERDADEIRO;
				}else{
					passou = FALSO;
				}

			break;
				
			case 2:
					aux_string = strcmp(lista->pontuacao_atual->nome,"nome2");
				if(aux_string==0 && lista->pontuacao_atual->pontos == 400){
					passou = VERDADEIRO;
				}else{
					passou = FALSO;
				}
			break;

			case 3:
					aux_string = strcmp(lista->pontuacao_atual->nome,"nome3");	
				if(aux_string==0 && lista->pontuacao_atual->pontos == 300){
					passou = VERDADEIRO;
				}else{
					passou = FALSO;
				}
			break;

			case 4:
					aux_string = strcmp(lista->pontuacao_atual->nome,"nome4");
				if(aux_string==0 && lista->pontuacao_atual->pontos == 200){
					passou = VERDADEIRO;
				}else{
					passou = FALSO;
				}
			break;

			case 5:
				aux_string = strcmp(lista->pontuacao_atual->nome,"nome5");
				if(aux_string==0 && lista->pontuacao_atual->pontos == 100){
					passou = VERDADEIRO;
				}else{
					passou = FALSO;
				}
			break;
		}

		if(lista->pontuacao_atual->proximo != NULL)
			lista->pontuacao_atual = lista->pontuacao_atual->proximo;
	
	}
	CU_ASSERT_TRUE(passou);

}

/**
*   Efetua o teste da funcao adiciona_lista_pontuacao() em tres cenarios:
*
*	1 - Quando a pontuacao a ser adicionada vai ficar em ultimo
*	2 - Quando a pontuacao a ser adicionada vai ficar em primeiro
*   3 - Quando a pontuacao a ser adicionada vai ficar em uma posicao intermediaria
*
*/

void teste_adiciona_lista_pontuacao(void){


	LISTA_PONTUACAO *lista;
	PONTUACAO *pontuacao;
	int passou;
	lista = malloc(sizeof(LISTA_PONTUACAO));


	lista = carrega_placar(VERDADEIRO);

	//Cenario 1
	pontuacao = malloc (sizeof(PONTUACAO));
	sprintf(pontuacao->nome,"nome_teste");
	sprintf(pontuacao->data,"01/01/01");
	sprintf(pontuacao->tempo,"00:00:00");
	pontuacao->pontos = 600;
	adiciona_lista_pontuacao(lista,pontuacao);
	if(lista->primeira_pontuacao->pontos == 600)
		passou = VERDADEIRO;
	else
		passou = FALSO;
	//Cenario 2
	pontuacao = malloc (sizeof(PONTUACAO));
	sprintf(pontuacao->nome,"nome_teste");
	sprintf(pontuacao->data,"01/01/01");
	sprintf(pontuacao->tempo,"00:00:00");
	pontuacao->pontos = 150;
	adiciona_lista_pontuacao(lista,pontuacao);
	if(lista->ultima_pontuacao->pontos == 150)
		passou = VERDADEIRO;
	else
		passou = FALSO;
	//Cenario 3
	pontuacao = malloc (sizeof(PONTUACAO));
	sprintf(pontuacao->nome,"nome_teste");
	sprintf(pontuacao->data,"01/01/01");
	sprintf(pontuacao->tempo,"00:00:00");
	pontuacao->pontos = 450;
	adiciona_lista_pontuacao(lista,pontuacao);
	passou = FALSO;
	while(lista->pontuacao_atual->proximo != NULL){
		if(lista->pontuacao_atual->pontos == 450)
			passou = VERDADEIRO;
		lista->pontuacao_atual = lista->pontuacao_atual->proximo;
	}

	CU_ASSERT_TRUE(passou);

}
/** Adiciona os casos de teste na suite de testes*/
void  adicionar_suite(void){
	CU_pSuite suite;

	/*Cria uma suite que conterá todos os testes*/
	suite = CU_add_suite("Testes modulo placar",NULL,NULL);

	/*Adiciona os testes para a função DT_data_valida*/
	CU_ADD_TEST(suite, teste_inicializa_lista_placar);
	CU_ADD_TEST(suite, teste_carrega_placar);
	CU_ADD_TEST(suite, teste_adiciona_lista_pontuacao);


}

/**Executa a suite de testes*/
int rodar_teste_pecas(){

	/*Inicializa o registro de suítes e testes do CUnit*/
	if (CUE_SUCCESS != CU_initialize_registry())
    		return CU_get_error();

    /*Adiciona os testes ao registro*/
   	adicionar_suite();

	/*Muda o modo do CUnit para o modo VERBOSE
	 O modo VERBOSE mostra algumas informacoes a
	 mais na hora da execucao. Outras opções: NORMAL e SILENT*/
	CU_basic_set_mode(CU_BRM_VERBOSE);

	/*Roda os testes e mostra na tela os resultados*/
	(void)CU_basic_run_tests();
	//CU_console_run_tests();
	//CU_automated_run_tests();


	/*Limpa o registro*/
	CU_cleanup_registry();
	return 1;
}

int main(){
	rodar_teste_pecas();
	return 1;
}
