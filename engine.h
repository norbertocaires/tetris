#include "parametros.h"

void inicia_ncurses();
void finaliza_ncurses();
int pega_input();

void insere_peca_tabuleiro(int tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA peca);

/* Movimentos das pecas */
void move_peca_para_esquerda(int tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA* peca);
void move_peca_para_direita(int tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA* peca);
void move_peca_para_baixo(int tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA* peca);

void verifica_peca_em_jogo(int tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA* peca);
int verifica_fim_de_jogo(int tabuleiro[NUM_LINHAS][NUM_COLUNAS]);
