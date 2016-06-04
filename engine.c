#include <ncurses.h>
#include "pecas.h"
#include "parametros.h"

extern void desce_todas_linhas(int tabuleiro[][NUM_COLUNAS],int linha);

/*
* Finaliza ncurses. 
*
*/
extern void inicia_ncurses(){
	(void) initscr();
	(void) start_color();
	(void) curs_set(FALSE);
}

/*
* Inicializa ncurses. 
*
*/
extern void finaliza_ncurses(){	
	(void) endwin();
}

/*
* Pega entrada no usuario. 
*
*/
extern char pega_input(){
	return (char) getchar();
}
/*
* Desenha peça atual no tabuleiro. 
*
*/
extern void insere_peca_tabuleiro(int tabuleiro[][NUM_COLUNAS], PECA* peca){
	int coluna;
	int linha;
	switch(peca->tipo){
		case RETA_VERTICAL:
			for(linha = peca->pos_linha; linha< peca->tamanho; linha++){
				tabuleiro[linha][peca->pos_coluna] = peca->cor;
			}
			break;
		case RETA_HORIZONTAL:
			for(coluna = peca->pos_coluna; coluna< peca->tamanho + peca->pos_coluna; coluna++){
				tabuleiro[peca->pos_linha][coluna] = peca->cor;
			}
			break;
		case PECA_Z:
			tabuleiro[0][peca->pos_coluna-1] = peca->cor;
			for(linha = 0; linha< 3; linha++){
				tabuleiro[linha][peca->pos_coluna] = peca->cor;
			}
			tabuleiro[2][peca->pos_coluna+1] = peca->cor;
			break;
		case PECA_T:
			for(coluna = peca->pos_coluna-2; coluna<= peca->pos_coluna+2; coluna++){
				tabuleiro[0][coluna] = peca->cor;
			}
			for(linha = 0; linha< 3; linha++){
				tabuleiro[linha][peca->pos_coluna] = peca->cor;
			}
			break;
		case PECA_QUADRADO:
			for(linha = 0; linha< 2; linha++){
				tabuleiro[linha][peca->pos_coluna] = peca->cor;
				tabuleiro[linha][peca->pos_coluna+1] = peca->cor;
			}
			break;
		case PECA_L:
			for(coluna = peca->pos_coluna-1; coluna<= peca->pos_coluna+1; coluna++){
				tabuleiro[peca->pos_linha+2][coluna] = peca->cor;
			}
			for(linha = 0; linha< 2; linha++){
				tabuleiro[linha][peca->pos_coluna-1] = peca->cor;
			}

			break;
		default:
			break;
	}

}

