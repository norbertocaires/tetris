#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pecas.h"

/**
* Função que retorna um parâmetro do tipo PECA, aleatório, gerando seu tipo e tamanho.
*
**/

PECA gera_peca(){

   srand( (unsigned)time(NULL) );
   PECA peca;

   peca.tipo = gera_tipo_peca();
   peca.tamanho = gera_tamanho_peca();
   gera_posicao_peca(&peca);
   peca.cor = gera_cor_peca();
   peca.status = EM_JOGO;
   return peca;
}


/**
* Função que gera, aleatóriamente o tamanho da peça. Nessa versão a peça terá entre os tamanhos 3 e 5.
*
*/

int gera_tamanho_peca(){
	int tamanho_peca = 0;

	while(tamanho_peca<3 || tamanho_peca>5){
    		tamanho_peca=rand()%6;
	}
	return tamanho_peca;

}

/**
* Função que gera, aleatoriamente a cor da peça. 
*
*/

int gera_cor_peca(){
	int cor_peca = 0;

	srand(time(NULL));

	while(cor_peca<4 || cor_peca>7){
    		cor_peca=rand()%8;
	}
	return cor_peca;

}

/**
* Função que gera, aleatóriamente, o tipo da peça. Nessa versão poderá ser do tipo RETA_VERTICAL e RETA_HORIZONTAL. Caso haja
* erro na geração, será retornado o número 99.
*
*/

int gera_tipo_peca(){
	int tipo_peca = rand()%QTD_PECAS;

	switch(tipo_peca){
		case 0:
			return RETA_VERTICAL;
		case 1:
			return RETA_HORIZONTAL;
		default:
			return 99;
	}
}

/**
* Função que gera, aleatóriamente, a posicao inicial da peça.
* Vertical: início da peça em [0][13].
* Horizontal: [0][x]... x varia com o tamanho da peça, mas com o foco no centro da linha.
*/

void gera_posicao_peca(PECA* peca){
	if(peca->tipo == 1){
		peca->pos_linha = 0;
		peca->pos_coluna = 13;
	}
	if(peca->tipo == 2){
		peca->pos_linha = 0;
		if(peca->tamanho == 3)
			peca->pos_coluna = 13 - 1;
		else
			peca->pos_coluna = 13 - 2;
	}
}

/**
* Funcao inicialza lista de peças.
*
*/
void inicializaLista(PECAS *pecas){
	pecas->primeiro = NULL;
	pecas->ultimo = NULL;
	pecas->tamanho = 0;
}

/**
* Adiciona uma peça na lista.
*
*/
void adicionaPecaLista(PECAS *pecas, PECA *peca ){
	if(pecas->primeiro == NULL){
		pecas->primeiro = peca;
		pecas->ultimo = peca;
	}else{		
		pecas->ultimo->proximo = peca;
		pecas->ultimo = peca;
	}
	peca->proximo = NULL;
	pecas->tamanho++;
}
