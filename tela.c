#include <ncurses.h>
#include "parametros.h"
#include "pecas.h"

void imprime_borda_tela(){
	int temp;
	for(temp=0;temp<COLS;temp++){
		mvaddch(0, temp, '@');
		mvaddch(LINES-1, temp, '@');
	}
	for(temp=0;temp<LINES;temp++){
		mvaddch(temp+1, 0,'@');
		mvaddch(temp, COLS-1, '@');
	}
	refresh();
}

void imprime_borda_tabuleiro(){
	int linha, coluna;
	for(linha=0;linha<NUM_LINHAS;linha++){
		if(linha+5 != 10){
			mvaddch(linha+POS_L, POS_C-1, '|');
			mvaddch(linha+POS_L, NUM_COLUNAS+POS_C, '|');
		}else{
			mvaddch(linha+POS_L, POS_C-1, '*');
			mvaddch(linha+POS_L, NUM_COLUNAS+POS_C, '*');
		}
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			mvaddch(4, coluna+POS_C, '_');
			mvaddch(NUM_LINHAS+POS_L, coluna+POS_C, '*');
		}
	}
	refresh();
}

void imprime_tabuleiro_sem_borda(int tabuleiro[NUM_LINHAS][NUM_COLUNAS]){
	int linha, coluna;
/**
*   Inicialização dos "pairs" que serão utilizados para colorir as peças.
*   Cada um desses pares é uma das cores que as peças poderão ter.
*/

	init_pair(3,3,3);
	init_pair(4,4,4);
	init_pair(5,5,5);
	init_pair(6,6,6);
	init_pair(7,7,7);
	init_pair(2,COLOR_BLACK,COLOR_BLACK);

/**
*   Laços que percorrem todas a matriz imprimindo o tabuleiro
*/

	for(linha=0;linha<NUM_LINHAS;linha++){
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			if(tabuleiro[linha][coluna]!=0){
				attrset(COLOR_PAIR(tabuleiro[linha][coluna]));
				mvaddch(linha+POS_L, coluna+POS_C,' ');
			}else{
				attrset(COLOR_PAIR(2));
				mvaddch(linha+POS_L, coluna+POS_C,' ');
			}

			
		}
	}
	attrset(COLOR_PAIR(2));
	refresh();
}

void imprime_tela_status(int pontuacao){
	
	WINDOW *my_win;
	int startx, starty, width, height;
	int ch;

	startx = 40;
	starty = 5;

	height = 3;
	width = 20;
	my_win = newwin(height,width,starty,startx);
	box(my_win,0,0);
	mvwprintw(my_win,1,3,"Pontuacao: %d",pontuacao);
	wrefresh(my_win);
	
}
