/**
 * O código deste módulo está totalmente desatualizado. Está como o exemplo passado em sala pela professora.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "parametros.h"
#include "testePecas.h"
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "pecas.h"


void teste_gera_peca(){


  PECA* peca = malloc(sizeof(PECA));
  int passou,i;
  passou = VERDADEIRO;

  for(i=0;i<10;i++){

  	peca = gera_peca();

  	if(peca->tipo != RETA_VERTICAL && peca->tipo != RETA_HORIZONTAL){
  		passou = FALSO;
  	}
  		
  	if(peca->tamanho<3 || peca->tamanho>5){
  		passou = FALSO;
  	}
  	if(peca->pos_linha != 0 && peca->pos_coluna != 11 && peca->pos_coluna != 12 && peca->pos_coluna != 13){
  		passou = FALSO;
  	}
  	if(peca->cor<1 || peca->cor>7){
		passou = FALSO;
	}
  }

  CU_ASSERT_TRUE(passou);
}

void teste_gera_tamanho_peca(){
	int passou,i,temp;

	passou = VERDADEIRO;

	for(i=0;i<60;i++){
		temp = gera_tamanho_peca();
		if(temp<TAM_PECA_MIN || temp>TAM_PECA_MAX){
			passou = FALSO;
		}
	}
	CU_ASSERT_TRUE(passou);
}

void teste_gera_tipo_peca(){

	int passou,i,temp;
	passou = VERDADEIRO;

		for(i=0;i<30;i++){
		temp = gera_tipo_peca();
		if(temp!=RETA_VERTICAL && temp!=RETA_HORIZONTAL){
			passou = FALSO;
		}
	}
	CU_ASSERT_TRUE(passou);

}
void teste_gera_posicao_peca(){

	int passou;
	passou = VERDADEIRO;

 	srand( (unsigned)time(NULL) );
    PECA* peca1 = malloc(sizeof(PECA));
    PECA* peca2 = malloc(sizeof(PECA));
    PECA* peca3 = malloc(sizeof(PECA));
    PECA* peca4 = malloc(sizeof(PECA));

    peca1->tipo = RETA_VERTICAL; 
    peca1->tamanho = 4;

    peca2->tipo = RETA_HORIZONTAL;
    peca2->tamanho = 3;

    peca3->tipo = RETA_HORIZONTAL;
    peca3->tamanho = 4;

	peca4->tipo = RETA_HORIZONTAL; 
    peca4->tamanho = 5;    

    gera_posicao_peca(peca1);
    gera_posicao_peca(peca2);
    gera_posicao_peca(peca3);    
    gera_posicao_peca(peca4);

    if(peca1->pos_linha != 0 || peca2->pos_linha!=0 || peca3->pos_linha != 0 || peca4->pos_linha != 0){
    	passou = FALSO;
    	return;
    }

    if(peca1->pos_coluna != 13 || peca2->pos_coluna != 12 || peca3->pos_coluna != 11 || peca3->pos_coluna != 11)
    	passou = FALSO;

    CU_ASSERT_TRUE(passou);
}

void teste_gera_cor_peca(){

	int cor_peca,passou;
	passou = VERDADEIRO;

	cor_peca = gera_cor_peca();

	if(cor_peca<1 || cor_peca>7)
		passou = FALSO;

	CU_ASSERT_TRUE(passou);
}

void  adicionar_suite(void){
	CU_pSuite suite;

	/*Cria uma suite que conterá todos os testes*/
	suite = CU_add_suite("Testes modulo pecas",NULL,NULL);

	/*Adiciona os testes para a função DT_data_valida*/
	CU_ADD_TEST(suite, teste_gera_peca);
	CU_ADD_TEST(suite, teste_gera_tamanho_peca);
	CU_ADD_TEST(suite, teste_gera_tipo_peca);
	CU_ADD_TEST(suite, teste_gera_posicao_peca);
	CU_ADD_TEST(suite, teste_gera_cor_peca);
}

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
	CU_basic_run_tests();
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