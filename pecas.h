#ifndef _pecas_h
#define _pecas_h


/** Inicio das constates que modelarão os tipos de peças */
#define RETA_VERTICAL 1
#define RETA_HORIZONTAL 2
/** Fim das constates que modelarão os tipos de peças */

/** Inicio das constates que modelarão os status das peças */

#define FIXA 1 /** Status no qual a peça já  alcançou o fundo do tabuleiro e não será mais movimentada*/
#define EM_JOGO 2 /** Status no qual a peça está em jogo e ainda pode ser movimentada */

/** Fim das constates que modelarão os status peças */


/** Struct que modela uma peça do jogo*/
struct peca{
    int tipo;
    int tamanho;
    int pos_x;
    int pos_y;
    int status;
};
typedef struct peca PECA;


/** Inicio funções relaciondas ao módulo Pecas */
PECA gera_peca();
int gera_tamanho_peca();
int gera_tipo_peca();
int gera_posicao_peca(int tipo, int tamanho);
void movimenta_peca();
/** Fim funções relaciondas ao módulo Pecas */
#endif

