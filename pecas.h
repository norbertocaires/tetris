#ifndef _pecas_h
#define _pecas_h




// Inicio das constates que modelarão os tipos de peças */
#define RETA_VERTICAL 1
#define RETA_HORIZONTAL 2
#define PECA_Z 3
#define PECA_T 4
#define PECA_QUADRADO 5
#define PECA_L 6

// Fim das constates que modelarão os tipos de peças */

#define QTD_PECAS 6 // Constante que indica a quantidade de tipos de peças que podem existir no jogo*/

// Inicio das constates que modelarão os status das peças */

#define FIXA 1 //Status no qual a peça já  alcançou o fundo do tabuleiro e não será mais movimentada*/
#define EM_JOGO 2 // Status no qual a peça está em jogo e ainda pode ser movimentada */

//Fim das constates que modelarão os status peças */

// Início das constatnes que modelarão o tamanho máximo e mínimo que as peças retas poderão ter.

#define TAM_PECA_MAX 5
#define TAM_PECA_MIN 3

// Fim das constatnes que modelarão o tamanho máximo e mínimo que as peças poderão ter.


/** Struct que modela uma peça do jogo*/
struct peca{
    int tipo; /**< representa o tipo de peca. Os tipos estão listados no arquivo pecas.h*/
    int tamanho; /**< representa o tamanho de peca. Somente as pecas retas tem tamanho variável*/
    int pos_linha; /**< representa linhas em que a peça está*/
    int pos_coluna; /**< representa a coluna em que a peça está*/
    int status; /**< representa o status da peça, que pode ser FIXa ou EM_JOGO*/
    int cor; /**< representa a cor da peça*/
    int qtd; /**< representa a de peças, daquele tipo que foram geradas no jogo*/
    int rotacao; /**< representa o estado de rotação da peça*/
    struct peca *proximo; /**< aponta para a pŕoxima peça, em uma lista de peças*/
};
typedef struct peca PECA;

/* Struct que modela uma lista de pecas*/
typedef struct pecas {
	int tamanho; /**< representa o tamanho da lista*/
	struct peca *primeiro; /**< ponteiro que aponta para o primeiro nó da lista*/
	struct peca *ultimo; /**< ponteiro que aponta para o último nó da lista*/
} PECAS;

// Inicio funções relaciondas ao módulo Pecas */

PECA* gera_peca();
int gera_tamanho_peca();
int gera_cor_peca();
int gera_tipo_peca();
void gera_posicao_peca(PECA* peca);
PECA* faz_copia_de_peca(PECA* peca);
void gera_lista_de_qtds(PECAS* pecas, PECAS *nova_lista_qtd);
void inicializaLista(PECAS /*@out@*/ *pecas);
void adicionaPecaLista(PECAS *pecas, PECA *peca);


#endif

