#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pecas.h"
#include "engine.h"
#include "tela.h"
#include "parametros.h"

int main(){
	int fimDeJogo = 0;
	int input = 0;
	char tabuleiro[NUM_LINHAS][NUM_COLUNAS];

	// PECA CORRENTE (ultima da lista de pecas)
	PECA peca;

	//LISTA DE PECAS
	PECAS pecas;
	inicializaLista(&pecas);

	memset(tabuleiro,' ', NUM_LINHAS * NUM_COLUNAS * sizeof(char));

	inicia_ncurses();

	imprime_borda_tela();
	imprime_tabuleiro_com_borda(tabuleiro);

	peca = gera_peca();
	adicionaPecaLista(&pecas, &peca);
	insere_peca_tabuleiro(tabuleiro, peca);

	while(1){
		imprime_tabuleiro_sem_borda(tabuleiro);
		input = pega_input();
		if(input == 27)
			move_peca_para_esquerda(tabuleiro, &peca);
		if(input == 26)
			move_peca_para_direita(tabuleiro, &peca);
		if(input == 25)
			move_peca_para_baixo(tabuleiro, &peca);
	}
	finaliza_ncurses();
	return 0;
}
