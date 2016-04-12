/**
 * O código deste módulo está totalmente desatualizado. Está como o exemplo passado em sala pela professora.
 */


#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 #include "teste.h"
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "pecas.h"

/
/* Teste numero numero par */
void teste_DT_VerificaParidade_Par(void){
	int resultado;
	resultado = VerificaParidade(2);
	CU_ASSERT_TRUE( !resultado );
	//CU_ASSERT(VerificaParidade(2) > 1);
}

/* Teste numero impar */
void teste_DT_VerificaParidade_Impar(void){
	int resultado;
	resultado = VerificaParidade(3);
	CU_ASSERT_TRUE( resultado );
}

/* Teste numero zero */
void teste_DT_VerificaParidade_Zero(void){
	int resultado;
	resultado = VerificaParidade(0);
	CU_ASSERT_TRUE( !resultado );
}

/* Teste letra maiuscula */
void teste_DT_ProximaLetra_Maiuscula(void){
	char resultado;
	resultado = ProximaLetra('A');
	CU_ASSERT_EQUAL( resultado, 'B' );
}

/* Teste letra maiuscula */
void teste_DT_ProximaLetra_Minuscula(void){
	char resultado;
	resultado = ProximaLetra('d');
	CU_ASSERT_EQUAL( resultado, 'e' );
}

/* Teste letra maiuscula */
void teste_DT_ProximaLetra_Z(void){
	char resultado;
	resultado = ProximaLetra('Z');
	CU_ASSERT_EQUAL( resultado, 'A' );
}

void  adicionar_suite(void){
	CU_pSuite suite;

	/*Cria uma suite que conterá todos os testes*/
	suite = CU_add_suite("Testes modulo pecas",NULL,NULL);

	/*Adiciona os testes para a função DT_data_valida*/
	CU_ADD_TEST(suite, teste_DT_VerificaParidade_Par);
	CU_ADD_TEST(suite, teste_DT_VerificaParidade_Impar);
	CU_ADD_TEST(suite, teste_DT_VerificaParidade_Zero);
	CU_ADD_TEST(suite, teste_DT_ProximaLetra_Maiuscula);
	CU_ADD_TEST(suite, teste_DT_ProximaLetra_Minuscula);
	CU_ADD_TEST(suite, teste_DT_ProximaLetra_Z);

}


int main(void, void* tabuleiro) {
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

	return CU_get_error();
}
