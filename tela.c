#include <time.h>
#include <ncurses.h>
#include "parametros.h"
#include "pecas.h"

void imprime_borda_tela(){
	border(0, 0, 0, 0, 0, 0, 0, 0);
	refresh();
}

void imprime_tela_inicial(){

	int i,j;

	start_color();
	init_pair(9,COLOR_GREEN,COLOR_GREEN);
	init_pair(10,COLOR_WHITE,COLOR_GREEN);
	init_pair(11,COLOR_BLACK,COLOR_BLACK);
	init_pair(12,COLOR_WHITE,COLOR_BLACK);
	attrset(COLOR_PAIR(9));

	for (i=1;i<(LINES-1);i++){
		for(j=1;j<(COLS-1);j++){
			mvaddch(i, j,'A');
		}
	}

	attrset(COLOR_PAIR(10));
	move(3,10);
	printw("...::: BEM VINDO AO TETRIS :::...");
	move(6,3);
	printw("...::: PRESSIONE ALGUMA TECLA PARA INICIAR O JOGO :::...");
	getch();
	getch();
	attrset(COLOR_PAIR(11));
	for (i=1;i<(LINES-1);i++){
		for(j=1;j<(COLS-1);j++){
			mvaddch(i, j,' ');
		}
	}
	attrset(COLOR_PAIR(12));
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

	startx = 30 + POS_C;
	starty = POS_L;

	height = 3;
	width = 20;
	my_win = newwin(height,width,starty,startx);
	box(my_win,0,0);
	mvwprintw(my_win,1,3,"Pontuacao: %d",pontuacao);
	wrefresh(my_win);
	
}

void imprime_tela_final(PECAS* lista_qtd_cada_peca, int pontuacao, time_t hora_inicio,time_t hora_final){
	int i,j;

	start_color();
	init_pair(9,COLOR_RED,COLOR_RED);
	init_pair(10,COLOR_WHITE,COLOR_RED);
	init_pair(11,COLOR_BLACK,COLOR_BLACK);
	init_pair(12,COLOR_WHITE,COLOR_BLACK);
	attrset(COLOR_PAIR(9));

	for (i=1;i<(LINES-1);i++){
		for(j=1;j<(COLS-1);j++){
			mvaddch(i, j,'A');
		}
	}

	attrset(COLOR_PAIR(10));
	move(3,14);
	printw("...::: FIM DE JOGO :::...");
	PECA* peca = lista_qtd_cada_peca->primeiro;
	int linha = 7;
	move(5,10);
	printw("QUANTIDADE DE CADA PECA:");
	while(peca != NULL){
		move(linha,10);
		if(peca->tipo == RETA_VERTICAL){
			printw("| RETA VERTICAL\t| TAMANHO: %i \t| QUANTIDADE: %i", peca->tamanho, peca->qtd );
		}
		if(peca->tipo == RETA_HORIZONTAL){
			printw("| RETA HORIZONTAL\t| TAMANHO: %i \t| QUANTIDADE: %i", peca->tamanho, peca->qtd );
		}
		linha += 1;
		peca = peca->proximo;
	}

	struct tm inicio = *localtime (&hora_inicio);
	struct tm fim = *localtime (&hora_final);

	move(LINES-9,25);
	printw("HORA INCIO: %d:%d:%d", inicio.tm_hour, inicio.tm_min, inicio.tm_sec);

	move(LINES-8,25);
	printw("HORA FIM: %d:%d:%d", fim.tm_hour, fim.tm_min, fim.tm_sec);

	int diferenca = (int)difftime(hora_final, hora_inicio);
	
	int segundos = diferenca%60;
	int minutos = diferenca/60;
	int horas = diferenca/60/60;

	move(LINES-7,25);
	printw("TEMPO DE JOGO: %d:%d:%d", horas, minutos%60, segundos);

	move(LINES-6,25);
	printw("PONTUACAO FINAL: %i", pontuacao);

	move(LINES-3,10);
	printw("...::: PRESSIONE ALGUMA TECLA PARA FINALIZAR :::...");
	getch();
}
