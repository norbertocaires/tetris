#include <ncurses.h>
#include "pecas.h"
#include "parametros.h"



void inicia_ncurses(){
	initscr();
	start_color();
}

void finaliza_ncurses(){
	
	endwin();
}

int pega_input(){
	fflush(stdin);
	__fpurge(stdin);
	return getch();
}

void insere_peca_tabuleiro(int tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA peca){
	if(peca.tipo == 1){
		int linha;
		for(linha = 0; linha< peca.tamanho; linha++){
			tabuleiro[linha][peca.pos_coluna] = peca.cor;
		}
	}
	if(peca.tipo == 2){
		int coluna;
		for(coluna = peca.pos_coluna; coluna< peca.tamanho + peca.pos_coluna; coluna++){
			tabuleiro[peca.pos_linha][coluna] = peca.cor;
		}
	}
}

void move_peca_para_esquerda(int tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA* peca){
	if(peca->tipo == 1){
		if(peca->pos_coluna == 0)
			return;
		int linha;
		for(linha = peca->pos_linha; linha< peca->tamanho + peca->pos_linha; linha++){
			if(tabuleiro[linha][peca->pos_coluna-1] == CHAR_PECA){
				return;
			}
		}
		for(linha = peca->pos_linha; linha< peca->tamanho + peca->pos_linha; linha++){
			tabuleiro[linha][peca->pos_coluna-1] = tabuleiro[linha][peca->pos_coluna];
			tabuleiro[linha][peca->pos_coluna] = 0;

		}
	}
	if(peca->tipo == 2){
		if(peca->pos_coluna == 0){
			return;
		}
		if(tabuleiro[peca->pos_linha][peca->pos_coluna-1] == ' '){
			tabuleiro[peca->pos_linha][peca->pos_coluna-1] = tabuleiro[peca->pos_linha][peca->pos_coluna + peca->tamanho -1];
			tabuleiro[peca->pos_linha][peca->pos_coluna + peca->tamanho -1] = 0;
		}else{
			return;
		}
	}
	peca->pos_coluna--;
}

void move_peca_para_direita(int tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA* peca){
	if(peca->tipo == 1){
		if(peca->pos_coluna > NUM_COLUNAS-2){
			return;
		}
		int linha;
		for(linha = peca->pos_linha; linha< peca->tamanho+peca->pos_linha; linha++){
			if(tabuleiro[linha][peca->pos_coluna+1] == CHAR_PECA){
				return;
			}
		}
		for(linha = peca->pos_linha; linha< peca->tamanho+peca->pos_linha; linha++){
			tabuleiro[linha][peca->pos_coluna+1] = tabuleiro[linha][peca->pos_coluna] = ' ';
			tabuleiro[linha][peca->pos_coluna] = 0;

		}
	}
	if(peca->tipo == 2){
		if(peca->pos_coluna + peca->tamanho > NUM_COLUNAS-1){
			return;
		}
		if(tabuleiro[peca->pos_linha][peca->pos_coluna+ peca->tamanho] == ' '){
			tabuleiro[peca->pos_linha][peca->pos_coluna + peca->tamanho] = tabuleiro[peca->pos_linha][peca->pos_coluna];
			tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;
			
		}else{
			return;
		}
	}
	peca->pos_coluna++;
}

void move_peca_para_baixo(int tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA* peca){
	if(peca->tipo == 1){
		if(peca->pos_linha + peca->tamanho >= NUM_LINHAS)
			return;
		if(tabuleiro[peca->pos_linha + peca->tamanho][peca->pos_coluna] == CHAR_PECA)
			return;
		tabuleiro[peca->pos_linha + peca->tamanho][peca->pos_coluna] = tabuleiro[peca->pos_linha][peca->pos_coluna];
		tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;
	}
	if(peca->tipo == 2){
		if(peca->pos_linha  > NUM_LINHAS-1){
			return;
		}
		int coluna;
		for(coluna = peca->pos_coluna; coluna < peca->pos_coluna + peca->tamanho; coluna++){
			if(tabuleiro[peca->pos_linha+1][coluna] == CHAR_PECA){
				return;
			}
		}
		for(coluna = peca->pos_coluna; coluna < peca->pos_coluna + peca->tamanho; coluna++){
			tabuleiro[peca->pos_linha + 1][coluna] = tabuleiro[peca->pos_linha][coluna];
			tabuleiro[peca->pos_linha][coluna] = 0;
		}
	}
	peca->pos_linha++;
}

void verifica_peca_em_jogo(int tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA* peca){
	if(peca->tipo == 1){
		if(peca->pos_linha + peca->tamanho >= NUM_LINHAS)
			peca->status = FIXA;
		if(tabuleiro[peca->pos_linha + peca->tamanho][peca->pos_coluna] != 0)
			peca->status = FIXA;
	}
	if(peca->tipo == 2){
		if(peca->pos_linha  > NUM_LINHAS-2){
			peca->status = FIXA;
		}
		int coluna;
		for(coluna = peca->pos_coluna; coluna < peca->pos_coluna + peca->tamanho; coluna++){
			if(tabuleiro[peca->pos_linha+1][coluna] != 0){
				peca->status = FIXA;
			}
		}
	}
}

int verifica_fim_de_jogo(int tabuleiro[NUM_LINHAS][NUM_COLUNAS]){
	int coluna;
	for(coluna = 0; coluna < NUM_COLUNAS; coluna++){
		if(tabuleiro[5][coluna] != 0){
			return 1;
		}
	}
	return 0;
}
