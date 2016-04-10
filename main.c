#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "pecas.h"
#include "engine.h"
#include "tela.h"
#include "parametros.h"

int main(){
	int fimDeJogo = 0,pontuacao=0;
	char input;
	int tabuleiro[NUM_LINHAS][NUM_COLUNAS];

	// PECA CORRENTE (ultima da lista de pecas)
	PECA* peca;

	//LISTA DE PECAS
	PECAS pecas;
	inicializaLista(&pecas);

	//LISTA DE QTD PECAS
	PECAS lista_qtd_cada_peca;
	inicializaLista(&lista_qtd_cada_peca);

	memset(tabuleiro, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));

	inicia_ncurses();
	 	
	imprime_borda_tela();
	imprime_tela_inicial();
	imprime_borda_tabuleiro();
	imprime_tela_status(pontuacao);
	pega_input();


	time_t hora_inicio = time(NULL);

	while(verifica_fim_de_jogo(tabuleiro) == 0){

		peca = gera_peca();
		adicionaPecaLista(&pecas, peca);

		insere_peca_tabuleiro(tabuleiro, peca);

		imprime_tabuleiro_sem_borda(tabuleiro);
		while(peca->status == EM_JOGO){
			input = pega_input();
			if(input == 'D')//26
				move_peca_para_esquerda(tabuleiro, peca);
			if(input == 'C')//27
				move_peca_para_direita(tabuleiro, peca);
			if(input == 'B')//28
				move_peca_para_baixo(tabuleiro, peca);
			verifica_peca_em_jogo(tabuleiro, peca);
			imprime_tabuleiro_sem_borda(tabuleiro);

		}
		pontuacao = pontuacao + pontua(tabuleiro);
		imprime_tela_status(pontuacao);
	}

	time_t hora_final =  time(NULL);
	
	gera_lista_de_qtds(&pecas, &lista_qtd_cada_peca);
	imprime_tela_final(&lista_qtd_cada_peca, pontuacao, hora_inicio, hora_final);

	finaliza_ncurses();
	return 0;
}
