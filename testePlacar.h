#ifndef _testePecas_h
#define _testePecas_h
#include "placar.h"

/**
* Abaixo estão as funções que efetuam os testes o modulo Pecas
*/


void teste_inicializa_lista_placar(void);

/**
*		Função que efetuara a leitura de um arquivo "teste_placar.txt", e carregara o placar em uma lista de pontuacoes.
*		Eh pressuposto que o arquivo existe, estah formatado da maneira correta e estah ordenado. O arquivo deve ser o seguinte:
*		
*		nome1 500 11/06/2016 0:0:4 
*		nome2 400 11/06/2016 0:0:4
*		nome3 300 11/06/2016 0:0:4
*		nome4 200 11/06/2016 0:0:4
*		nome5 100 11/06/2016 0:0:4
*
*		Sendo os campos: nome, pontuacao, data e tempo de jogo
*
*/
void teste_carrega_placar(void);
void teste_atualiza_placar(void);
void teste_mostra_placar(void);   
void teste_retira_ultima_pontuacao(void);
void teste_adiciona_lista_pontuacao(void);
void teste_escreve_placar(void);


#endif
