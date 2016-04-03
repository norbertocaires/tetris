#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define reta_vertical "ooooo"
#define reta_horizontal "o\no\no\no\no"
#define qtd_pecas 2

char* sorteia_peca(){
	srand( (unsigned)time(NULL) );
	int i = rand()%2;

	switch( i ){
		case 0:
			return reta_vertical;
		case 1:
			return reta_horizontal;
		default:
			return "ERRO";
	}

}