/*
* Faz o movimento da peça atual para esquerda. 
*
*/
extern void move_peca_para_esquerda(int tabuleiro[][NUM_COLUNAS], PECA* peca){
	int linha;
	switch(peca->tipo){
		case RETA_VERTICAL:
			if(peca->pos_coluna == 0){
				return;
			}

			for(linha = peca->pos_linha; linha< peca->tamanho + peca->pos_linha; linha++){
				if(tabuleiro[linha][peca->pos_coluna-1] != 0){
					return;
				}
			}
			for(linha = peca->pos_linha; linha< peca->tamanho + peca->pos_linha; linha++){
				tabuleiro[linha][peca->pos_coluna-1] = tabuleiro[linha][peca->pos_coluna];
				tabuleiro[linha][peca->pos_coluna] = 0;

			}
			peca->pos_coluna--;
			break;
		case RETA_HORIZONTAL:
			if(peca->pos_coluna == 0){
				return;
			}
			if(tabuleiro[peca->pos_linha][peca->pos_coluna-1] == 0){
				tabuleiro[peca->pos_linha][peca->pos_coluna-1] = tabuleiro[peca->pos_linha][peca->pos_coluna + peca->tamanho -1];
				tabuleiro[peca->pos_linha][peca->pos_coluna + peca->tamanho -1] = 0;
			}else{
				return;
			}
			peca->pos_coluna--;
			break;
		case PECA_Z:
			if(peca->pos_coluna - 2 < 0){
				return;
			}
			if(peca->rotacao == 1){
				if(		tabuleiro[peca->pos_linha][peca->pos_coluna-2] != 0 || 
						tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] != 0 || 
						tabuleiro[peca->pos_linha+2][peca->pos_coluna-1] != 0){
					return;
				}
				tabuleiro[peca->pos_linha][peca->pos_coluna - 2] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna -1] = peca->cor; 	
				tabuleiro[peca->pos_linha+1][peca->pos_coluna] = 0;

				tabuleiro[peca->pos_linha + 2][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha + 2][peca->pos_coluna+1] = 0;
			
				peca->pos_coluna--;
			} 
			if(peca->rotacao == 2){
				if(		tabuleiro[peca->pos_linha-1][peca->pos_coluna] != 0 || 
						tabuleiro[peca->pos_linha][peca->pos_coluna-2] != 0 || 
						tabuleiro[peca->pos_linha+1][peca->pos_coluna-2] != 0){
					return;
				}
				tabuleiro[peca->pos_linha-1][peca->pos_coluna] = peca->cor;
				tabuleiro[peca->pos_linha-1][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha][peca->pos_coluna - 2] = peca->cor; 	
				tabuleiro[peca->pos_linha][peca->pos_coluna + 1] = 0;

				tabuleiro[peca->pos_linha + 1][peca->pos_coluna-2] = peca->cor;
				tabuleiro[peca->pos_linha + 1][peca->pos_coluna-1] = 0;
			
				peca->pos_coluna--;
			}

			break;
		case PECA_T:

			if(peca->rotacao == 1){
				if(peca->pos_coluna - 3 < 0){
					return;
				}
				if(	tabuleiro[peca->pos_linha][peca->pos_coluna-3] != 0 ||
					tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] != 0 || 
					tabuleiro[peca->pos_linha+2][peca->pos_coluna-1] != 0){
					return;
				}
				tabuleiro[peca->pos_linha][peca->pos_coluna-3] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna+2] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna - 1] = peca->cor; 	
				tabuleiro[peca->pos_linha+1][peca->pos_coluna] = 0;

				tabuleiro[peca->pos_linha + 2][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha + 2][peca->pos_coluna] = 0;

				peca->pos_coluna--;

			}

			if(peca->rotacao == 2){
				if(peca->pos_coluna - 2 < 0){
					return;
				}
				if(	tabuleiro[peca->pos_linha-2][peca->pos_coluna] != 0 || 
					tabuleiro[peca->pos_linha-1][peca->pos_coluna] != 0 ||
					tabuleiro[peca->pos_linha][peca->pos_coluna-2] != 0 ||
					tabuleiro[peca->pos_linha+1][peca->pos_coluna] != 0 || 
					tabuleiro[peca->pos_linha+2][peca->pos_coluna] != 0){
					return;
				}

				tabuleiro[peca->pos_linha-2][peca->pos_coluna] = peca->cor; 	
				tabuleiro[peca->pos_linha-2][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha - 1][peca->pos_coluna] = peca->cor;
				tabuleiro[peca->pos_linha - 1][peca->pos_coluna+1] = 0;


				tabuleiro[peca->pos_linha][peca->pos_coluna-2] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna] = peca->cor; 	
				tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha + 2][peca->pos_coluna] = peca->cor;
				tabuleiro[peca->pos_linha + 2][peca->pos_coluna+1] = 0;

				peca->pos_coluna--;

			}
			if(peca->rotacao == 3){
				if(peca->pos_coluna - 3 < 0){
					return;
				}
				if(	tabuleiro[peca->pos_linha-1][peca->pos_coluna-1] != 0 ||
					tabuleiro[peca->pos_linha][peca->pos_coluna-1] != 0 || 
					tabuleiro[peca->pos_linha+1][peca->pos_coluna-3] != 0){
					return;
				}
				tabuleiro[peca->pos_linha-1][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha-1][peca->pos_coluna] = 0;

				tabuleiro[peca->pos_linha][peca->pos_coluna - 1] = peca->cor; 	
				tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;

				tabuleiro[peca->pos_linha + 1][peca->pos_coluna-3] = peca->cor;
				tabuleiro[peca->pos_linha + 1][peca->pos_coluna+2] = 0;

				peca->pos_coluna--;

			}

			if(peca->rotacao == 4){
				if(peca->pos_coluna - 2 < 0){
					return;
				}
				if(	tabuleiro[peca->pos_linha-2][peca->pos_coluna-2] != 0 || 
					tabuleiro[peca->pos_linha-1][peca->pos_coluna-2] != 0 ||
					tabuleiro[peca->pos_linha][peca->pos_coluna-2] != 0 ||
					tabuleiro[peca->pos_linha+1][peca->pos_coluna-2] != 0 || 
					tabuleiro[peca->pos_linha+2][peca->pos_coluna-2] != 0){
					return;
				}

				tabuleiro[peca->pos_linha-2][peca->pos_coluna-2] = peca->cor; 	
				tabuleiro[peca->pos_linha-2][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha - 1][peca->pos_coluna-2] = peca->cor;
				tabuleiro[peca->pos_linha - 1][peca->pos_coluna-1] = 0;


				tabuleiro[peca->pos_linha][peca->pos_coluna-2] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna-2] = peca->cor; 	
				tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha + 2][peca->pos_coluna-2] = peca->cor;
				tabuleiro[peca->pos_linha + 2][peca->pos_coluna-1] = 0;

				peca->pos_coluna--;

			}

			break;
		case PECA_QUADRADO:
			if(peca->pos_coluna -1 < 0){
				return;
			} 
			if(tabuleiro[peca->pos_linha][peca->pos_coluna-1] != 0 || tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] != 0){
				return;
			}

			tabuleiro[peca->pos_linha][peca->pos_coluna-1] = peca->cor; 	
			tabuleiro[peca->pos_linha][peca->pos_coluna+1] = 0;

			tabuleiro[peca->pos_linha + 1][peca->pos_coluna-1] = peca->cor;
			tabuleiro[peca->pos_linha + 1][peca->pos_coluna+1] = 0;

			peca->pos_coluna--;

			break;
		case PECA_L:
			if(peca->pos_coluna - 2 < 0){
				return;
			}
			if(peca->rotacao == 1){
				if(	tabuleiro[peca->pos_linha][peca->pos_coluna-2] != 0 ||
					tabuleiro[peca->pos_linha+1][peca->pos_coluna-2] != 0 || 
					tabuleiro[peca->pos_linha+2][peca->pos_coluna-2] != 0){
					return;
				}
				tabuleiro[peca->pos_linha][peca->pos_coluna-2] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna-2] = peca->cor; 	
				tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha + 2][peca->pos_coluna-2] = peca->cor;
				tabuleiro[peca->pos_linha + 2][peca->pos_coluna+1] = 0;

				peca->pos_coluna--;

			}

			if(peca->rotacao == 2){
				if(	tabuleiro[peca->pos_linha][peca->pos_coluna-2] != 0 ||
					tabuleiro[peca->pos_linha+1][peca->pos_coluna-2] != 0 || 
					tabuleiro[peca->pos_linha+2][peca->pos_coluna-2] != 0){
					return;
				}
				tabuleiro[peca->pos_linha][peca->pos_coluna-2] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna-2] = peca->cor; 	
				tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha + 2][peca->pos_coluna-2] = peca->cor;
				tabuleiro[peca->pos_linha + 2][peca->pos_coluna-1] = 0;

				peca->pos_coluna--;

			}
			if(peca->rotacao == 3){
				if(	tabuleiro[peca->pos_linha][peca->pos_coluna-2] != 0 ||
					tabuleiro[peca->pos_linha+1][peca->pos_coluna] != 0 || 
					tabuleiro[peca->pos_linha+2][peca->pos_coluna] != 0){
					return;
				}
				tabuleiro[peca->pos_linha][peca->pos_coluna-2] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna] = peca->cor; 	
				tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha + 2][peca->pos_coluna] = peca->cor;
				tabuleiro[peca->pos_linha + 2][peca->pos_coluna+1] = 0;

				peca->pos_coluna--;

			}
			if(peca->rotacao == 4){
				if(	tabuleiro[peca->pos_linha][peca->pos_coluna] != 0 ||
					tabuleiro[peca->pos_linha+1][peca->pos_coluna] != 0 || 
					tabuleiro[peca->pos_linha+2][peca->pos_coluna-2] != 0){
					return;
				}
				tabuleiro[peca->pos_linha][peca->pos_coluna] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna] = peca->cor; 	
				tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha + 2][peca->pos_coluna-2] = peca->cor;
				tabuleiro[peca->pos_linha + 2][peca->pos_coluna+1] = 0;

				peca->pos_coluna--;

			}

			break;
		default:
			break;

	}
}

