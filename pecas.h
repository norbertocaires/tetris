#ifndef _pecas_h
#define _pecas_h


/** Inicio das constates que modelarão os tipos de peças */
#define RETA_VERTICAL 1
#define RETA_HORIZONTAL 2
#define PECA_Z 3
#define PECA_T 4
#define PECA_QUADRADO 5
#define PECA_L 6

/** Fim das constates que modelarão os tipos de peças */

#define QTD_PECAS 6 /** Constante que indica a quantidade de tipos de peças que podem existir no jogo*/

/** Inicio das constates que modelarão os status das peças */

#define FIXA 1 /** Status no qual a peça já  alcançou o fundo do tabuleiro e não será mais movimentada*/
#define EM_JOGO 2 /** Status no qual a peça está em jogo e ainda pode ser movimentada */

/** Fim das constates que modelarão os status peças */

/** Início das constatnes que modelarão o tamanho máximo e mínimo que as peças retas poderão ter.*/

#define TAM_PECA_MAX 5
#define TAM_PECA_MIN 3

/** Fim das constatnes que modelarão o tamanho máximo e mínimo que as peças poderão ter.*/


/** Struct que modela uma peça do jogo*/
struct peca{
    int tipo;
    int tamanho;
    int pos_linha;
    int pos_coluna;
    int status;
    int cor;
    int qtd;
    int rotacao;
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
int gera_cor_peca();
int gera_tipo_peca();
void gera_posicao_peca(PECA* peca);
PECA* faz_copia_de_peca(PECA* peca);
void gera_lista_de_qtds(PECAS* pecas, PECAS *nova_lista_qtd);
void inicializa_lista(PECAS /*@out@*/ *pecas);
void adiciona_peca_lista(PECAS *pecas, PECA *peca);


#endif

