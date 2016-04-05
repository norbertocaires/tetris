#include "parametros.h"

void inicia_ncurses();
void finaliza_ncurses();
int pega_input();

void insere_peca_tabuleiro(char tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA peca);

/* Movimentos das pecas */
void move_peca_para_esquerda(char tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA* peca);
void move_peca_para_direita(char tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA* peca);
void move_peca_para_baixo(char tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA* peca);

void verifica_peca_em_jogo(char tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA* peca);
int verifica_fim_de_jogo(char tabuleiro[NUM_LINHAS][NUM_COLUNAS]);
