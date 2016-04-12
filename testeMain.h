#ifndef _teste_h
#define _teste_h

void adicionar_suite(void);

/*Declaração - Testes unitarios */


void teste_gera_peca();
void teste_geraTamanhoPeca(void);
void teste_geraTipoPeca(void);
void teste_geraPosicao(void);
void teste_umovimenta_peca();
void teste_inicializaLista(PECAS *pecas);
void teste_inicializaLista(PECAS *pecas);
void teste_adicionaPecaLista(PECAS *pecas, PECA *peca);
int  teste_gera_cor_peca();
void teste_adicionaPecaLista_qtd(PECAS *pecas, PECA *peca );
void teste_gera_lista_qtd_cada_peca(PECAS pecas, PECAS *nova_lista_qtd);
void teste_adicionaPecaLista_qtd(PECAS *pecas, PECA *peca );
void teste_gera_lista_de_qtds(PECAS* pecas, PECAS *nova_lista_qtd);

/*Fim declaração testes unitários*/






#endif
