#include "parametros.h"

void inicia_ncurses();
void finaliza_ncurses();
char pega_input();

void insere_peca_tabuleiro(char tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA peca);

/* Movimentos das pecas */
void move_peca_para_esquerda(char tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA* peca);
void move_peca_para_direita(char tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA* peca);
void move_peca_para_baixo(char tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA* peca);
