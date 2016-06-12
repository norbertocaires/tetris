#include <time.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "parametros.h"
#include "pecas.h"
#include "placar.h"



/**
*    Função que imprime as bordas da tela
*/
void imprime_borda_tela(){
	border(0, 0, 0, 0, 0, 0, 0, 0);
	refresh();
}


/**
*    Função que imprime tela inicial. Definido a cor de fundo e fazendo com que o programa fique aguardando 
* 	qualquer entrada no teclado para iniciar o jogo.
*/
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
			mvaddch(i, j, (chtype) 'A');
		}
	}

	attrset(COLOR_PAIR(10));
	move(3,10);
	printw("...::: BEM VINDO AO TETRIS :::...");
	move(6,3);
	printw("...::: PRESSIONE ALGUMA TECLA PARA INICIAR O JOGO :::...");
	getch();
	attrset(COLOR_PAIR(11));
	for (i=1;i<(LINES-1);i++){
		for(j=1;j<(COLS-1);j++){
			mvaddch(i, j, (chtype) ' ');
		}
	}
	attrset(COLOR_PAIR(12));
}

/**
*    Função que imprime as bordas do tabuleiro.
*/

void imprime_borda_tabuleiro(){
	int linha, coluna;
	for(linha=0;linha<NUM_LINHAS;linha++){
		if(linha+5 != 10){
			mvaddch(linha+POS_L, POS_C-1, (chtype) '|');
			mvaddch(linha+POS_L, NUM_COLUNAS+POS_C, (chtype) '|');
		}else{
			mvaddch(linha+POS_L, POS_C-1, (chtype) '*');
			mvaddch(linha+POS_L, NUM_COLUNAS+POS_C, (chtype) '*');
		}
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			mvaddch(4, coluna+POS_C, (chtype) '_');
			mvaddch(NUM_LINHAS+POS_L, coluna+POS_C, (chtype) '*');
		}
	}
	refresh();
}
/**
*    Função que imprime somente a parte interna do tabuleiro.
*/
void imprime_tabuleiro_sem_borda(int tabuleiro[][NUM_COLUNAS]){
	int linha, coluna;

//   Inicialização dos "pairs" que serão utilizados para colorir as peças.
//   Cada um desses pares é uma das cores que as peças poderão ter.


	init_pair(3,3,3);
	init_pair(4,4,4);
	init_pair(5,5,5);
	init_pair(6,6,6);
	init_pair(7,7,7);
	init_pair(2,COLOR_BLACK,COLOR_BLACK);

//
//   Laços que percorrem todas a matriz imprimindo o tabuleiro
//

	for(linha=0;linha<NUM_LINHAS;linha++){
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			if(tabuleiro[linha][coluna]!=0){
				attrset(COLOR_PAIR(tabuleiro[linha][coluna]));
				mvaddch(linha+POS_L, coluna+POS_C, (chtype) ' ');
			}else{
				attrset(COLOR_PAIR(2));
				mvaddch(linha+POS_L, coluna+POS_C, (chtype) ' ');
			}

			
		}
	}
	attrset(COLOR_PAIR(2));
	refresh();
}
/*
*  Imprime e uma pequena tela auxiliar, ao lado do tabuleiro de jogo, contendo a pontuação do jogador.
* @param pontuacao: Recebe a pontuação que será exibida.
*/
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


