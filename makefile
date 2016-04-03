all :	programa clear

programa: engine.o tela.o pecas.o
	gcc main.c engine.o tela.o pecas.o -o tetris -lncurses

pecas.o: pecas.c pecas.h
	gcc -c pecas.c -Wall -Wextra

tela.o: tela.c tela.h
	gcc -c tela.c -Wall -Wextra

engine.o: engine.c engine.h
	gcc -c engine.c -Wall -Wextra

clear:
	rm *.o
