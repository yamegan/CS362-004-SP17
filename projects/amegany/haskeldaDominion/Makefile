CFLAGS = -Wall -fpic -coverage -lm

default: playdom player cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard1 randomtestcard2 randomtestadventurer

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
		
cardtest1: cardtest1.c dominion.o rngs.o
		gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
		
cardtest2: cardtest2.c dominion.o rngs.o
		gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
		
cardtest3: cardtest3.c dominion.o rngs.o
		gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
		
cardtest4: cardtest4.c dominion.o rngs.o
		gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
		
unittestresults.out: cardtest1 cardtest2 cardtest3 cardtest4	
	echo "cardtest1.c:" >> unittestresults.out
	cardtest1 >> unittestresults.out
	gcov cardtest1.c >> unittestresults.out
	
	echo "cardtest2.c:" >> unittestresults.out
	cardtest2 >> unittestresults.out
	gcov cardtest2.c >> unittestresults.out
	
	echo "cardtest3.c:" >> unittestresults.out
	cardtest3 >> unittestresults.out
	gcov cardtest3.c >> unittestresults.out
	
	echo "cardtest4.c:" >> unittestresults.out
	cardtest4 >> unittestresults.out
	gcov cardtest4.c >> unittestresults.out
		
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
	rm unittestresults.out randomtestresults.out

cleanall:
	rm -f *.o *.exe *.gcov *.gcda *.gcno *.out playdom player cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard1 randomtestcard2 randomtestadventurer
