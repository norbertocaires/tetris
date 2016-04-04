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
   peca.pos_x = gera_posicao_peca(peca.tipo,peca.tamanho);
   peca.status = FIXA;
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
* Função que gera, aleatóriamente, o tipo da peça. Nessa versão poderá ser do tipo RETA_VERTICAL e RETA_HORIZONTAL. Caso haja
* erro na geração, será retornado o número 99.
*
*/

int gera_tipo_peca(){
	int tipo_peca = rand()%2;

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
*
*/

int gera_posicao_peca(int tipo, int tamanho){
	int posicao = 0;

	while(posicao ==0){
		posicao = rand()%26;
		if(tipo == RETA_HORIZONTAL && (posicao+tamanho)>25){
			posicao=0;
		}
	}
	return posicao;
}