/*
* Faz o movimento da peça atual para direita. 
*
*/
extern void move_peca_para_direita(int tabuleiro[][NUM_COLUNAS], PECA* peca){
	int linha;

	switch(peca->tipo){
		case RETA_VERTICAL:
			if(peca->pos_coluna > NUM_COLUNAS-2){
				return;
			}
			for(linha = peca->pos_linha; linha< peca->tamanho+peca->pos_linha; linha++){
				if(tabuleiro[linha][peca->pos_coluna+1] != 0){
					return;
				}
			}
			for(linha = peca->pos_linha; linha< peca->tamanho+peca->pos_linha; linha++){
				tabuleiro[linha][peca->pos_coluna+1] = tabuleiro[linha][peca->pos_coluna];
				tabuleiro[linha][peca->pos_coluna] = 0;

			}
			peca->pos_coluna++;
			break;
		case RETA_HORIZONTAL:
			if(peca->pos_coluna + peca->tamanho > NUM_COLUNAS-1){
				return;
			}
			if(tabuleiro[peca->pos_linha][peca->pos_coluna+ peca->tamanho] == 0){
				tabuleiro[peca->pos_linha][peca->pos_coluna + peca->tamanho] = tabuleiro[peca->pos_linha][peca->pos_coluna];
				tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;
			
			}else{
				return;
			}
			peca->pos_coluna++;
			break;
		case PECA_Z:
			if(peca->pos_coluna + 2 >= NUM_COLUNAS){
				return;
			}
			if(peca->rotacao == 1){

				if(		tabuleiro[peca->pos_linha][peca->pos_coluna+1] != 0 || 
						tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] != 0 || 
						tabuleiro[peca->pos_linha+2][peca->pos_coluna+2] != 0){
					return;
				}
				tabuleiro[peca->pos_linha][peca->pos_coluna + 1] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna - 1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna +1] = peca->cor; 	
				tabuleiro[peca->pos_linha+1][peca->pos_coluna] = 0;

				tabuleiro[peca->pos_linha + 2][peca->pos_coluna+2] = peca->cor;
				tabuleiro[peca->pos_linha + 2][peca->pos_coluna] = 0;
			
				peca->pos_coluna++;
			} 
			if(peca->rotacao == 2){
				if(		tabuleiro[peca->pos_linha-1][peca->pos_coluna+2] != 0 || 
						tabuleiro[peca->pos_linha][peca->pos_coluna+2] != 0 || 
						tabuleiro[peca->pos_linha+1][peca->pos_coluna] != 0){
					return;
				}
				tabuleiro[peca->pos_linha-1][peca->pos_coluna+2] = peca->cor;
				tabuleiro[peca->pos_linha-1][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha][peca->pos_coluna + 2] = peca->cor; 	
				tabuleiro[peca->pos_linha][peca->pos_coluna - 1] = 0;

				tabuleiro[peca->pos_linha + 1][peca->pos_coluna] = peca->cor;
				tabuleiro[peca->pos_linha + 1][peca->pos_coluna-1] = 0;
			
				peca->pos_coluna++;
			}
			

			break;
		case PECA_T:
			if(peca->rotacao == 1){
				if(peca->pos_coluna + 3 >= NUM_COLUNAS){
					return;
				}
				if(	tabuleiro[peca->pos_linha][peca->pos_coluna+3] != 0 ||
					tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] != 0 || 
					tabuleiro[peca->pos_linha+2][peca->pos_coluna+1] != 0){
					return;
				}
				tabuleiro[peca->pos_linha][peca->pos_coluna+3] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna-2] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna + 1] = peca->cor; 	
				tabuleiro[peca->pos_linha+1][peca->pos_coluna] = 0;

				tabuleiro[peca->pos_linha + 2][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha + 2][peca->pos_coluna] = 0;

				peca->pos_coluna++;

			}

			if(peca->rotacao == 2){
				if(peca->pos_coluna + 2 >= NUM_COLUNAS){
					return;
				}
				if(	tabuleiro[peca->pos_linha-2][peca->pos_coluna+2] != 0 || 
					tabuleiro[peca->pos_linha-1][peca->pos_coluna+2] != 0 ||
					tabuleiro[peca->pos_linha][peca->pos_coluna+2] != 0 ||
					tabuleiro[peca->pos_linha+1][peca->pos_coluna+2] != 0 || 
					tabuleiro[peca->pos_linha+2][peca->pos_coluna+2] != 0){
					return;
				}

				tabuleiro[peca->pos_linha-2][peca->pos_coluna+2] = peca->cor; 	
				tabuleiro[peca->pos_linha-2][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha - 1][peca->pos_coluna+2] = peca->cor;
				tabuleiro[peca->pos_linha - 1][peca->pos_coluna+1] = 0;


				tabuleiro[peca->pos_linha][peca->pos_coluna+2] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna+2] = peca->cor; 	
				tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha + 2][peca->pos_coluna+2] = peca->cor;
				tabuleiro[peca->pos_linha + 2][peca->pos_coluna+1] = 0;

				peca->pos_coluna++;

			}
			if(peca->rotacao == 3){
				if(peca->pos_coluna + 3 >= NUM_COLUNAS){
					return;
				}
				if(	tabuleiro[peca->pos_linha-1][peca->pos_coluna+1] != 0 ||
					tabuleiro[peca->pos_linha][peca->pos_coluna+1] != 0 || 
					tabuleiro[peca->pos_linha+1][peca->pos_coluna+3] != 0){
					return;
				}
				tabuleiro[peca->pos_linha-1][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha-1][peca->pos_coluna] = 0;

				tabuleiro[peca->pos_linha][peca->pos_coluna + 1] = peca->cor; 	
				tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;

				tabuleiro[peca->pos_linha + 1][peca->pos_coluna+3] = peca->cor;
				tabuleiro[peca->pos_linha + 1][peca->pos_coluna-2] = 0;

				peca->pos_coluna++;

			}

			if(peca->rotacao == 4){
				if(peca->pos_coluna + 2 >= NUM_COLUNAS){
					return;
				}
				if(	tabuleiro[peca->pos_linha-2][peca->pos_coluna] != 0 || 
					tabuleiro[peca->pos_linha-1][peca->pos_coluna] != 0 ||
					tabuleiro[peca->pos_linha][peca->pos_coluna+2] != 0 ||
					tabuleiro[peca->pos_linha+1][peca->pos_coluna] != 0 || 
					tabuleiro[peca->pos_linha+2][peca->pos_coluna] != 0){
					return;
				}

				tabuleiro[peca->pos_linha-2][peca->pos_coluna] = peca->cor; 	
				tabuleiro[peca->pos_linha-2][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha - 1][peca->pos_coluna] = peca->cor;
				tabuleiro[peca->pos_linha - 1][peca->pos_coluna-1] = 0;


				tabuleiro[peca->pos_linha][peca->pos_coluna+2] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna] = peca->cor; 	
				tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha + 2][peca->pos_coluna] = peca->cor;
				tabuleiro[peca->pos_linha + 2][peca->pos_coluna-1] = 0;

				peca->pos_coluna++;

			}

			break;
		case PECA_QUADRADO:
			if(peca->pos_coluna + 2 >= NUM_COLUNAS){
				return;
			} 
			if(tabuleiro[peca->pos_linha][peca->pos_coluna+2] != 0 || tabuleiro[peca->pos_linha+1][peca->pos_coluna+2] != 0){
				return;
			}

			tabuleiro[peca->pos_linha][peca->pos_coluna+2] = peca->cor;
			tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;

			tabuleiro[peca->pos_linha + 1][peca->pos_coluna+2] = peca->cor;
			tabuleiro[peca->pos_linha + 1][peca->pos_coluna] = 0;

			peca->pos_coluna++;

			break;
		case PECA_L:

			if(peca->pos_coluna + 2 >= NUM_COLUNAS){
				return;
			}
			if(peca->rotacao == 1){
				if(	tabuleiro[peca->pos_linha][peca->pos_coluna] != 0 ||
					tabuleiro[peca->pos_linha+1][peca->pos_coluna] != 0 || 
					tabuleiro[peca->pos_linha+2][peca->pos_coluna+2] != 0){
					return;
				}
				tabuleiro[peca->pos_linha][peca->pos_coluna] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna] = peca->cor; 	
				tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha + 2][peca->pos_coluna+2] = peca->cor;
				tabuleiro[peca->pos_linha + 2][peca->pos_coluna-1] = 0;

				peca->pos_coluna++;

			}

			if(peca->rotacao == 2){
				if(	tabuleiro[peca->pos_linha][peca->pos_coluna+2] != 0 ||
					tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] != 0 || 
					tabuleiro[peca->pos_linha+2][peca->pos_coluna+1] != 0){
					return;
				}
				tabuleiro[peca->pos_linha][peca->pos_coluna+2] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna] = peca->cor; 	
				tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha + 2][peca->pos_coluna] = peca->cor;
				tabuleiro[peca->pos_linha + 2][peca->pos_coluna-1] = 0;

				peca->pos_coluna++;

			}
			if(peca->rotacao == 3){
				if(	tabuleiro[peca->pos_linha][peca->pos_coluna+2] != 0 ||
					tabuleiro[peca->pos_linha+1][peca->pos_coluna+2] != 0 || 
					tabuleiro[peca->pos_linha+2][peca->pos_coluna+2] != 0){
					return;
				}
				tabuleiro[peca->pos_linha][peca->pos_coluna+2] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna+2] = peca->cor; 	
				tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha + 2][peca->pos_coluna+2] = peca->cor;
				tabuleiro[peca->pos_linha + 2][peca->pos_coluna+1] = 0;

				peca->pos_coluna++;

			}
			if(peca->rotacao == 4){
				if(	tabuleiro[peca->pos_linha][peca->pos_coluna+2] != 0 ||
					tabuleiro[peca->pos_linha+1][peca->pos_coluna+2] != 0 || 
					tabuleiro[peca->pos_linha+2][peca->pos_coluna+2] != 0){
					return;
				}
				tabuleiro[peca->pos_linha][peca->pos_coluna+2] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna+2] = peca->cor; 	
				tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha + 2][peca->pos_coluna+2] = peca->cor;
				tabuleiro[peca->pos_linha + 2][peca->pos_coluna-1] = 0;

				peca->pos_coluna++;

			}


			break;
		default:
			break;
	}


}

