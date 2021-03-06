#ifndef _tela_h
#define _tela_h

#include <time.h>
#include "parametros.h"

void imprime_tabuleiro_com_borda(int tabuleiro[][NUM_COLUNAS]);
void imprime_tabuleiro_sem_borda(int tabuleiro[][NUM_COLUNAS]);
void imprime_borda_tabuleiro();

void imprime_borda_tela();

void imprime_tela_final(PECAS* lista_qtd_cada_peca, int pontuacao, time_t hora_inicio,time_t hora_final);
void imprime_tela_inicial();

void imprime_tela_status(int pontuacao);

#endif
