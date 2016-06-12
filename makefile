all :	programa testePecas testeEngine  testePlacar clear

programa: engine.o tela.o pecas.o placar.o
	gcc main.c engine.o tela.o pecas.o placar.o -o tetris -lncurses -lpthread

testePecas: testePecas.o pecas.o
	gcc -I./CUnit -L./CUnit testePecas.o pecas.o -lcunit -o testePecas -lncurses

testeEngine: testeEngine.o pecas.o pecas.h engine.o
	gcc -I./CUnit -L./CUnit testeEngine.o pecas.o engine.o -lcunit -o testeEngine -lncurses

testePlacar: testePlacar.o placar.o
	gcc -I./CUnit -L./CUnit testePlacar.o placar.o -lcunit -o testePlacar -lncurses

pecas.o: pecas.c pecas.h
	gcc -c pecas.c -Wall -Wextra

tela.o: tela.c tela.h
	gcc -c tela.c -Wall -Wextra

engine.o: engine.c engine.h
	gcc -c engine.c -Wall -Wextra

placar.o: placar.c placar.h
	gcc -c placar.c -Wall -Wextra

testePecas.o: testePecas.c testePecas.h
		gcc -c testePecas.c testePecas.h -Wall -Wextra

testeEngine.o: testeEngine.c testeEngine.h pecas.o
		gcc -c testeEngine.c testeEngine.h -Wall -Wextra

testePlacar.o: testePlacar.c testePlacar.h placar.o
		gcc -c testePlacar.c testePlacar.h -Wall -Wextra

clear:
	rm *.o
