#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pecas.h"
#include "parametros.h"

/**
* Função que retorna um parâmetro do tipo PECA, aleatório, gerando seu tipo e tamanho.
*
**/

PECA* gera_peca(){

   srand((unsigned)time(NULL) );
   PECA* peca = malloc(sizeof(PECA));

   peca->tipo = gera_tipo_peca();
   peca->tamanho = gera_tamanho_peca();
   gera_posicao_peca(peca);
   peca->cor = gera_cor_peca();
   peca->status = EM_JOGO;
   return peca;
}


/**
* Função que gera, aleatóriamente o tamanho da peça. Nessa versão a peça terá entre os tamanhos 3 e 5.
*
*/

int gera_tamanho_peca(){
	int tamanho_peca = 0;

	while(tamanho_peca<TAM_PECA_MIN || tamanho_peca>TAM_PECA_MAX){
    		tamanho_peca=rand()%(TAM_PECA_MAX+1);
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

	while(cor_peca<3 || cor_peca>7){
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
	if(peca->tipo == RETA_VERTICAL){
		peca->pos_linha = 0;
		peca->pos_coluna = 13;
	}
	if(peca->tipo == RETA_HORIZONTAL){
		peca->pos_linha = 0;
		if(peca->tamanho == 3)
			peca->pos_coluna = 13 - 1;
		else
			peca->pos_coluna = 13 - 2;
	}
}

/**
* Faz copia de peca
*/
PECA* faz_copia_de_peca(PECA* peca){
	PECA* copia = malloc(sizeof(PECA));
	copia->tipo = peca->tipo;
	copia->tamanho = peca->tamanho;
	copia->pos_linha = peca->pos_linha;
	copia->pos_coluna = peca->pos_coluna;
	copia->status = peca->status;
	copia->cor = peca->cor;
	copia->qtd=1;
	return copia;
}

/**
* Função que gera lista de peças e com a quantidade que cada 
* peca apareceu no jogo;
**/
void gera_lista_de_qtds(PECAS* pecas, PECAS *nova_lista_qtd){
	if(pecas->primeiro == NULL)
		return;
	int add;

	PECA *peca = pecas->primeiro;
	PECA *peca_qtd;
	while(peca != NULL){
		peca_qtd = nova_lista_qtd->primeiro;
		add =0;
		while(peca_qtd != NULL){
			if(peca->tipo == peca_qtd->tipo && peca->tamanho == peca_qtd->tamanho ){
				peca_qtd->qtd ++;
				add =1;
			}
			peca_qtd = peca_qtd->proximo;
		}
		if(add ==0){

			adicionaPecaLista(nova_lista_qtd, faz_copia_de_peca(peca));
		}
		peca = peca->proximo;
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
	pecas->tamanho++;
}
