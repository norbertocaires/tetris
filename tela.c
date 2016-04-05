#include <ncurses.h>
#include "parametros.h"



void imprime_borda_tela(){
	int a;
	for(a=0;a<COLS;a++){
		mvaddch(0, a, '@');
		mvaddch(LINES-1, a, '@');
	}
	for(a=0;a<LINES;a++){
		mvaddch(a+1, 0,'@');
		mvaddch(a, COLS-1, '@');
	}
	refresh();
}

void imprime_tabuleiro_com_borda(char tabuleiro[NUM_LINHAS][NUM_COLUNAS]){
	int a, b;
	for(a=0;a<NUM_LINHAS;a++){
		if(a+5 != 10){
			mvaddch(a+POS_L, POS_C-1, '|');
			mvaddch(a+POS_L, NUM_COLUNAS+POS_C, '|');
		}else{
			mvaddch(a+POS_L, POS_C-1, '*');
			mvaddch(a+POS_L, NUM_COLUNAS+POS_C, '*');
		}
		for(b=0;b<NUM_COLUNAS;b++){
			mvaddch(4, b+POS_C, '_');
			mvaddch(NUM_LINHAS+POS_L, b+POS_C, '*');
			mvaddch(a+POS_L, b+POS_C,tabuleiro[a][b]);
		}
	}
	refresh();
}

void imprime_tabuleiro_sem_borda(char tabuleiro[NUM_LINHAS][NUM_COLUNAS]){
	int a, b;
	for(a=0;a<NUM_LINHAS;a++){
		for(b=0;b<NUM_COLUNAS;b++){
			mvaddch(a+POS_L, b+POS_C,tabuleiro[a][b]);
		}
	}
	refresh();
}
