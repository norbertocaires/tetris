
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "parametros.h"
#include "testeEngine.h"
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "pecas.h"
#include "engine.h"

int tab[NUM_LINHAS][NUM_COLUNAS];

PECA* gera_peca_horizontal(int tamanho){
	PECA* peca = malloc(sizeof(PECA));
	peca->status = EM_JOGO;
	peca->pos_linha = 0;
	if(tamanho == 3)
		peca->pos_coluna = 13 - 1;
	else
		peca->pos_coluna = 13 - 2;
	peca->tipo = RETA_HORIZONTAL;
	peca->tamanho = tamanho;
	peca->cor = 100;

	peca->tamanho = tamanho;
	peca->rotacao = 0;
	peca->proximo = NULL;
	peca->qtd = 0;

	return peca;
}

PECA* gera_peca_vertical(int tamanho){
	PECA* peca = malloc(sizeof(PECA));
	peca->status = EM_JOGO;
	peca->pos_linha = 0;
	peca->pos_coluna = 13;
	peca->tipo = RETA_VERTICAL;
	peca->tamanho = tamanho;
	peca->cor = 100;

	peca->tamanho = tamanho;
	peca->rotacao = 0;
	peca->proximo = NULL;
	peca->qtd = 0;

	return peca;
}

PECA* gera_peca_teste_engine(int tipo, int tamanho, int rotacao){
	PECA* peca = malloc(sizeof(PECA));
	peca->status = EM_JOGO;
	peca->pos_linha = 0;
	peca->pos_coluna = 13;
	peca->tipo = tipo;
	peca->tamanho = tamanho;
	peca->cor = 100;

	peca->rotacao = rotacao;
	peca->proximo = NULL;
	peca->qtd = 0;

	return peca;
}