/*
* Após o fim do jogo, serão exibidas as informações sobre a performande do jogador (pontuação, tempo de jogo e etc.)
* Será, também, requerido ao jogado escrever seu nome e, se for o caso, incluído no placar com as melhores pontuacoes.
*/
void imprime_tela_final(PECAS* lista_qtd_cada_peca, int pontuacao, time_t hora_inicio,time_t hora_final){
	LISTA_PONTUACAO *lista_pontuacao;
	int i, j, linha, diferenca, segundos, minutos, horas;
	char nome[TAM_NOME];
	char tempoJogo [100];
	PONTUACAO *pontuacao_aux;
	PECA* peca;
	struct tm inicio;
	struct tm fim;

	start_color();
	init_pair(9,COLOR_RED,COLOR_RED);
	init_pair(10,COLOR_WHITE,COLOR_RED);
	init_pair(11,COLOR_BLACK,COLOR_BLACK);
	init_pair(12,COLOR_WHITE,COLOR_BLACK);
	attrset(COLOR_PAIR(9));

	for (i=1;i<(LINES-1);i++){
		for(j=1;j<(COLS-1);j++){
			mvaddch(i, j, (chtype)'A');
		}
	}

	attrset(COLOR_PAIR(10));
	move(3,14);
	printw("...::: FIM DE JOGO :::...");
	peca = lista_qtd_cada_peca->primeiro;
	linha = 7;
	move(5,10);
	printw("QUANTIDADE DE CADA PECA:");
	while(peca != NULL){
		move(linha,10);
		if(peca->tipo == 10){
			printw("| RETA\t| QUANTIDADE: %i", peca->qtd );
		}
		if(peca->tipo == PECA_Z){
			printw("| PECA Z\t| QUANTIDADE: %i", peca->qtd );
		}
		if(peca->tipo == PECA_T){
			printw("| PECA T\t| QUANTIDADE: %i", peca->qtd );
		}

		if(peca->tipo == PECA_QUADRADO){
			printw("| QUADRADO\t| QUANTIDADE: %i", peca->qtd );
		}

		if(peca->tipo == PECA_L){
			printw("| PECA L\t| QUANTIDADE: %i", peca->qtd );
		}

		linha += 1;
		peca = peca->proximo;
	}

	inicio = *localtime (&hora_inicio);
	fim = *localtime (&hora_final);

	move(LINES-9,25);
	printw("HORA INCIO: %d:%d:%d", inicio.tm_hour, inicio.tm_min, inicio.tm_sec);

	move(LINES-8,25);
	printw("HORA FIM: %d:%d:%d", fim.tm_hour, fim.tm_min, fim.tm_sec);

	diferenca = (int)difftime(hora_final, hora_inicio);
	
	segundos = diferenca%60;
	minutos = diferenca/60;
	horas = diferenca/60/60;

	move(LINES-7,25);
	printw("TEMPO DE JOGO: %d:%d:%d", horas, minutos%60, segundos);
	sprintf(tempoJogo,"%d:%d:%d", horas, minutos%60, segundos);

	move(LINES-6,25);
	printw("PONTUACAO FINAL: %d", pontuacao);

	move(LINES-3,10);
	printw("...::: PRESSIONE ALGUMA TECLA PARA FINALIZAR :::...");
	getch(); getch();

		attrset(COLOR_PAIR(9));

/* Apresenta o placar */

//Limpa a tela
	for (i=1;i<(LINES-1);i++){
		for(j=1;j<(COLS-1);j++){
			mvaddch(i, j, (chtype) 'A');
		}
	}
	
// Recebe o nome do usuario
	attrset(COLOR_PAIR(10));
	move(3,10);
	printw("Digite seu nome: ");
	move(5,10);
	printw("Serao gravadas as 10 primeiras letras");
	move(3,28);
	getstr(nome);
	
	
// Apresenta o placar
	//O argumento diz se vai carregar o arquivo de teste ou nao
	lista_pontuacao = carrega_placar(FALSO);
	
	if (lista_pontuacao->primeira_pontuacao == NULL){// FIca repetido pois as verifciacoes do else if estava dando segmentation fault

		pontuacao_aux = malloc(sizeof(PONTUACAO));
		sprintf(pontuacao_aux->nome,"%s",nome);
		pontuacao_aux->pontos = pontuacao;
		sprintf(pontuacao_aux->data,"%s",data());
		sprintf(pontuacao_aux->tempo,"%s",tempoJogo);
		adiciona_lista_pontuacao(lista_pontuacao,pontuacao_aux);

	}else if(pontuacao > lista_pontuacao->ultima_pontuacao->pontos || lista_pontuacao->qtd_pontuacoes < 5 ){
		pontuacao_aux = malloc(sizeof(PONTUACAO));
		sprintf(pontuacao_aux->nome,"%s",nome);
		pontuacao_aux->pontos = pontuacao;
		sprintf(pontuacao_aux->data,"%s",data());
		sprintf(pontuacao_aux->tempo,"%s",tempoJogo);
		adiciona_lista_pontuacao(lista_pontuacao,pontuacao_aux);
	}

	lista_pontuacao->pontuacao_atual = lista_pontuacao->primeira_pontuacao;
	i =10;
	while(lista_pontuacao->pontuacao_atual->proximo != NULL){
		move(i,10);
		printw("Nome: %s pontuacao: %d", lista_pontuacao->pontuacao_atual->nome,lista_pontuacao->pontuacao_atual->pontos);
		lista_pontuacao->pontuacao_atual = lista_pontuacao->pontuacao_atual->proximo;
		i++;
	}

	move(i,10);
	printw("Nome: %s pontuacao: %d", lista_pontuacao->pontuacao_atual->nome,lista_pontuacao->pontuacao_atual->pontos);
	lista_pontuacao->pontuacao_atual = lista_pontuacao->primeira_pontuacao;
	
	escreve_placar(lista_pontuacao);
	
	getch();getch();



}
