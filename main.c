#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"
#include "tela.h"
#include "parametros.h"

int main(){
	int fimDeJogo = 0;
	int input = 0;
	char tabuleiro[NUM_LINHAS][NUM_COLUNAS], *peca;

	memset(tabuleiro,' ', 15 * 25 * sizeof(char));

	inicia_ncurses();

	imprime_borda_tela();
	imprime_tabuleiro_com_borda(tabuleiro);

	while(fimDeJogo == 0){
		imprime_tabuleiro_sem_borda(tabuleiro);
		sorteia_peca();
		input = pega_input();
		fimDeJogo = 1;
	}
	finaliza_ncurses();
	return 0;
}
