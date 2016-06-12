#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pecas.h"
#include "parametros.h"

/**
* Função que gera uma PECA. Ela gera, aleatoriamente, seu tipo,tamanho e posicao.
*	
* Posicoes: 0 - Inicial
*       1 - 90 graus
*	    2 - 180 graus	
*	    3 - 270 graus
*
*
*     @return Retorna um ponteiro para PECA, 
**/

PECA* gera_peca(){
   PECA* peca;

   srand((unsigned)time(NULL) );
   peca = malloc(sizeof(PECA));

   peca->pos_linha = 0;
   peca->pos_coluna = 0;
   peca->proximo = NULL;

   peca->qtd = 0;
   peca->tipo = gera_tipo_peca();
   peca->tamanho = gera_tamanho_peca();
   peca->cor = gera_cor_peca();
   peca->status = EM_JOGO;
   peca->rotacao = 1;
   gera_posicao_peca(peca);
   return peca;
}


/**
* Função que gera, aleatóriamente o tamanho da peças retas. Os limites de tamanho estão no arquivo "parametros.h".
*
*  @return Retorna o tamanho gerado, dentro do intervalo definido
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
*    @return Retorna um inteiro representando a cor gerada.
*
*/

int gera_cor_peca(){
	int cor_peca = 0;

	(void )srand(time(NULL));

	while(cor_peca<3 || cor_peca>7){
    		cor_peca=rand()%8;
	}
	return cor_peca;

}

/**
* Função que gera, aleatóriamente, o tipo da peça. Caso haja erro na geração, será retornado o número 99.
*
* @return Retorna um inteiro representando o tipo da peça. As constantes estão definidas no arquivo "pecas.h"
*
*
*/
int gera_tipo_peca(){
	int tipo_peca = rand()%QTD_PECAS;

	switch(tipo_peca){
		case 0:
			return RETA_VERTICAL;
		case 1:
			return RETA_HORIZONTAL;
		case 2:
			return PECA_Z;
		case 3:
			return PECA_T ;
		case 4:	
			return PECA_QUADRADO;
		case 5:	
			return PECA_L;
		default:
			return 99;
	}
}

/**
* Função que gera, aleatóriamente, a posicao inicial das peças horizontais e verticais. Essa função é necessária
* Uma vez que esses tipos de peças tem tamanho variável.
* Vertical: início da peça em [0][13].
* Horizontal: [0][x]... x varia com o tamanho da peça, mas com o foco no centro da linha.
* @param peca: ponteiro para a peça cuja posicao inical será gerada.
*/

void gera_posicao_peca(PECA* peca){
	peca->pos_linha = 0;
	switch(peca->tipo){

		case RETA_VERTICAL:
			peca->pos_coluna = 12;
			break;
		case RETA_HORIZONTAL:
			if(peca->tamanho == 3)
				peca->pos_coluna = 12 - 1;
			if(peca->tamanho == 4)
				peca->pos_coluna = 12 - 1;
			if(peca->tamanho == 5)
				peca->pos_coluna = 12 - 2;
			break;
		default:
			peca->pos_coluna = 12;
			break;		
	}		
}

/**
* Faz copia de peca
* @param peca: Ponteiro para a peca que será copiada
* @return Ponteiro para a copia da peça recebida
*
*/
PECA* faz_copia_de_peca(PECA* peca){
	PECA* copia = malloc(sizeof(PECA));
	copia->tipo = peca->tipo;
	copia->tamanho = peca->tamanho;
	copia->pos_linha = peca->pos_linha;
	copia->pos_coluna = peca->pos_coluna;
	copia->status = peca->status;
	copia->cor = peca->cor;
	copia->qtd = 1;
	copia->proximo = NULL;
	copia->rotacao = peca->rotacao;
	return copia;
}

/**
* Função que gera lista de peças e com a quantidade que cada 
* peca apareceu no jogo;
*  @param pecas: Lista de pecas
*  @param nova_lista_qtd: lista de qtd de peças.
**/

void gera_lista_de_qtds(PECAS* pecas, PECAS *nova_lista_qtd){
	int add;
	PECA *peca;
	PECA *peca_qtd;
	PECA *copia;

	if(pecas->primeiro == NULL)
		return;

	peca = pecas->primeiro;
	while(peca != NULL){
		peca_qtd = nova_lista_qtd->primeiro;
		add = 1;
		copia = faz_copia_de_peca(peca);
		while(peca_qtd != NULL){
			if(copia->tipo == RETA_VERTICAL || copia->tipo == RETA_HORIZONTAL)
				copia->tipo = 10;
			if(peca_qtd->tipo == RETA_VERTICAL || peca_qtd->tipo == RETA_HORIZONTAL)
				peca_qtd->tipo = 10;
			if(copia->tipo == peca_qtd->tipo ){
				peca_qtd->qtd ++;
				add = 0;
			}
			peca_qtd = peca_qtd->proximo;
		}
		if(add == 1){
			adicionaPecaLista(nova_lista_qtd, copia);
		}
		peca = peca->proximo;
	}
}


/**
* Funcao inicialza lista de peças.
* @param Ponteiro para a lista de peças que será inicializada.
*/
void inicializaLista(PECAS /*@out@*/ *pecas){
	pecas->primeiro = NULL;
	pecas->ultimo = NULL;
	pecas->tamanho = 0;
}

/**
* Adiciona uma peça na lista.
*
* @param pecas: lista de peças que irá receber uma nova peca
* @param peca: Nova peça que será inserida na lista.
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
