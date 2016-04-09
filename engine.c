#include <ncurses.h>
#include "pecas.h"
#include "parametros.h"

/*
* Finaliza ncurses. 
*
*/
void inicia_ncurses(){
	initscr();
	start_color();
}

/*
* Inicializa ncurses. 
*
*/
void finaliza_ncurses(){	
	endwin();
}

/*
* Pega entrada no usuario. 
*
*/
int pega_input(){

	return getchar();
}
/*
* Desenha peça atual no tabuleiro. 
*
*/
void insere_peca_tabuleiro(int tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA peca){
	if(peca.tipo == RETA_VERTICAL){
		int linha;
		for(linha = 0; linha< peca.tamanho; linha++){
			tabuleiro[linha][peca.pos_coluna] = peca.cor;
		}
	}
	if(peca.tipo == RETA_HORIZONTAL){
		int coluna;
		for(coluna = peca.pos_coluna; coluna< peca.tamanho + peca.pos_coluna; coluna++){
			tabuleiro[peca.pos_linha][coluna] = peca.cor;
		}
	}
}

/*
* Faz o movimento da peça atual para esquerda. 
*
*/
void move_peca_para_esquerda(int tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA* peca){
	if(peca->tipo == RETA_VERTICAL){
		if(peca->pos_coluna == 0)
			return;
		int linha;
		for(linha = peca->pos_linha; linha< peca->tamanho + peca->pos_linha; linha++){
			if(tabuleiro[linha][peca->pos_coluna-1] != 0){
				return;
			}
		}
		for(linha = peca->pos_linha; linha< peca->tamanho + peca->pos_linha; linha++){
			tabuleiro[linha][peca->pos_coluna-1] = tabuleiro[linha][peca->pos_coluna];
			tabuleiro[linha][peca->pos_coluna] = 0;

		}
	}
	if(peca->tipo == RETA_HORIZONTAL){
		if(peca->pos_coluna == 0){
			return;
		}
		if(tabuleiro[peca->pos_linha][peca->pos_coluna-1] == 0){
			tabuleiro[peca->pos_linha][peca->pos_coluna-1] = tabuleiro[peca->pos_linha][peca->pos_coluna + peca->tamanho -1];
			tabuleiro[peca->pos_linha][peca->pos_coluna + peca->tamanho -1] = 0;
		}else{
			return;
		}
	}
	peca->pos_coluna--;
}

/*
* Faz o movimento da peça atual para direita. 
*
*/
void move_peca_para_direita(int tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA* peca){
	if(peca->tipo == RETA_VERTICAL){
		if(peca->pos_coluna > NUM_COLUNAS-2){
			return;
		}
		int linha;
		for(linha = peca->pos_linha; linha< peca->tamanho+peca->pos_linha; linha++){
			if(tabuleiro[linha][peca->pos_coluna+1] != 0){
				return;
			}
		}
		for(linha = peca->pos_linha; linha< peca->tamanho+peca->pos_linha; linha++){
			tabuleiro[linha][peca->pos_coluna+1] = tabuleiro[linha][peca->pos_coluna];
			tabuleiro[linha][peca->pos_coluna] = 0;

		}
	}
	if(peca->tipo == RETA_HORIZONTAL){
		if(peca->pos_coluna + peca->tamanho > NUM_COLUNAS-1){
			return;
		}
		if(tabuleiro[peca->pos_linha][peca->pos_coluna+ peca->tamanho] == 0){
			tabuleiro[peca->pos_linha][peca->pos_coluna + peca->tamanho] = tabuleiro[peca->pos_linha][peca->pos_coluna];
			tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;
			
		}else{
			return;
		}
	}
	peca->pos_coluna++;
}

/*
* Faz o movimento da peça atual para baixo. 
*
*/
void move_peca_para_baixo(int tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA* peca){
	if(peca->tipo == RETA_VERTICAL){
		if(peca->pos_linha + peca->tamanho >= NUM_LINHAS)
			return;
		if(tabuleiro[peca->pos_linha + peca->tamanho][peca->pos_coluna] != 0)
			return;
		tabuleiro[peca->pos_linha + peca->tamanho][peca->pos_coluna] = tabuleiro[peca->pos_linha][peca->pos_coluna];
		tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;
	}
	if(peca->tipo == RETA_HORIZONTAL){
		if(peca->pos_linha  > NUM_LINHAS-1){
			return;
		}
		int coluna;
		for(coluna = peca->pos_coluna; coluna < peca->pos_coluna + peca->tamanho; coluna++){
			if(tabuleiro[peca->pos_linha+1][coluna] != 0){
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

/*
* Verifica se a peça atual chegou no final do tabuleiro ou encostou em outra peça.
* Caso verdadeiro, a peça fica FIXA.
*/

void verifica_peca_em_jogo(int tabuleiro[NUM_LINHAS][NUM_COLUNAS], PECA* peca){
	if(peca->tipo == RETA_VERTICAL){
		if(peca->pos_linha + peca->tamanho >= NUM_LINHAS)
			peca->status = FIXA;
		if(tabuleiro[peca->pos_linha + peca->tamanho][peca->pos_coluna] != 0)
			peca->status = FIXA;
	}
	if(peca->tipo == RETA_HORIZONTAL){
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

/*
* Verifica se na linha 6 existe alguma peça, caso exista o jogo acaba.
*
*/

int verifica_fim_de_jogo(int tabuleiro[NUM_LINHAS][NUM_COLUNAS]){
	int coluna;
	for(coluna = 0; coluna < NUM_COLUNAS; coluna++){
		if(tabuleiro[5][coluna] != 0){
			return 1;
		}
	}
	return 0;
}

/**
*   Função que recebe com parâmetro o tabuleiro e verifica se alguma das linhas está completa. Retorna a pontuação feita naquela rodada ( 100 pontos para cada linha)
*/


int pontua(int tabuleiro[NUM_LINHAS][NUM_COLUNAS]){

	int linha,coluna,contador_peca=0,buffer_cor_peca,pontuacao = 0 ;

	for(linha=0;linha<NUM_LINHAS;linha++){
		contador_peca = 0;
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			if(tabuleiro[linha][coluna] != 0){
				buffer_cor_peca = tabuleiro[linha][coluna];
				contador_peca++;
			}
		}
		if(contador_peca==NUM_COLUNAS){
			desce_todas_linhas(tabuleiro,linha);
			pontuacao = pontuacao+100;

		}
	}
	
	return pontuacao;
}


/**
*   Função que transforma todas as colunas de uma linhas completa em zeros. Na versão do primeiro trabalho, essa ação não poderá ser visualizada. Porém quando as funções de tempo forem implementadas,
*   a "limpeza" poderá ser visualizada.
*
*/
void limpa_linha(int tabuleiro[NUM_LINHAS][NUM_COLUNAS],int linha){
	int coluna;
	for(coluna=0;coluna<NUM_COLUNAS;coluna++){
		tabuleiro[linha][coluna] = 0;
		
	}
}

/**
*     Função que faz com que todas as linhas, acima da linha
*
*/


void desce_linha(int tabuleiro[NUM_LINHAS][NUM_COLUNAS],int linha){

	int coluna;

	for (coluna=0;coluna<NUM_COLUNAS;coluna++){
		tabuleiro[linha][coluna] = tabuleiro[linha-1][coluna];
	}

}

void desce_todas_linhas(int tabuleiro[NUM_LINHAS][NUM_COLUNAS],int linha){

	int linha_temp,coluna,i=0;
	limpa_linha(tabuleiro,linha);

	i=linha;
	while(i>6){
		desce_linha(tabuleiro,i);
		i--;	
	}

}