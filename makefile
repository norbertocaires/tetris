all :	programa testePecas testeEngine clear

programa: engine.o tela.o pecas.o
	gcc main.c engine.o tela.o pecas.o -o tetris -lncurses -lpthread

testePecas: testePecas.o pecas.o
	gcc -I./CUnit -L./CUnit testePecas.o pecas.o -lcunit -o testePecas -lncurses

testeEngine: testeEngine.o pecas.o pecas.h engine.o
	gcc -I./CUnit -L./CUnit testeEngine.o pecas.o engine.o -lcunit -o testeEngine -lncurses

pecas.o: pecas.c pecas.h
	gcc -c pecas.c -Wall -Wextra

tela.o: tela.c tela.h
	gcc -c tela.c -Wall -Wextra

engine.o: engine.c engine.h
	gcc -c engine.c -Wall -Wextra

testePecas.o: testePecas.c testePecas.h
		gcc -c testePecas.c testePecas.h -Wall -Wextra

testeEngine.o: testeEngine.c testeEngine.h pecas.o
		gcc -c testeEngine.c testeEngine.h -Wall -Wextra

clear:
	rm *.o
