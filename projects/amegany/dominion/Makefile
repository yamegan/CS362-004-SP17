CFLAGS = -Wall -fpic -coverage -lm

default: playdom player randomtestcard1 randomtestcard2 randomtestadventurer

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
		
randomtestcard1: randomtestcard1.c dominion.o rngs.o
		gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
		
randomtestcard2: randomtestcard2.c dominion.o rngs.o
		gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
		
randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
		gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	
randomtestresults.out: randomtestcard1 randomtestcard2 randomtestadventurer
	echo "randomtestcard1.c:" >> randomtestresults.out
	randomtestcard1 >> randomtestresults.out
	gcov randomtestcard1.c >> randomtestresults.out
	
	echo "randomtestcard2.c:" >> randomtestresults.out
	randomtestcard2 >> randomtestresults.out
	gcov randomtestcard2.c >> randomtestresults.out
	
	echo "randomtestadventurer.c:" >> randomtestresults.out
	randomtestadventurer >> randomtestresults.out
	gcov randomtestadventurer.c >> randomtestresults.out
	
clean:
	rm randomtestresults.out

cleanall:
	rm -f *.o *.exe *.gcov *.gcda *.gcno *.out playdom player randomtestcard1 randomtestcard2 randomtestadventurer