/*
* Faz o movimento da peça atual para baixo. 
*
*/
extern void move_peca_para_baixo(int tabuleiro[][NUM_COLUNAS], PECA* peca){
	int coluna;
	switch (peca->tipo){

		case RETA_VERTICAL:
			if(peca->pos_linha + peca->tamanho >= NUM_LINHAS){
				return;
			}
			if(tabuleiro[peca->pos_linha + peca->tamanho][peca->pos_coluna] != 0){
				return;
			}
			tabuleiro[peca->pos_linha + peca->tamanho][peca->pos_coluna] = peca->cor;
			tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;			
			break;
		case RETA_HORIZONTAL:
			if(peca->pos_linha + 1 >= NUM_LINHAS){
				return;
			}
			for(coluna = peca->pos_coluna; coluna < peca->pos_coluna + peca->tamanho; coluna++){
				if(tabuleiro[peca->pos_linha+1][coluna] != 0){
					return;
				}
			}
			for(coluna = peca->pos_coluna; coluna < peca->pos_coluna + peca->tamanho; coluna++){
				tabuleiro[peca->pos_linha + 1][coluna] = tabuleiro[peca->pos_linha][coluna];
				tabuleiro[peca->pos_linha][coluna] = 0;
			}			

			break;
		case PECA_Z:
			if(peca->pos_linha + 3 >= NUM_LINHAS && peca->rotacao== 1){//testa se fim do tabuleiro
				return;
			}
			if(peca->pos_linha + 2 >= NUM_LINHAS && peca->rotacao == 2){//testa se fim do tabuleiro
				return;
			}
			if(peca->rotacao == 1){
				if(tabuleiro[peca->pos_linha+1][peca->pos_coluna-1]!=0){
					return;
				}
				if(tabuleiro[peca->pos_linha+3][peca->pos_coluna] != 0 || tabuleiro[peca->pos_linha+3][peca->pos_coluna+1] != 0){
					return;
				}
				tabuleiro[peca->pos_linha + 3][peca->pos_coluna] = tabuleiro[peca->pos_linha][peca->pos_coluna];
				tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;
				tabuleiro[peca->pos_linha+1][peca->pos_coluna -1] = tabuleiro[peca->pos_linha][peca->pos_coluna -1]; 	
				tabuleiro[peca->pos_linha][peca->pos_coluna -1] = 0;
				tabuleiro[peca->pos_linha + 3][peca->pos_coluna+1] = tabuleiro[peca->pos_linha+2][peca->pos_coluna+1];
				tabuleiro[peca->pos_linha+2][peca->pos_coluna+1] = 0;

			}else if(peca->rotacao ==2){
				if(tabuleiro[peca->pos_linha+2][peca->pos_coluna-1] != 0){
					return;
				}

				if(tabuleiro[peca->pos_linha+1][peca->pos_coluna] != 0 || tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] != 0){
					return;
				}
				tabuleiro[peca->pos_linha+2][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha-1][peca->pos_coluna+1] = 0;

			}


			break;
		case PECA_T:
			if(peca->rotacao == 1){
				if(peca->pos_linha + 3 >= NUM_LINHAS){
					return;
				}
				if(tabuleiro[peca->pos_linha+3][peca->pos_coluna] != 0){
					return;
				}
				for(coluna = peca->pos_coluna-2;coluna <= peca->pos_coluna+2;coluna++){
					if(coluna != peca->pos_coluna){
						if(tabuleiro[peca->pos_linha+1][coluna] != 0){
							return;						
						}
					}
				}
				for(coluna = peca->pos_coluna-2;coluna <= peca->pos_coluna+2;coluna++){
					if(coluna == peca->pos_coluna){
						tabuleiro[peca->pos_linha+3][peca->pos_coluna] = tabuleiro[peca->pos_linha][peca->pos_coluna];
						tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;
					}else{
						tabuleiro[peca->pos_linha+1][coluna] = tabuleiro[peca->pos_linha][coluna];
						tabuleiro[peca->pos_linha][coluna] = 0;					
					}
				}
			}	
			if(peca->rotacao == 2){
				if(peca->pos_linha + 3 >= NUM_LINHAS){
					return;
				}
				if(tabuleiro[peca->pos_linha+3][peca->pos_coluna+1] != 0){
					return;
				}
				for(coluna = peca->pos_coluna-1;coluna <= peca->pos_coluna+1;coluna++){
					if(tabuleiro[peca->pos_linha+1][coluna] != 0 && coluna != peca->pos_coluna+1){
						return;						
					}
				}
				for(coluna = peca->pos_coluna-1;coluna <= peca->pos_coluna+1;coluna++){
					if(coluna == peca->pos_coluna+1){
						tabuleiro[peca->pos_linha+3][peca->pos_coluna+1] = peca->cor;
						tabuleiro[peca->pos_linha-2][peca->pos_coluna+1] = 0;
					}else{
						tabuleiro[peca->pos_linha+1][coluna] = peca->cor;
						tabuleiro[peca->pos_linha][coluna] = 0;					
					}
				}
			}
			if(peca->rotacao == 3){
				if(peca->pos_linha + 2 >= NUM_LINHAS){
					return;
				}
				if(	tabuleiro[peca->pos_linha+2][peca->pos_coluna-2] != 0 ||
					tabuleiro[peca->pos_linha+2][peca->pos_coluna-1] != 0 ||
					tabuleiro[peca->pos_linha+2][peca->pos_coluna] != 0 || 
					tabuleiro[peca->pos_linha+2][peca->pos_coluna+1] != 0 ||
					tabuleiro[peca->pos_linha+2][peca->pos_coluna+2] != 0 ){
					return;
				}
				tabuleiro[peca->pos_linha+2][peca->pos_coluna-2] = peca->cor;
				tabuleiro[peca->pos_linha+1][peca->pos_coluna-2] = 0;

				tabuleiro[peca->pos_linha+2][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha+2][peca->pos_coluna] = peca->cor; 	
				tabuleiro[peca->pos_linha-1][peca->pos_coluna] = 0;

				tabuleiro[peca->pos_linha+2][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha+2][peca->pos_coluna+2] = peca->cor;
				tabuleiro[peca->pos_linha+1][peca->pos_coluna+2] = 0;

			}

			if(peca->rotacao == 4){
				if(peca->pos_linha + 3 >= NUM_LINHAS){
					return;
				}
				if(	tabuleiro[peca->pos_linha+3][peca->pos_coluna-1] != 0 || 
					tabuleiro[peca->pos_linha+1][peca->pos_coluna] != 0 ||
					tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] != 0 ){

					return;
				}

				tabuleiro[peca->pos_linha+3][peca->pos_coluna-1] = peca->cor; 	
				tabuleiro[peca->pos_linha-2][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha + 1][peca->pos_coluna] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;

				tabuleiro[peca->pos_linha + 1][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna+1] = 0;


			}


			break;
		case PECA_QUADRADO:
			if(peca->pos_linha + 2 >= NUM_LINHAS){
				return;
			}

			if(tabuleiro[peca->pos_linha+2][peca->pos_coluna] !=0 || tabuleiro[peca->pos_linha+2][peca->pos_coluna+1] != 0){
				return;
			}

			for(coluna = peca->pos_coluna; coluna <= peca->pos_coluna+1; coluna++){
				tabuleiro[peca->pos_linha+2][coluna] = peca->cor;
				tabuleiro[peca->pos_linha][coluna] = 0;
			}
			break;
		case PECA_L:
			if(peca->rotacao == 1){
				if(peca->pos_linha+3 >= NUM_LINHAS){
					return;
				}
				for(coluna = peca->pos_coluna -1; coluna <= peca->pos_coluna+1;coluna++){
					if(tabuleiro[peca->pos_linha+3][coluna] != 0){
						return;
					}
				}

				for(coluna = peca->pos_coluna -1; coluna <= peca->pos_coluna+1;coluna++){
					if(coluna == peca->pos_coluna -1){
						tabuleiro[peca->pos_linha][coluna] = 0;
						tabuleiro[peca->pos_linha+3][coluna] = peca->cor;
					}else{
						tabuleiro[peca->pos_linha+2][coluna] = 0;
						tabuleiro[peca->pos_linha+3][coluna] = peca->cor;
					}
				}
			}
			if(peca->rotacao == 2){
				if(peca->pos_linha+3 >= NUM_LINHAS){
					return;
				}
				if(	tabuleiro[peca->pos_linha+3][peca->pos_coluna-1] != 0 ||
					tabuleiro[peca->pos_linha+1][peca->pos_coluna] != 0 || 
					tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] != 0){
					return;
				}


				tabuleiro[peca->pos_linha+3][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna+1] = 0;

			}

			if(peca->rotacao == 3){
				if(peca->pos_linha+3 >= NUM_LINHAS){
					return;
				}
				if(	tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] != 0 ||
					tabuleiro[peca->pos_linha+1][peca->pos_coluna] != 0 || 
					tabuleiro[peca->pos_linha+3][peca->pos_coluna+1] != 0){
					return;
				}


				tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;

				tabuleiro[peca->pos_linha+3][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna+1] = 0;

			}
			if(peca->rotacao == 4){
				if(peca->pos_linha+3 >= NUM_LINHAS){
					return;
				}
				if(	tabuleiro[peca->pos_linha+3][peca->pos_coluna-1] != 0 ||
					tabuleiro[peca->pos_linha+3][peca->pos_coluna] != 0 || 
					tabuleiro[peca->pos_linha+3][peca->pos_coluna+1] != 0){
					return;
				}


				tabuleiro[peca->pos_linha+3][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha+2][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha+3][peca->pos_coluna] = peca->cor;
				tabuleiro[peca->pos_linha+2][peca->pos_coluna] = 0;

				tabuleiro[peca->pos_linha+3][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna+1] = 0;

			}

			break;
		default:
			break;
	}	
	peca->pos_linha++;

}

