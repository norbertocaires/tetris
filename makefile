all :	tetris teste clear

programa: engine.o tela.o pecas.o
	gcc main.c engine.o tela.o pecas.o -o tetris -lncurses

teste: testePecas.o pecas.o
	gcc -I./CUnit -L./CUnit testePecas.o pecas.o -lcunit -o teste -lncurses

pecas.o: pecas.c pecas.h
	gcc -c pecas.c -Wall -Wextra

tela.o: tela.c tela.h
	gcc -c tela.c -Wall -Wextra

engine.o: engine.c engine.h
	gcc -c engine.c -Wall -Wextra

testePecas.o: testePecas.c testePecas.h
		gcc -c testePecas.c testePecas.h -Wall -Wextra
clear:
	rm *.o