/**
* Testa função que ferifica fim de jogo
*
*/
void testa_fim_de_jogo(void){

	int coluna;

	memset(tab, 3, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	CU_ASSERT_TRUE( verifica_fim_de_jogo(tab) == 1 );

	for(coluna=0;coluna<NUM_COLUNAS;coluna++){
		memset(tab, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
		tab[5][coluna] = 3;
		CU_ASSERT_TRUE( verifica_fim_de_jogo(tab) == 1 );
	}
}


/**
* Testa função que pontua a cada linha preenchida 
*
*/

void testa_pontua(void){
	int linha, coluna;
	memset(tab, 3, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	CU_ASSERT_TRUE( pontua(tab) == NUM_LINHAS * 100 );

	memset(tab, 3, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	for(linha=0;linha<NUM_LINHAS;linha++){
		tab[linha][0] = 0;
	}
	CU_ASSERT_TRUE( pontua(tab) == 0 );

	memset(tab, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	for(coluna=0;coluna<NUM_COLUNAS;coluna++){
		tab[NUM_LINHAS-1][coluna] = 3;
	}
	CU_ASSERT_TRUE( pontua(tab) == 100 );

	memset(tab, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	for(linha=NUM_LINHAS-1;linha>NUM_LINHAS-6;linha--){
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			tab[linha][coluna] = 3;
		}
	}
	CU_ASSERT_TRUE( pontua(tab) == 500 );

}

/**
* Testa a insercao de uma reta HORIZONTAL TAMANHO variavel
*
*/

void teste_insere_reta_horizontal(int tamanho){
	PECA* peca;
	int qtd_100, qtd_0;
	int coluna, linha;
	
	memset(tab, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	peca = gera_peca_horizontal(tamanho);

	insere_peca_tabuleiro(tab,peca);
	for(coluna = peca->pos_coluna; coluna< peca->tamanho + peca->pos_coluna; coluna++){
		CU_ASSERT_TRUE( tab[peca->pos_linha][coluna] == 100 );
	}
	qtd_100 = 0, qtd_0 = 0;
	for(linha=0;linha<NUM_LINHAS;linha++){
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			if(tab[linha][coluna] == 100)
				qtd_100++;
			else
				qtd_0++;
		}
	}
	CU_ASSERT_TRUE( qtd_0 == (NUM_LINHAS*NUM_COLUNAS) - tamanho );
	CU_ASSERT_TRUE( qtd_100 == tamanho );
	verifica_peca_em_jogo(tab, peca);
	CU_ASSERT_TRUE( peca->status == EM_JOGO );
}

void teste_insere_peca(int tipo_peca, int tamanho){
	PECA* peca;
	int qtd_100, qtd_0;
	int coluna, linha;
	
	memset(tab, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	peca = gera_peca_teste_engine(tipo_peca, tamanho, 0);

	insere_peca_tabuleiro(tab,peca);
	qtd_100 = 0, qtd_0 = 0;
	for(linha=0;linha<NUM_LINHAS;linha++){
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			if(tab[linha][coluna] == 100)
				qtd_100++;
			else
				qtd_0++;
		}
	}
	CU_ASSERT_TRUE( qtd_0 == (NUM_LINHAS*NUM_COLUNAS) - tamanho );
	CU_ASSERT_TRUE( qtd_100 == tamanho );
	verifica_peca_em_jogo(tab, peca);
	CU_ASSERT_TRUE( peca->status == EM_JOGO );
}

void teste_insere_reta_horizontal_tamanho_3(void){
	teste_insere_reta_horizontal(3);
}

void teste_insere_reta_horizontal_tamanho_4(void){
	teste_insere_reta_horizontal(4);
}

void teste_insere_reta_horizontal_tamanho_5(void){
	teste_insere_reta_horizontal(5);
}
void teste_insere_Z(void){
	teste_insere_peca(PECA_Z, 5);
}

void teste_insere_T(void){
	teste_insere_peca(PECA_T, 7);
}

void teste_insere_L(void){
	teste_insere_peca(PECA_L, 5);
}

void teste_insere_quadrado(void){
	teste_insere_peca(PECA_QUADRADO, 4);
}

/**
* Testa a insercao de uma reta VERTICAL TAMANHO varivel
*
*/

void teste_insere_reta_vertical(int tamanho){
	PECA* peca;
	int coluna, linha;
	int qtd_100, qtd_0;

	memset(tab, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	peca = gera_peca_vertical(tamanho);

	insere_peca_tabuleiro(tab,peca);

	for(linha = 0; linha< peca->tamanho; linha++){
		CU_ASSERT_TRUE( tab[linha][peca->pos_coluna] == 100 );
	}

	qtd_100 = 0, qtd_0 = 0;
	for(linha=0;linha<NUM_LINHAS;linha++){
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			if(tab[linha][coluna] == 100)
				qtd_100++;
			else
				qtd_0++;
		}
	}
	CU_ASSERT_TRUE( qtd_0 == (NUM_LINHAS*NUM_COLUNAS) - tamanho );
	CU_ASSERT_TRUE( qtd_100 == tamanho );
	verifica_peca_em_jogo(tab, peca);
	CU_ASSERT_TRUE( peca->status == EM_JOGO );
}

void teste_insere_reta_vertical_tamanho_3(void){
	teste_insere_reta_vertical(3);
}
void teste_insere_reta_vertical_tamanho_4(void){
	teste_insere_reta_vertical(4);
}
void teste_insere_reta_vertical_tamanho_5(void){
	teste_insere_reta_vertical(5);
}

/**
* Testa mover esquerda uma reta HORIZONTAL TAMANHO variavel
*
*/

void teste_move_peca_para_esquerda_horizontal(int tamanho){
	PECA* peca;
	int coluna, linha;
	int qtd_100 = 0, qtd_0 = 0;

	memset(tab, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	peca = gera_peca_horizontal(tamanho);

	insere_peca_tabuleiro(tab,peca);
	move_peca_para_esquerda(tab, peca);


	for(coluna = peca->pos_coluna; coluna< peca->tamanho + peca->pos_coluna; coluna++){
		CU_ASSERT_TRUE( tab[peca->pos_linha][coluna] == 100 );
	}


	for(linha=0;linha<NUM_LINHAS;linha++){
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			if(tab[linha][coluna] == 100)
				qtd_100++;
			else
				qtd_0++;
		}
	}
	CU_ASSERT_TRUE( qtd_0 == (NUM_LINHAS*NUM_COLUNAS) - tamanho );
	CU_ASSERT_TRUE( qtd_100 == tamanho );
	verifica_peca_em_jogo(tab, peca);
	CU_ASSERT_TRUE( peca->status == EM_JOGO );
}

void teste_move_peca_para_esquerda_horizontal_tamanho_3(void){
	teste_move_peca_para_esquerda_horizontal(3);
}

void teste_move_peca_para_esquerda_horizontal_tamanho_4(void){
	teste_move_peca_para_esquerda_horizontal(4);
}

void teste_move_peca_para_esquerda_horizontal_tamanho_5(void){
	teste_move_peca_para_esquerda_horizontal(5);
}

/**
* Testa mover esquerda até borda uma reta HORIZONTAL TAMANHO variavel
*
*/

void teste_move_peca_para_esquerda_ate_borda_horizontal(int tamanho){
	PECA* peca;
	int i;
	int qtd_100 = 0, qtd_0 = 0;
	int coluna, linha;

	memset(tab, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	peca = gera_peca_horizontal(tamanho);

	insere_peca_tabuleiro(tab,peca);

	while(i<NUM_COLUNAS){
		move_peca_para_esquerda(tab, peca);
		i++;
	}

	for(coluna = peca->pos_coluna; coluna< peca->tamanho + peca->pos_coluna; coluna++){
		CU_ASSERT_TRUE( tab[peca->pos_linha][coluna] == 100 );
	}

	for(linha=0;linha<NUM_LINHAS;linha++){
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			if(tab[linha][coluna] == 100)
				qtd_100++;
			else
				qtd_0++;
		}
	}
	CU_ASSERT_TRUE( qtd_0 == (NUM_LINHAS*NUM_COLUNAS) - tamanho );
	CU_ASSERT_TRUE( qtd_100 == tamanho );
	verifica_peca_em_jogo(tab, peca);
	CU_ASSERT_TRUE( peca->status = EM_JOGO );
}

void teste_move_peca_para_esquerda_ate_borda_horizontal_tamanho_3(void){
	teste_move_peca_para_esquerda_ate_borda_horizontal(3);
}

void teste_move_peca_para_esquerda_ate_borda_horizontal_tamanho_4(void){
	teste_move_peca_para_esquerda_ate_borda_horizontal(4);
}

void teste_move_peca_para_esquerda_ate_borda_horizontal_tamanho_5(void){
	teste_move_peca_para_esquerda_ate_borda_horizontal(5);
}

/**
* Testa mover esquerda uma reta VERTICAL TAMANHO vaiavel
*
*/

void teste_move_peca_para_esquerda_vertical(int tamanho){
	PECA* peca;
	int coluna, linha;
	int qtd_100 = 0, qtd_0 = 0;

	memset(tab, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	peca = gera_peca_vertical(tamanho);

	insere_peca_tabuleiro(tab,peca);
	move_peca_para_esquerda(tab, peca);


	for(linha = 0; linha< peca->tamanho; linha++){
		CU_ASSERT_TRUE( tab[linha][peca->pos_coluna] == 100 );
	}

	for(linha=0;linha<NUM_LINHAS;linha++){
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			if(tab[linha][coluna] == 100)
				qtd_100++;
			else
				qtd_0++;
		}
	}
	CU_ASSERT_TRUE( qtd_0 == (NUM_LINHAS*NUM_COLUNAS) - tamanho );
	CU_ASSERT_TRUE( qtd_100 == tamanho );
	verifica_peca_em_jogo(tab, peca);
	CU_ASSERT_TRUE( peca->status == EM_JOGO );
}

void teste_move_peca_para_esquerda_vertical_tamanho_3(void){
	teste_move_peca_para_esquerda_vertical(3);
}

void teste_move_peca_para_esquerda_vertical_tamanho_4(void){
	teste_move_peca_para_esquerda_vertical(4);
}

void teste_move_peca_para_esquerda_vertical_tamanho_5(void){
	teste_move_peca_para_esquerda_vertical(5);
}

/**
* Testa mover esquerda ate borda uma reta VERTICAL TAMANHO vaiavel
*
*/

void teste_move_peca_para_esquerda_ate_borda_vertical(int tamanho){
	PECA* peca;
	int i =0;
	int coluna, linha;
	int qtd_100 = 0, qtd_0 = 0;

	memset(tab, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	peca = gera_peca_vertical(tamanho);

	insere_peca_tabuleiro(tab,peca);

	while(i < NUM_COLUNAS){
		move_peca_para_esquerda(tab, peca);
		i++;
	}

	for(linha = 0; linha< peca->tamanho; linha++){
		CU_ASSERT_TRUE( tab[linha][peca->pos_coluna] == 100 );
	}

	for(linha=0;linha<NUM_LINHAS;linha++){
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			if(tab[linha][coluna] == 100)
				qtd_100++;
			else
				qtd_0++;
		}
	}
	CU_ASSERT_TRUE( qtd_0 == (NUM_LINHAS*NUM_COLUNAS) - tamanho );
	CU_ASSERT_TRUE( qtd_100 == tamanho );
	verifica_peca_em_jogo(tab, peca);
	CU_ASSERT_TRUE( peca->status == EM_JOGO );
}

void teste_move_peca_para_esquerda_ate_borda_vertical_tamanho_3(void){
	teste_move_peca_para_esquerda_ate_borda_vertical(3);
}

void teste_move_peca_para_esquerda_ate_borda_vertical_tamanho_4(void){
	teste_move_peca_para_esquerda_ate_borda_vertical(4);
}

void teste_move_peca_para_esquerda_ate_borda_vertical_tamanho_5(void){
	teste_move_peca_para_esquerda_ate_borda_vertical(5);
}

/**
* Testa mover baixo uma reta HORIZONTAL TAMANHO variavel
*
*/

void teste_move_peca_para_baixo_horizontal(int tamanho){
	PECA* peca;
	int coluna, linha;
	int qtd_100 = 0, qtd_0 = 0;

	memset(tab, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	peca = gera_peca_horizontal(tamanho);

	insere_peca_tabuleiro(tab,peca);
	move_peca_para_baixo(tab, peca);

	for(coluna = peca->pos_coluna; coluna< peca->tamanho + peca->pos_coluna; coluna++){
		CU_ASSERT_TRUE( tab[peca->pos_linha][coluna] == 100 );
	}

	for(linha=0;linha<NUM_LINHAS;linha++){
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			if(tab[linha][coluna] == 100)
				qtd_100++;
			else
				qtd_0++;
		}
	}
	CU_ASSERT_TRUE( qtd_0 == (NUM_LINHAS*NUM_COLUNAS) - tamanho );
	CU_ASSERT_TRUE( qtd_100 == tamanho );
	verifica_peca_em_jogo(tab, peca);
	CU_ASSERT_TRUE( peca->status == EM_JOGO );
}

void teste_move_peca_para_baixo_horizontal_tamanho_3(void){
	teste_move_peca_para_baixo_horizontal(3);
}

void teste_move_peca_para_baixo_horizontal_tamanho_4(void){
	teste_move_peca_para_baixo_horizontal(3);
}

void teste_move_peca_para_baixo_horizontal_tamanho_5(void){
	teste_move_peca_para_baixo_horizontal(5);
}

/**
* Testa mover baixo uma reta HORIZONTAL ate borda TAMANHO variavel
*
*/

void teste_move_peca_para_baixo_ate_borda_horizontal(int tamanho){
	PECA* peca;
	int i = 0;
	int coluna, linha;
	int qtd_100 = 0, qtd_0 = 0;

	memset(tab, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	peca = gera_peca_horizontal(tamanho);

	insere_peca_tabuleiro(tab,peca);

	while(i<NUM_LINHAS){
		move_peca_para_baixo(tab, peca);
		i++;
	}

	for(coluna = peca->pos_coluna; coluna< peca->tamanho + peca->pos_coluna; coluna++){
		CU_ASSERT_TRUE( tab[peca->pos_linha][coluna] == 100 );
	}

	for(linha=0;linha<NUM_LINHAS;linha++){
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			if(tab[linha][coluna] == 100)
				qtd_100++;
			else
				qtd_0++;
		}
	}
	CU_ASSERT_TRUE( qtd_0 == (NUM_LINHAS*NUM_COLUNAS) - tamanho );
	CU_ASSERT_TRUE( qtd_100 == tamanho );
	verifica_peca_em_jogo(tab, peca);
	CU_ASSERT_TRUE( peca->status == FIXA );
}

void teste_move_peca_para_baixo_ate_borda_horizontal_tamanho_3(void){
	teste_move_peca_para_baixo_ate_borda_horizontal(3);
}

void teste_move_peca_para_baixo_ate_borda_horizontal_tamanho_4(void){
	teste_move_peca_para_baixo_ate_borda_horizontal(4);
}

void teste_move_peca_para_baixo_ate_borda_horizontal_tamanho_5(void){
	teste_move_peca_para_baixo_ate_borda_horizontal(5);
}

/**
* Testa mover direita uma reta HORIZONTAL TAMANHO variavel
*
*/

void teste_move_peca_para_direita_horizontal(int tamanho){
	PECA* peca;
	int coluna, linha;
	int qtd_100 = 0, qtd_0 = 0;

	memset(tab, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	peca = gera_peca_horizontal(tamanho);

	insere_peca_tabuleiro(tab,peca);
	move_peca_para_direita(tab, peca);

	for(coluna = peca->pos_coluna; coluna< peca->tamanho + peca->pos_coluna; coluna++){
		CU_ASSERT_TRUE( tab[peca->pos_linha][coluna] == 100 );
	}

	for(linha=0;linha<NUM_LINHAS;linha++){
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			if(tab[linha][coluna] == 100)
				qtd_100++;
			else
				qtd_0++;
		}
	}
	CU_ASSERT_TRUE( qtd_0 == (NUM_LINHAS*NUM_COLUNAS) - tamanho );
	CU_ASSERT_TRUE( qtd_100 == tamanho );
	verifica_peca_em_jogo(tab, peca);
	CU_ASSERT_TRUE( peca->status == EM_JOGO );
}

void teste_move_peca_para_direita_horizontal_tamanho_3(void){
	teste_move_peca_para_baixo_horizontal(3);
}

void teste_move_peca_para_direita_horizontal_tamanho_4(void){
	teste_move_peca_para_baixo_horizontal(3);
}

void teste_move_peca_para_direita_horizontal_tamanho_5(void){
	teste_move_peca_para_baixo_horizontal(5);
}

/**
* Testa mover direita uma reta HORIZONTAL ate borda TAMANHO variavel
*
*/
void teste_move_peca_para_direita_ate_borda_horizontal(int tamanho){
	PECA* peca;
	int i=0;
	int coluna, linha;
	int qtd_100 = 0, qtd_0 = 0;

	memset(tab, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	peca = gera_peca_horizontal(tamanho);

	insere_peca_tabuleiro(tab,peca);

	while(i<NUM_COLUNAS){
		move_peca_para_direita(tab, peca);
		i++;
	}

	for(coluna = peca->pos_coluna; coluna< peca->tamanho + peca->pos_coluna; coluna++){
		CU_ASSERT_TRUE( tab[peca->pos_linha][coluna] == 100 );
	}

	for(linha=0;linha<NUM_LINHAS;linha++){
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			if(tab[linha][coluna] == 100)
				qtd_100++;
			else
				qtd_0++;
		}
	}
	CU_ASSERT_TRUE( qtd_0 == (NUM_LINHAS*NUM_COLUNAS) - tamanho );
	CU_ASSERT_TRUE( qtd_100 == tamanho );
	verifica_peca_em_jogo(tab, peca);
	CU_ASSERT_TRUE( peca->status == EM_JOGO );
}

void teste_move_peca_para_direita_ate_borda_horizontal_tamanho_3(void){
	teste_move_peca_para_direita_ate_borda_horizontal(3);
}

void teste_move_peca_para_direita_ate_borda_horizontal_tamanho_4(void){
	teste_move_peca_para_direita_ate_borda_horizontal(3);
}

void teste_move_peca_para_direita_ate_borda_horizontal_tamanho_5(void){
	teste_move_peca_para_direita_ate_borda_horizontal(5);
}

/**
* Testa mover baixo uma reta VERTICAL TAMANHO variavel
*
*/

void teste_move_peca_para_baixo_vertical(int tamanho){
	PECA* peca;
	int coluna, linha;
	int qtd_100 = 0, qtd_0 = 0;

	memset(tab, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	peca = gera_peca_vertical(tamanho);

	insere_peca_tabuleiro(tab,peca);
	move_peca_para_baixo(tab, peca);

	for(linha = 1; linha< peca->tamanho; linha++){
		CU_ASSERT_TRUE( tab[linha][peca->pos_coluna] == 100 );
	}

	for(linha=0;linha<NUM_LINHAS;linha++){
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			if(tab[linha][coluna] == 100)
				qtd_100++;
			else
				qtd_0++;
		}
	}
	CU_ASSERT_TRUE( qtd_0 == (NUM_LINHAS*NUM_COLUNAS) - tamanho );
	CU_ASSERT_TRUE( qtd_100 == tamanho );
	verifica_peca_em_jogo(tab, peca);
	CU_ASSERT_TRUE( peca->status == EM_JOGO );
}

void teste_move_peca_para_baixo_vertical_tamanho_3(void){
	teste_move_peca_para_baixo_vertical(3);
}

void teste_move_peca_para_baixo_vertical_tamanho_4(void){
	teste_move_peca_para_baixo_vertical(4);
}

void teste_move_peca_para_baixo_vertical_tamanho_5(void){
	teste_move_peca_para_baixo_vertical(5);
}

/**
* Testa mover baixo uma reta VERTICAL ate borda TAMANHO variavel
*
*/
void teste_move_peca_para_baixo_ate_borda_vertical(int tamanho){
	PECA* peca;
	int i = 0;
	int qtd_100 = 0, qtd_0 = 0;
	int coluna, linha;

	memset(tab, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	peca = gera_peca_vertical(tamanho);

	insere_peca_tabuleiro(tab,peca);
	
	while(i< NUM_LINHAS+200){
		move_peca_para_baixo(tab, peca);
		i++;
	}

	for(linha = peca->pos_linha; linha< peca->tamanho; linha++){
		CU_ASSERT_TRUE( tab[linha][peca->pos_coluna] == 100 );
	}

	for(linha=0;linha<NUM_LINHAS;linha++){
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			if(tab[linha][coluna] == 100)
				qtd_100++;
			else
				qtd_0++;
		}
	}
	CU_ASSERT_TRUE( qtd_0 == (NUM_LINHAS*NUM_COLUNAS) - tamanho );
	CU_ASSERT_TRUE( qtd_100 == tamanho );
	verifica_peca_em_jogo(tab, peca);
	CU_ASSERT_TRUE( peca->status == FIXA );
}

void teste_move_peca_para_baixo_ate_borda_vertical_tamanho_3(void){
	teste_move_peca_para_baixo_ate_borda_vertical(3);
}

void teste_move_peca_para_baixo_ate_borda_vertical_tamanho_4(void){
	teste_move_peca_para_baixo_ate_borda_vertical(4);
}

void teste_move_peca_para_baixo_ate_borda_vertical_tamanho_5(void){
	teste_move_peca_para_baixo_ate_borda_vertical(5);
}

/**
* Testa mover direita uma reta VERTICAL TAMANHO variavel
*
*/
void teste_move_peca_para_direita_vertical(int tamanho){
	PECA* peca;
	int coluna, linha;
	int qtd_100 = 0, qtd_0 = 0;

	memset(tab, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	peca = gera_peca_vertical(tamanho);

	insere_peca_tabuleiro(tab,peca);
	move_peca_para_direita(tab, peca);

	for(linha = 0; linha< peca->tamanho; linha++){
		CU_ASSERT_TRUE( tab[linha][peca->pos_coluna] == 100 );
	}

	for(linha=0;linha<NUM_LINHAS;linha++){
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			if(tab[linha][coluna] == 100)
				qtd_100++;
			else
				qtd_0++;
		}
	}
	CU_ASSERT_TRUE( qtd_0 == (NUM_LINHAS*NUM_COLUNAS) - tamanho );
	CU_ASSERT_TRUE( qtd_100 == tamanho );
	verifica_peca_em_jogo(tab, peca);
	CU_ASSERT_TRUE( peca->status == EM_JOGO );
}

void teste_move_peca_para_direita_vertical_tamanho_3(void){
	teste_move_peca_para_baixo_vertical(3);
}

void teste_move_peca_para_direita_vertical_tamanho_4(void){
	teste_move_peca_para_baixo_vertical(4);
}

void teste_move_peca_para_direita_vertical_tamanho_5(void){
	teste_move_peca_para_baixo_vertical(5);
}

/**
* Testa mover direita uma reta VERTICAL ate borda TAMANHO variavel
*
*/
void teste_move_peca_para_direita_ate_borda_vertical(int tamanho){
	PECA* peca;
	int coluna, linha;
	int i =0;
	int qtd_100 = 0, qtd_0 = 0;

	memset(tab, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	peca = gera_peca_vertical(tamanho);

	insere_peca_tabuleiro(tab,peca);

	while(i < NUM_LINHAS){
		move_peca_para_direita(tab, peca);
		i++;
	}

	for(linha = 0; linha< peca->tamanho; linha++){
		CU_ASSERT_TRUE( tab[linha][peca->pos_coluna] == 100 );
	}

	for(linha=0;linha<NUM_LINHAS;linha++){
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			if(tab[linha][coluna] == 100)
				qtd_100++;
			else
				qtd_0++;
		}
	}
	CU_ASSERT_TRUE( qtd_0 == (NUM_LINHAS*NUM_COLUNAS) - tamanho );
	CU_ASSERT_TRUE( qtd_100 == tamanho );
	verifica_peca_em_jogo(tab, peca);
	CU_ASSERT_TRUE( peca->status == EM_JOGO );
}

void teste_move_peca_para_direita_ate_borda_vertical_tamanho_3(void){
	teste_move_peca_para_direita_ate_borda_vertical(3);
}

void teste_move_peca_para_direita_ate_borda_vertical_tamanho_4(void){
	teste_move_peca_para_direita_ate_borda_vertical(4);
}

void teste_move_peca_para_direita_ate_borda_vertical_tamanho_5(void){
	teste_move_peca_para_direita_ate_borda_vertical(5);
}

/**
* Testa mover peca T, Z, L e quadrado
*
*/
void teste_move_peca_direita(int tipo, int tamanho){
	PECA* peca;
	int coluna, linha;
	int i =0;
	int qtd_100 = 0, qtd_0 = 0;

	memset(tab, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	peca = gera_peca_teste_engine(tipo, tamanho, 0);

	insere_peca_tabuleiro(tab,peca);

	while(i <= NUM_LINHAS){
		move_peca_para_direita(tab, peca);
		i++;
	}

	for(linha=0;linha<NUM_LINHAS;linha++){
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			if(tab[linha][coluna] == 100)
				qtd_100++;
			else
				qtd_0++;
		}
	}
	CU_ASSERT_TRUE( qtd_0 == (NUM_LINHAS*NUM_COLUNAS) - tamanho );
	CU_ASSERT_TRUE( qtd_100 == tamanho );
	verifica_peca_em_jogo(tab, peca);
	CU_ASSERT_TRUE( peca->status == EM_JOGO );
}

void teste_move_peca_direita_L(void){
	teste_move_peca_direita(PECA_L, 5);

}

void teste_move_peca_direita_Z(void){
	teste_move_peca_direita(PECA_Z, 5);
}

void teste_move_peca_direita_T(void){
	teste_move_peca_direita(PECA_T, 7);

}

void teste_move_peca_direita_quadrado(void){
	teste_move_peca_direita(PECA_QUADRADO, 4);
}


void teste_move_peca_esquerda(int tipo, int tamanho){
	PECA* peca;
	int coluna, linha;
	int i =0;
	int qtd_100 = 0, qtd_0 = 0;

	memset(tab, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	peca = gera_peca_teste_engine(tipo, tamanho, 0);

	insere_peca_tabuleiro(tab,peca);

	while(i < NUM_LINHAS){
		move_peca_para_esquerda(tab, peca);
		i++;
	}

	for(linha=0;linha<NUM_LINHAS;linha++){
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			if(tab[linha][coluna] == 100)
				qtd_100++;
			else
				qtd_0++;
		}
	}
	CU_ASSERT_TRUE( qtd_0 == (NUM_LINHAS*NUM_COLUNAS) - tamanho );
	CU_ASSERT_TRUE( qtd_100 == tamanho );
	verifica_peca_em_jogo(tab, peca);
	CU_ASSERT_TRUE( peca->status == EM_JOGO );
}

void teste_move_peca_esquerda_L(void){
	teste_move_peca_esquerda(PECA_L, 5);
}

void teste_move_peca_esquerda_Z(void){
	teste_move_peca_esquerda(PECA_Z, 5);
}

void teste_move_peca_esquerda_T(void){
	teste_move_peca_esquerda(PECA_T, 7);
}

void teste_move_peca_esquerda_quadrado(void){
	teste_move_peca_esquerda(PECA_QUADRADO, 4);
}

void teste_move_peca_baixo(int tipo, int tamanho, int rotacao){
	PECA* peca;
	int coluna, linha;
	int i =0;
	int qtd_100 = 0, qtd_0 = 0;

	memset(tab, 0, NUM_LINHAS * NUM_COLUNAS * sizeof(int));
	peca = gera_peca_teste_engine(tipo, tamanho, 1);

	insere_peca_tabuleiro(tab,peca);

	while(i <= NUM_COLUNAS + NUM_LINHAS){
		move_peca_para_baixo(tab, peca);
		if( i == 5){
			while(peca->rotacao != rotacao){
				gira_peca_noventa_graus(tab, peca);
			}
		}
		i++;
	}

	for(linha=0;linha<NUM_LINHAS;linha++){
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			if(tab[linha][coluna] == 100)
				qtd_100++;
			else
				qtd_0++;
		}
	}
	CU_ASSERT_TRUE( qtd_0 == (NUM_LINHAS*NUM_COLUNAS) - tamanho );
	CU_ASSERT_TRUE( qtd_100 == tamanho );
	verifica_peca_em_jogo(tab, peca);
	if(tamanho == 4)
	CU_ASSERT_TRUE( peca->status == FIXA );
}

void teste_move_peca_baixo_L(void){
	teste_move_peca_baixo(PECA_L, 5, 1);
	teste_move_peca_baixo(PECA_L, 5, 2);
	teste_move_peca_baixo(PECA_L, 5, 3);
	teste_move_peca_baixo(PECA_L, 5, 4);
}

void teste_move_peca_baixo_Z(void){
	teste_move_peca_baixo(PECA_Z, 5, 1);
	teste_move_peca_baixo(PECA_Z, 5, 2);
}

void teste_move_peca_baixo_T(void){
	teste_move_peca_baixo(PECA_T, 7, 1);
	teste_move_peca_baixo(PECA_T, 7, 2);
	teste_move_peca_baixo(PECA_T, 7, 3);
	teste_move_peca_baixo(PECA_T, 7, 4);
}

void teste_move_peca_baixo_quadrado(void){
	teste_move_peca_baixo(PECA_QUADRADO, 4, 1);
}


void  adicionar_suite_engine(void){
	CU_pSuite suite;

	/*Cria uma suite que conterá todos os testes*/
	suite = CU_add_suite("Testes modulo engine, inserir pecas horizontais",NULL,NULL);

	CU_ADD_TEST(suite, teste_insere_reta_horizontal_tamanho_3);
	CU_ADD_TEST(suite, teste_insere_reta_horizontal_tamanho_4);
	CU_ADD_TEST(suite, teste_insere_reta_horizontal_tamanho_5);

	suite = CU_add_suite("Testes modulo engine, inserir pecas verticais",NULL,NULL);
	CU_ADD_TEST(suite, teste_insere_reta_vertical_tamanho_3);
	CU_ADD_TEST(suite, teste_insere_reta_vertical_tamanho_4);
	CU_ADD_TEST(suite, teste_insere_reta_vertical_tamanho_5);

	suite = CU_add_suite("Testes modulo engine, inserir pecas T, Z, L E quadrado",NULL,NULL);
	CU_ADD_TEST(suite, teste_insere_T);
	CU_ADD_TEST(suite, teste_insere_Z);
	CU_ADD_TEST(suite, teste_insere_L);
	CU_ADD_TEST(suite, teste_insere_quadrado);

	suite = CU_add_suite("Testes modulo engine, mover pecas horizontais",NULL,NULL);
	CU_ADD_TEST(suite, teste_move_peca_para_esquerda_horizontal_tamanho_3);
	CU_ADD_TEST(suite, teste_move_peca_para_esquerda_horizontal_tamanho_4);
	CU_ADD_TEST(suite, teste_move_peca_para_esquerda_horizontal_tamanho_5);

	CU_ADD_TEST(suite, teste_move_peca_para_esquerda_ate_borda_horizontal_tamanho_3);
	CU_ADD_TEST(suite, teste_move_peca_para_esquerda_ate_borda_horizontal_tamanho_4);
	CU_ADD_TEST(suite, teste_move_peca_para_esquerda_ate_borda_horizontal_tamanho_5);

	CU_ADD_TEST(suite, teste_move_peca_para_baixo_horizontal_tamanho_3);
	CU_ADD_TEST(suite, teste_move_peca_para_baixo_horizontal_tamanho_4);
	CU_ADD_TEST(suite, teste_move_peca_para_baixo_horizontal_tamanho_5);

	CU_ADD_TEST(suite, teste_move_peca_para_baixo_ate_borda_horizontal_tamanho_3);
	CU_ADD_TEST(suite, teste_move_peca_para_baixo_ate_borda_horizontal_tamanho_4);
	CU_ADD_TEST(suite, teste_move_peca_para_baixo_ate_borda_horizontal_tamanho_5);

	CU_ADD_TEST(suite, teste_move_peca_para_direita_ate_borda_horizontal_tamanho_3);
	CU_ADD_TEST(suite, teste_move_peca_para_direita_ate_borda_horizontal_tamanho_4);
	CU_ADD_TEST(suite, teste_move_peca_para_direita_ate_borda_horizontal_tamanho_5);

	CU_ADD_TEST(suite, teste_move_peca_para_direita_horizontal_tamanho_3);
	CU_ADD_TEST(suite, teste_move_peca_para_direita_horizontal_tamanho_4);
	CU_ADD_TEST(suite, teste_move_peca_para_direita_horizontal_tamanho_5);

	suite = CU_add_suite("Testes modulo engine, mover pecas verticais",NULL,NULL);
	CU_ADD_TEST(suite, teste_move_peca_para_esquerda_vertical_tamanho_3);
	CU_ADD_TEST(suite, teste_move_peca_para_esquerda_vertical_tamanho_4);
	CU_ADD_TEST(suite, teste_move_peca_para_esquerda_vertical_tamanho_5);

	CU_ADD_TEST(suite, teste_move_peca_para_esquerda_ate_borda_vertical_tamanho_3);
	CU_ADD_TEST(suite, teste_move_peca_para_esquerda_ate_borda_vertical_tamanho_4);
	CU_ADD_TEST(suite, teste_move_peca_para_esquerda_ate_borda_vertical_tamanho_5);

	CU_ADD_TEST(suite, teste_move_peca_para_baixo_ate_borda_vertical_tamanho_3);
	CU_ADD_TEST(suite, teste_move_peca_para_baixo_ate_borda_vertical_tamanho_4);
	CU_ADD_TEST(suite, teste_move_peca_para_baixo_ate_borda_vertical_tamanho_5);

	CU_ADD_TEST(suite, teste_move_peca_para_baixo_vertical_tamanho_3);
	CU_ADD_TEST(suite, teste_move_peca_para_baixo_vertical_tamanho_4);
	CU_ADD_TEST(suite, teste_move_peca_para_baixo_vertical_tamanho_5);

	CU_ADD_TEST(suite, teste_move_peca_para_direita_vertical_tamanho_3);
	CU_ADD_TEST(suite, teste_move_peca_para_direita_vertical_tamanho_4);
	CU_ADD_TEST(suite, teste_move_peca_para_direita_vertical_tamanho_5);

	CU_ADD_TEST(suite, teste_move_peca_para_direita_ate_borda_vertical_tamanho_3);
	CU_ADD_TEST(suite, teste_move_peca_para_direita_ate_borda_vertical_tamanho_4);
	CU_ADD_TEST(suite, teste_move_peca_para_direita_ate_borda_vertical_tamanho_5);


	suite = CU_add_suite("Testes modulo engine, mover peca T",NULL,NULL);

	CU_ADD_TEST(suite, teste_move_peca_direita_T);
	CU_ADD_TEST(suite, teste_move_peca_esquerda_T);
	CU_ADD_TEST(suite, teste_move_peca_baixo_T);

	suite = CU_add_suite("Testes modulo engine, mover peca Z",NULL,NULL);

	CU_ADD_TEST(suite, teste_move_peca_direita_Z);
	CU_ADD_TEST(suite, teste_move_peca_esquerda_Z);
	CU_ADD_TEST(suite, teste_move_peca_baixo_Z);

	suite = CU_add_suite("Testes modulo engine, mover peca L",NULL,NULL);

	CU_ADD_TEST(suite, teste_move_peca_direita_L);
	CU_ADD_TEST(suite, teste_move_peca_esquerda_L);
	CU_ADD_TEST(suite, teste_move_peca_baixo_L);

	suite = CU_add_suite("Testes modulo engine, mover peca quadrado",NULL,NULL);

	CU_ADD_TEST(suite, teste_move_peca_direita_quadrado);
	CU_ADD_TEST(suite, teste_move_peca_esquerda_quadrado);
	CU_ADD_TEST(suite, teste_move_peca_baixo_quadrado);

	suite = CU_add_suite("Testes modulo engine, pontos",NULL,NULL);
	CU_ADD_TEST(suite, testa_pontua);

	suite = CU_add_suite("Testes modulo engine, fim de jogo",NULL,NULL);
	CU_ADD_TEST(suite, testa_fim_de_jogo);

}


int rodar_teste_engine(){

	/*Inicializa o registro de suítes e testes do CUnit*/
	if (CUE_SUCCESS != CU_initialize_registry())
    		return CU_get_error();

	/*Adiciona os testes ao registro*/
   	adicionar_suite_engine();

	/*Muda o modo do CUnit para o modo VERBOSE
	 O modo VERBOSE mostra algumas informacoes a
	 mais na hora da execucao-> Outras opções: NORMAL e SILENT*/
	CU_basic_set_mode(CU_BRM_VERBOSE);

	/*Roda os testes e mostra na tela os resultados*/
	(void)CU_basic_run_tests();
	//CU_console_run_tests();
	//CU_automated_run_tests();


	/*Limpa o registro*/
	CU_cleanup_registry();
	return 1;
}

int main(){
	rodar_teste_engine();
	return 1;
}