extern void gira_peca_noventa_graus(int tabuleiro[][NUM_COLUNAS], PECA* peca){
	int linha = 0;
	int coluna = 0;
	switch (peca->tipo){
		case RETA_VERTICAL:
			if(peca->tamanho == 3){
				if(peca->pos_coluna-1 < 0 || peca->pos_coluna+1 >= NUM_COLUNAS){
					return;
				}

				for(coluna = peca->pos_coluna-1; coluna <= peca->pos_coluna+1; coluna++){
					if(tabuleiro[peca->pos_linha+1][coluna] != 0 && coluna != peca->pos_coluna){
						return;					
					}
				}
				tabuleiro[peca->pos_linha+1][peca->pos_coluna + 1] = peca->cor; 	
				tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;
				tabuleiro[peca->pos_linha + 1][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha+2][peca->pos_coluna] = 0;
				peca->pos_linha ++;
				peca->pos_coluna --;
				peca->tipo = RETA_HORIZONTAL;
			}
			if(peca->tamanho == 4){
				if(peca->pos_coluna-1 < 0 || peca->pos_coluna+2 >= NUM_COLUNAS){
					return;
				}

				for(coluna = peca->pos_coluna-1; coluna <= peca->pos_coluna+2; coluna++){
					if(tabuleiro[peca->pos_linha+1][coluna] != 0 && coluna != peca->pos_coluna){
						return;					
					}
				}
				tabuleiro[peca->pos_linha+1][peca->pos_coluna + 1] = peca->cor; 	
				tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;
				tabuleiro[peca->pos_linha + 1][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha+2][peca->pos_coluna] = 0;
				tabuleiro[peca->pos_linha + 1][peca->pos_coluna+2] = peca->cor;
				tabuleiro[peca->pos_linha+3][peca->pos_coluna] = 0;
				peca->pos_linha ++;
				peca->pos_coluna --;
				peca->tipo = RETA_HORIZONTAL;
			}
			if(peca->tamanho == 5){
				if(peca->pos_coluna-2 < 0 || peca->pos_coluna+2 >= NUM_COLUNAS){
					return;
				}

				for(coluna = peca->pos_coluna-2; coluna <= peca->pos_coluna+2; coluna++){
					if(tabuleiro[peca->pos_linha+2][coluna] != 0 && coluna != peca->pos_coluna){
						return;					
					}
				}
				tabuleiro[peca->pos_linha+2][peca->pos_coluna + 2] = peca->cor; 	
				tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;
				tabuleiro[peca->pos_linha+2][peca->pos_coluna + 1] = peca->cor; 	
				tabuleiro[peca->pos_linha+1][peca->pos_coluna] = 0;
				
				tabuleiro[peca->pos_linha + 2][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha+3][peca->pos_coluna] = 0;
				tabuleiro[peca->pos_linha + 2][peca->pos_coluna-2] = peca->cor;
				tabuleiro[peca->pos_linha+4][peca->pos_coluna] = 0;

				peca->pos_linha = peca->pos_linha +2;
				peca->pos_coluna = peca->pos_coluna -2;
				peca->tipo = RETA_HORIZONTAL;
			}

			break;
		case RETA_HORIZONTAL:
			if(peca->tamanho == 3){
				if(peca->pos_linha - 1 < 0 || peca->pos_linha + 1 >= NUM_LINHAS){
					return;
				}

				for(linha = peca->pos_linha-1; linha <= peca->pos_linha+1; linha++){
					if(tabuleiro[linha][peca->pos_coluna+1] != 0 && linha != peca->pos_linha){
						return;					
					}
				}
				tabuleiro[peca->pos_linha-1][peca->pos_coluna + 1] = peca->cor; 	
				tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;
				tabuleiro[peca->pos_linha + 1][peca->pos_coluna + 1] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna+2] = 0;
				peca->pos_linha --;
				peca->pos_coluna ++;
				peca->tipo = RETA_VERTICAL;
			}
			if(peca->tamanho == 4){
				if(peca->pos_linha-1 < 0 || peca->pos_linha+2 >= NUM_LINHAS){
					return;
				}

				for(linha = peca->pos_linha-1; linha <= peca->pos_linha+2; linha++){
					if(tabuleiro[linha][peca->pos_coluna+1] != 0 && linha != peca->pos_linha){
						return;					
					}
				}
				tabuleiro[peca->pos_linha-1][peca->pos_coluna + 1] = peca->cor; 	
				tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;
				tabuleiro[peca->pos_linha + 1][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna+2] = 0;
				tabuleiro[peca->pos_linha+2][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna+3] = 0;
				peca->pos_linha --;
				peca->pos_coluna ++;
				peca->tipo = RETA_VERTICAL;
			}
			if(peca->tamanho == 5){
				if(peca->pos_linha-2 < 0 || peca->pos_linha+2 >= NUM_LINHAS){
					return;
				}

				for(linha = peca->pos_linha-2; linha <= peca->pos_linha+2; linha++){
					if(tabuleiro[linha][peca->pos_coluna+2] != 0 && linha != peca->pos_linha){
						return;					
					}
				}
				tabuleiro[peca->pos_linha-2][peca->pos_coluna + 2] = peca->cor; 	
				tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;
				tabuleiro[peca->pos_linha-1][peca->pos_coluna + 2] = peca->cor; 	
				tabuleiro[peca->pos_linha][peca->pos_coluna+1] = 0;
				
				tabuleiro[peca->pos_linha + 1][peca->pos_coluna+2] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna+3] = 0;
				tabuleiro[peca->pos_linha + 2][peca->pos_coluna+2] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna+4] = 0;

				peca->pos_linha = peca->pos_linha -2;
				peca->pos_coluna = peca->pos_coluna +2;
				peca->tipo = RETA_VERTICAL;
			}

			break;
		case PECA_Z:
			if(peca->rotacao == 1){
				if(tabuleiro[peca->pos_linha][peca->pos_coluna+1] != 0 || tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] != 0){
					return;
				}
				if(tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] != 0 || tabuleiro[peca->pos_linha+2][peca->pos_coluna-1] != 0){
					return;
				}
				tabuleiro[peca->pos_linha][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha+2][peca->pos_coluna] = 0;

				tabuleiro[peca->pos_linha+2][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha+2][peca->pos_coluna+1] = 0;

				peca->pos_linha ++;

				peca->rotacao =2;

			} else if(peca->rotacao == 2){
				if(tabuleiro[peca->pos_linha-1][peca->pos_coluna] != 0 || tabuleiro[peca->pos_linha-1][peca->pos_coluna-1] != 0){
					return;
				}
				if(tabuleiro[peca->pos_linha+1][peca->pos_coluna] != 0 || tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] != 0){
					return;
				}
				tabuleiro[peca->pos_linha-1][peca->pos_coluna] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha-1][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha-1][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna-1] = 0;

				peca->pos_linha --;


				peca->rotacao =1;
			}

			break;
		case PECA_T:
			if(peca->rotacao == 1){
				if(tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] != 0 ){
					return;
				}

				if(peca->pos_linha - 1 < 0 || peca->pos_linha + 3 >= NUM_LINHAS){
					return;
				}	

				for(linha = peca->pos_linha-1; linha <= peca->pos_linha + 2 ; linha++ ){
					if(tabuleiro[linha][peca->pos_coluna+1] != 0 && linha != peca->pos_linha){
						return;
					}
				}


				tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha+2][peca->pos_coluna] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;

				tabuleiro[peca->pos_linha+2][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha+3][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna+2] = 0;

				tabuleiro[peca->pos_linha][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha-1][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna-2] = 0;
			
				peca->pos_linha++;

				peca->rotacao = 2;
			} else if(peca->rotacao == 2){

				if(tabuleiro[peca->pos_linha-1][peca->pos_coluna] != 0 ){
					return;
				}

				if(peca->pos_coluna - 2 < 0 || peca->pos_coluna + 2 >= NUM_COLUNAS){
					return;
				}	

				for(coluna = peca->pos_coluna-2; coluna <= peca->pos_coluna + 2 ; coluna++ ){
					if(tabuleiro[peca->pos_linha+1][coluna] != 0 && coluna != peca->pos_coluna+1){
						return;
					}
				}


				tabuleiro[peca->pos_linha-1][peca->pos_coluna] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna-2] = peca->cor;
				tabuleiro[peca->pos_linha+2][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha-1][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna+2] = peca->cor;
				tabuleiro[peca->pos_linha-2][peca->pos_coluna+1] = 0;


				peca->rotacao = 3;
			} else if(peca->rotacao == 3){
				if(tabuleiro[peca->pos_linha][peca->pos_coluna+1] != 0 ){
					return;
				}

				if(peca->pos_linha - 2 < 0 || peca->pos_linha + 2 >= NUM_LINHAS){
					return;
				}	

				for(linha = peca->pos_linha-2; linha <= peca->pos_linha + 2 ; linha++ ){
					if(tabuleiro[linha][peca->pos_coluna-1] != 0 && linha != peca->pos_linha+1){
						return;
					}
				}


				tabuleiro[peca->pos_linha][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha-1][peca->pos_coluna] = 0;

				tabuleiro[peca->pos_linha-2][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha+1][peca->pos_coluna-2] = 0;

				tabuleiro[peca->pos_linha-1][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha+1][peca->pos_coluna] = 0;

				tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha+2][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha+1][peca->pos_coluna+2] = 0;
			

				peca->rotacao = 4;
			} else if(peca->rotacao == 4){
				if(tabuleiro[peca->pos_linha+1][peca->pos_coluna] != 0 ){
					return;
				}

				if(peca->pos_coluna - 2 < 0 || peca->pos_coluna + 2 >= NUM_COLUNAS){
					return;
				}	

				for(coluna = peca->pos_coluna-2; coluna <= peca->pos_coluna + 2 ; coluna++ ){
					if(tabuleiro[peca->pos_linha-1][coluna] != 0 && coluna != peca->pos_coluna-1){
						return;
					}
				}


				tabuleiro[peca->pos_linha+1][peca->pos_coluna] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna+1] = 0;

				tabuleiro[peca->pos_linha-1][peca->pos_coluna+2] = peca->cor;
				tabuleiro[peca->pos_linha-2][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha-1][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha-1][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha-1][peca->pos_coluna] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha-1][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] = 0;

				tabuleiro[peca->pos_linha-1][peca->pos_coluna-2] = peca->cor;
				tabuleiro[peca->pos_linha+2][peca->pos_coluna-1] = 0;

				peca->pos_linha--;

				peca->rotacao = 1;
			}
			break;
		case PECA_QUADRADO:

			break;
		case PECA_L:

			if(peca->rotacao == 1){
				if(tabuleiro[peca->pos_linha][peca->pos_coluna] != 0 && tabuleiro[peca->pos_linha][peca->pos_coluna+1] != 0){
					return;
				}

				tabuleiro[peca->pos_linha][peca->pos_coluna]  = peca->cor;
				tabuleiro[peca->pos_linha+2][peca->pos_coluna] = 0;
				tabuleiro[peca->pos_linha][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha+2][peca->pos_coluna+1] = 0;

				peca->rotacao = 2;
			} else if(peca->rotacao == 2){
				if(tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] != 0 && tabuleiro[peca->pos_linha+2][peca->pos_coluna+1] != 0){
					return;
				}

				tabuleiro[peca->pos_linha+1][peca->pos_coluna+1]  = peca->cor;
				tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] = 0;
				tabuleiro[peca->pos_linha+2][peca->pos_coluna+1] = peca->cor;
				tabuleiro[peca->pos_linha+2][peca->pos_coluna-1] = 0;

				peca->rotacao = 3;
			} else if(peca->rotacao == 3){
				if(tabuleiro[peca->pos_linha+2][peca->pos_coluna] != 0 && tabuleiro[peca->pos_linha+2][peca->pos_coluna-1] != 0){
					return;
				}

				tabuleiro[peca->pos_linha+2][peca->pos_coluna]  = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna] = 0;
				tabuleiro[peca->pos_linha+2][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna-1] = 0;


				peca->rotacao = 4;
			} else if(peca->rotacao == 4){

				if(tabuleiro[peca->pos_linha][peca->pos_coluna-1] != 0 && tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] != 0){
					return;
				}

				tabuleiro[peca->pos_linha][peca->pos_coluna-1]  = peca->cor;
				tabuleiro[peca->pos_linha][peca->pos_coluna+1] = 0;
				tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] = peca->cor;
				tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] = 0;


				peca->rotacao = 1;
			}


			break;
		default:
			break;
	}	


}

