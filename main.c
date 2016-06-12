#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#include "pecas.h"
#include "engine.h"
#include "tela.h"
#include "parametros.h"


int tabuleiro[NUM_LINHAS][NUM_COLUNAS];

// PECA CORRENTE (ultima da lista de pecas)
PECA* peca;
	
pthread_t thread;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // lock para as partes criticas

PECAS pecas;
int pontuacao = 0;
int fim_jogo = 0;

int velocidade = 1;

/*
* Faz o movimento da peça atual a cada 1 segundo para baixo. 
*
*/
void *move_peca_um_segundo(){
	while(fim_jogo == 0){
		int time = 1000000;
		velocidade = 1;
		pthread_mutex_lock(&lock);
		if(peca->status == FIXA && fim_jogo == 0){
			peca = gera_peca();
			adiciona_peca_lista(&pecas, peca);
			insere_peca_tabuleiro(tabuleiro, peca);
			imprime_tabuleiro_sem_borda(tabuleiro);
		}
		pthread_mutex_unlock(&lock);
		while(peca->status == EM_JOGO){
			usleep(time / velocidade);
			pthread_mutex_lock(&lock);
			move_peca_para_baixo(tabuleiro, peca);
			imprime_tabuleiro_sem_borda(tabuleiro);
			verifica_peca_em_jogo(tabuleiro, peca);
			pthread_mutex_unlock(&lock);
		}
		pthread_mutex_lock(&lock);
		pontuacao = pontuacao + pontua(tabuleiro);
		imprime_tela_status(pontuacao);
		fim_jogo = verifica_fim_de_jogo(tabuleiro);
		pthread_mutex_unlock(&lock);
	}	
}


int main(){
	char input; 
	PECAS lista_qtd_cada_peca;
	time_t hora_inicio, hora_final;

	//LISTA DE PECAS
	inicializa_lista(&pecas);

	//LISTA DE QTD PECAS
	inicializa_lista(&lista_qtd_cada_peca);

	memset(tabuleiro, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));

	inicia_ncurses();
	 	
	imprime_borda_tela();
	imprime_tela_inicial();
	imprime_borda_tabuleiro();
	imprime_tela_status(pontuacao);

	hora_inicio = time(NULL);
	peca = gera_peca();
	insere_peca_tabuleiro(tabuleiro, peca);
	imprime_tabuleiro_sem_borda(tabuleiro);
	adiciona_peca_lista(&pecas, peca);
	pthread_create(&thread, NULL, move_peca_um_segundo, NULL);

	while(fim_jogo == 0){
		while(peca->status == EM_JOGO){
			input = pega_input();
			if(input == 'D'){//26
				pthread_mutex_lock(&lock);
				move_peca_para_esquerda(tabuleiro, peca);
				pthread_mutex_unlock(&lock);
			}
			if(input == 'C'){//27
				pthread_mutex_lock(&lock);
				move_peca_para_direita(tabuleiro, peca);
				pthread_mutex_unlock(&lock);
			}
			if(input == 'B'){//28
				pthread_mutex_lock(&lock);
				move_peca_para_baixo(tabuleiro, peca);
				velocidade = velocidade * 2;
				pthread_mutex_unlock(&lock);
			}
			if(input == 'A'){//28
				pthread_mutex_lock(&lock);
				gira_peca_noventa_graus(tabuleiro, peca);
				pthread_mutex_unlock(&lock);
			}
			pthread_mutex_lock(&lock);
			verifica_peca_em_jogo(tabuleiro, peca);
			imprime_tabuleiro_sem_borda(tabuleiro);
			pthread_mutex_unlock(&lock);
		}

		pthread_mutex_lock(&lock);
		pontuacao = pontuacao + pontua(tabuleiro);
		imprime_tela_status(pontuacao);

		fim_jogo = verifica_fim_de_jogo(tabuleiro);

		if(peca->status == FIXA && fim_jogo == 0){
			peca = gera_peca();
			adiciona_peca_lista(&pecas, peca);
			insere_peca_tabuleiro(tabuleiro, peca);
			imprime_tabuleiro_sem_borda(tabuleiro);
		}

		pthread_mutex_unlock(&lock);
	}
	pthread_join(thread, NULL); 
	hora_final =  time(NULL);
	
	gera_lista_de_qtds(&pecas, &lista_qtd_cada_peca);
	imprime_tela_final(&lista_qtd_cada_peca, pontuacao, hora_inicio, hora_final);

	finaliza_ncurses();
	return 0;
}
