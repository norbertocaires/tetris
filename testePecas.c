
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "parametros.h"
#include "testePecas.h"
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "pecas.h"

PECA* gera_peca_teste(int tamanho, int tipo){
	PECA* peca = malloc(sizeof(PECA));
	peca->status = EM_JOGO;
	peca->pos_linha = 0;
	peca->pos_coluna = 13;
	peca->tipo = tipo;
	peca->tamanho = tamanho;
	peca->cor = 100;

	peca->tamanho = tamanho;
	peca->rotacao = 0;
	peca->proximo = NULL;
	peca->qtd = 0;

	return peca;
}


/* *Teste da função gera_peca**/
void teste_gera_peca(){
  PECA* peca = malloc(sizeof(PECA));
  int passou,i;

  for(i=0;i<10;i++){
	passou = VERDADEIRO;
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
	CU_ASSERT_TRUE(passou);
  }
}

/** Teste da função gera_tamanho_peca**/
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

/** Teste da função gera_tipo_peca**/
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


/**Teste da função gera_posicao_peca**/
void teste_gera_posicao_peca(){
    PECA* peca1 = gera_peca_teste(4, RETA_VERTICAL);
    PECA* peca2 = gera_peca_teste(3, RETA_HORIZONTAL);
    PECA* peca3 = gera_peca_teste(4, RETA_HORIZONTAL);
    PECA* peca4 = gera_peca_teste(5, RETA_HORIZONTAL);

	int passou;
	passou = VERDADEIRO;

 	srand( (unsigned)time(NULL) );

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

/** Teste da função gera_cor_peca**/
void teste_gera_cor_peca(){

	int cor_peca,passou;
	passou = VERDADEIRO;

	cor_peca = gera_cor_peca();

	if(cor_peca<3 || cor_peca>7)
		passou = FALSO;

	CU_ASSERT_TRUE(passou);
}

/** Testa de a inicialização de lista é feita corretamente */
void teste_inicia_lista_pecas(void){
	PECAS lista;
	inicializaLista(&lista);
	CU_ASSERT_TRUE( lista.primeiro == NULL );
	CU_ASSERT_TRUE( lista.ultimo == NULL );
	CU_ASSERT_TRUE( lista.tamanho == 0 );
}

/** Testa a insercao de 1 elemento em uma lista        */
void teste_adiciona_na_lista(void){
	PECAS lista;
	PECA* peca =  gera_peca();
	inicializaLista(&lista);
	adicionaPecaLista(&lista, peca);
	CU_ASSERT_TRUE( lista.primeiro == peca );
	CU_ASSERT_TRUE( lista.ultimo == peca );
	CU_ASSERT_TRUE( lista.tamanho == 1 );
}

/** Testa a insercao de 60 elementos na lista*/
void teste_adiciona_60_pecas_na_lista(void){
	PECAS lista;
	PECA* peca_primeira;
	int i;
	inicializaLista(&lista);
	peca_primeira = gera_peca();
	adicionaPecaLista(&lista, peca_primeira);
	for(i=2;i<=60;i++){
		PECA* peca = gera_peca();
		adicionaPecaLista(&lista, peca);
		CU_ASSERT_TRUE( lista.primeiro == peca_primeira );
		CU_ASSERT_TRUE( lista.ultimo == peca );
		CU_ASSERT_TRUE( lista.tamanho == i );
	}
}
/** Adiciona os casos de teste na suite de teste*/
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
	
	CU_ADD_TEST(suite, teste_inicia_lista_pecas);
	CU_ADD_TEST(suite, teste_adiciona_na_lista);
	CU_ADD_TEST(suite, teste_adiciona_60_pecas_na_lista);

}

/** Executa o teste do modulo pecas*/
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
