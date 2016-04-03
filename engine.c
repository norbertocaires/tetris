#include <ncurses.h>

void inicia_ncurses(){
	initscr();
}

void finaliza_ncurses(){
	endwin();
}

int pega_input(){
	return getchar();
}