/*
* Verifica se a peça atual chegou no final do tabuleiro ou encostou em outra peça.
* Caso verdadeiro, a peça fica FIXA.
*/

extern void verifica_peca_em_jogo(int tabuleiro[][NUM_COLUNAS], PECA* peca){
	int coluna;
	if(peca->status == FIXA){
		return;
	}

	switch(peca->tipo){
		case RETA_VERTICAL:
			if(peca->pos_linha + peca->tamanho >= NUM_LINHAS)
				peca->status = FIXA;
			if(tabuleiro[peca->pos_linha + peca->tamanho][peca->pos_coluna] != 0)
				peca->status = FIXA;
			break;
		case RETA_HORIZONTAL:
			if(peca->pos_linha + 1  >= NUM_LINHAS){
				peca->status = FIXA;
			}
			for(coluna = peca->pos_coluna; coluna < peca->pos_coluna + peca->tamanho; coluna++){
				if(tabuleiro[peca->pos_linha+1][coluna] != 0){
					peca->status = FIXA;
					return;
				}
			}

			break;
		case PECA_Z:
			if(peca->pos_linha + 3 >= NUM_LINHAS && peca->rotacao== 1){
				peca->status = FIXA;
				return;
			}
			if(peca->pos_linha + 2 >= NUM_LINHAS && peca->rotacao == 2){
				peca->status = FIXA;
				return;
			}
			if(peca->rotacao == 1){
				if(tabuleiro[peca->pos_linha+1][peca->pos_coluna-1]!=0){
					peca->status = FIXA;
					return;
				}
				if(tabuleiro[peca->pos_linha+3][peca->pos_coluna] != 0 || tabuleiro[peca->pos_linha+3][peca->pos_coluna+1] != 0){
					peca->status = FIXA;
					return;
				}
			}else if(peca->rotacao ==2){
				if(tabuleiro[peca->pos_linha+2][peca->pos_coluna-1] != 0){
					peca->status = FIXA;
					return;
				}

				if(tabuleiro[peca->pos_linha+1][peca->pos_coluna] != 0 || tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] != 0){
					peca->status = FIXA;
					return;
				}
			}

			break;
		case PECA_T:
			if(peca->rotacao == 1){
				if(peca->pos_linha + 3 >= NUM_LINHAS){
					peca->status = FIXA;
					return;
				}
				if(tabuleiro[peca->pos_linha+3][peca->pos_coluna] != 0){
					peca->status = FIXA;
					return;
				}
				for(coluna = peca->pos_coluna-2;coluna <= peca->pos_coluna+2;coluna++){
					if(coluna != peca->pos_coluna){
						if(tabuleiro[peca->pos_linha+1][coluna] != 0){
							peca->status = FIXA;
							return;						
						}
					}
				}
			}	
			if(peca->rotacao == 2){
				if(peca->pos_linha + 3 >= NUM_LINHAS){
					peca->status = FIXA;
					return;
				}
				if(tabuleiro[peca->pos_linha+3][peca->pos_coluna+1] != 0){
					peca->status = FIXA;
					return;
				}
				for(coluna = peca->pos_coluna-1;coluna <= peca->pos_coluna+1;coluna++){
					if(tabuleiro[peca->pos_linha+1][coluna] != 0 && coluna != peca->pos_coluna+1){
						peca->status = FIXA;
						return;						
					}
				}
			}
			if(peca->rotacao == 3){
				if(peca->pos_linha + 2 >= NUM_LINHAS){
					peca->status = FIXA;
					return;
				}
				if(	tabuleiro[peca->pos_linha+2][peca->pos_coluna-2] != 0 ||
					tabuleiro[peca->pos_linha+2][peca->pos_coluna-1] != 0 ||
					tabuleiro[peca->pos_linha+2][peca->pos_coluna] != 0 || 
					tabuleiro[peca->pos_linha+2][peca->pos_coluna+1] != 0 ||
					tabuleiro[peca->pos_linha+2][peca->pos_coluna+2] != 0 ){
					peca->status = FIXA;
					return;
				}
			}

			if(peca->rotacao == 4){
				if(peca->pos_linha + 3 >= NUM_LINHAS){
					peca->status = FIXA;
					return;
				}
				if(	tabuleiro[peca->pos_linha+3][peca->pos_coluna-1] != 0 || 
					tabuleiro[peca->pos_linha+1][peca->pos_coluna] != 0 ||
					tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] != 0 ){
					peca->status = FIXA;
					return;
				}
			}


			break;
		case PECA_QUADRADO:
			if(peca->pos_linha + 2 >= NUM_LINHAS){
				peca->status = FIXA;
				return;
			}

			if(tabuleiro[peca->pos_linha+2][peca->pos_coluna] !=0 || tabuleiro[peca->pos_linha+2][peca->pos_coluna+1] != 0){
				peca->status = FIXA;
				return;
			}

			break;
		case PECA_L:
			if(peca->rotacao == 1){
				if(peca->pos_linha+3 >= NUM_LINHAS){
					peca->status = FIXA;
					return;
				}
				for(coluna = peca->pos_coluna -1; coluna <= peca->pos_coluna+1;coluna++){
					if(tabuleiro[peca->pos_linha+3][coluna] != 0){
						peca->status = FIXA;	
						return;
					}
				}

			}
			if(peca->rotacao == 2){
				if(peca->pos_linha+3 >= NUM_LINHAS){
					peca->status = FIXA;
					return;
				}
				if(	tabuleiro[peca->pos_linha+3][peca->pos_coluna-1] != 0 ||
					tabuleiro[peca->pos_linha+1][peca->pos_coluna] != 0 || 
					tabuleiro[peca->pos_linha+1][peca->pos_coluna+1] != 0){
					peca->status = FIXA;
					return;
				}
			}
			if(peca->rotacao == 3){
				if(peca->pos_linha+3 >= NUM_LINHAS){
					peca->status = FIXA;
					return;
				}
				if(	tabuleiro[peca->pos_linha+1][peca->pos_coluna-1] != 0 ||
					tabuleiro[peca->pos_linha+1][peca->pos_coluna] != 0 || 
					tabuleiro[peca->pos_linha+3][peca->pos_coluna+1] != 0){
					peca->status = FIXA;
					return;
				}

			}
			if(peca->rotacao == 4){
				if(peca->pos_linha+3 >= NUM_LINHAS){
					peca->status = FIXA;
					return;
				}
				if(	tabuleiro[peca->pos_linha+3][peca->pos_coluna-1] != 0 ||
					tabuleiro[peca->pos_linha+3][peca->pos_coluna] != 0 || 
					tabuleiro[peca->pos_linha+3][peca->pos_coluna+1] != 0){
					peca->status = FIXA;
					return;
				}

			}


			break;
		default:
			break;
	}



}

