#ifndef _pecas_h
#define _pecas_h


/** Inicio das constates que modelarão os tipos de peças */
#define RETA_VERTICAL 1
#define RETA_HORIZONTAL 2
/** Fim das constates que modelarão os tipos de peças */

#define QTD_PECAS 2 /** Constante que indica a quantidade de tipos de peças que podem existir no jogo*/

/** Inicio das constates que modelarão os status das peças */

#define FIXA 1 /** Status no qual a peça já  alcançou o fundo do tabuleiro e não será mais movimentada*/
#define EM_JOGO 2 /** Status no qual a peça está em jogo e ainda pode ser movimentada */

/** Fim das constates que modelarão os status peças */


/** Struct que modela uma peça do jogo*/
struct peca{
    int tipo;
    int tamanho;
    int pos_linha;
    int pos_coluna;
    int status;
    int cor;
    int qtd;
    struct peca *proximo;
};
typedef struct peca PECA;

/** Struct que modela uma lista de pecas*/
typedef struct pecas {
	int tamanho;
	struct peca *primeiro;
	struct peca *ultimo;
} PECAS;

/** Inicio funções relaciondas ao módulo Pecas */
PECA* gera_peca();
int gera_tamanho_peca();
int gera_tipo_peca();
void gera_posicao_peca(PECA* peca);
void movimenta_peca();
void adicionaPecaLista(PECAS *pecas, PECA *peca);
void inicializaLista(PECAS *pecas);
int gera_cor_peca();

void adicionaPecaLista_qtd(PECAS *pecas, PECA *peca );
void gera_lista_qtd_cada_peca(PECAS pecas, PECAS *nova_lista_qtd);

void adicionaPecaLista_qtd(PECAS *pecas, PECA *peca );
void gera_lista_de_qtds(PECAS* pecas, PECAS *nova_lista_qtd);

/** Fim funções relaciondas ao módulo Pecas */
#endif