/*
* Verifica se na linha 6 existe alguma peça, caso exista o jogo acaba.
*
*/

extern int verifica_fim_de_jogo(int tabuleiro[][NUM_COLUNAS]){
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


extern int pontua(int tabuleiro[][NUM_COLUNAS]){

	int linha,coluna,contador_peca=0,pontuacao = 0 ;

	for(linha=0;linha<NUM_LINHAS;linha++){
		contador_peca = 0;
		for(coluna=0;coluna<NUM_COLUNAS;coluna++){
			if(tabuleiro[linha][coluna] != 0){
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
extern void limpa_linha(int tabuleiro[][NUM_COLUNAS],int linha){
	int coluna;
	for(coluna=0;coluna<NUM_COLUNAS;coluna++){
		tabuleiro[linha][coluna] = 0;
		
	}
}

/**
*     Função que faz com que todas as linhas, acima da linha
*
*/


extern void desce_linha(int tabuleiro[][NUM_COLUNAS],int linha){

	int coluna;

	for (coluna=0;coluna<NUM_COLUNAS;coluna++){
		tabuleiro[linha][coluna] = tabuleiro[linha-1][coluna];
	}

}

extern void desce_todas_linhas(int tabuleiro[][NUM_COLUNAS],int linha){

	int i=0;
	limpa_linha(tabuleiro,linha);

	i=linha;
	while(i>1){
		desce_linha(tabuleiro,i);
		i--;	
	}

}
