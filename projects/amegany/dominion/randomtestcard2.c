/* Random Tester 2: Village */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "rngs.h"
// set PRINT to 0 to remove printfs from output
#define PRINT 0

int assertTrue(char* msg, int a, int b){
	#if (PRINT == 1)
	printf("%s", msg);
	#endif
	if(a == b){
		#if (PRINT == 1)
		printf("Passed\n");
		#endif
		return 0;
	} else {
		#if (PRINT == 1)
		printf("Failed\n");
		#endif
		return 1;
	}
}

int testVillage(struct gameState *ctrlGame, int thisPlayer, int handpos){
	//Game variables
	int assertAll = 0;
    int ctrlState, testState;
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	struct gameState testGame;
	
	//Copy game state
	memcpy(&testGame, ctrlGame, sizeof(struct gameState));
	//Play Card
	cardEffect(village, choice1, choice2, choice3, &testGame, handpos, &bonus);
	
	//Card from draw deck is added to hand
	testState = testGame.hand[thisPlayer][testGame.handCount[thisPlayer] - 1];
	ctrlState = ctrlGame->deck[thisPlayer][ctrlGame->deckCount[thisPlayer] - 1];
	assertAll = assertAll + assertTrue("Assert Same Card:", testState, ctrlState);
	
	//Player gains 2 actions
	testState = testGame.numActions;
	ctrlState = ctrlGame->numActions + 2;
	assertAll = assertAll + assertTrue("Assert +Actions:", testState, ctrlState);
	
	//Played card discarded
	testState = testGame.discard[thisPlayer][testGame.discardCount[thisPlayer] -1];
	ctrlState = ctrlGame->hand[thisPlayer][handpos];
	assertAll = assertAll + assertTrue("Assert Card Discarded:", testState, ctrlState);
	
	#if (PRINT == 1)//Display error result
	if(assertAll == 0){
		printf("--- CARD TEST SUCCESS: NO ERRORS ---\n");
	} else {
		printf("--- CARD TEST FAILED: FOUND ERRORS ---\n");
	}
	#endif
	return assertAll;
}

int main(){
	int result = 0;
	int test, player;
	int handpos = 0;
	struct gameState ctrlGame;
	
	//Initialize Game
	int seed = 1000;
	int numPlayers = MAX_PLAYERS;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	initializeGame(numPlayers, k, seed, &ctrlGame);
	
	srand(time(NULL));
	int numTests = 1000;
	//Fill state variables with random values
	for(test = 0; test < numTests; test++){
		player = rand() % MAX_PLAYERS;
		ctrlGame.handCount[player] = rand() % MAX_HAND;
		if (ctrlGame.handCount[player] >= 1){
			handpos = rand() % (ctrlGame.handCount[player]);
		}
		ctrlGame.deckCount[player] = rand() % MAX_DECK;
		ctrlGame.discardCount[player] = rand() % MAX_DECK;
		ctrlGame.numActions = rand() % 4;
		
		result += testVillage(&ctrlGame, player, handpos);
	}
	//Display error result
	printf("Number of tests: %d\n", test);
	if(result == 0){
		printf("--- RANDOM TEST SUCCESS: NO ERRORS ---\n");
	} else {
		printf("--- RANDOM TEST FAILED: FOUND ERRORS ---\n");
	}
	return 0;
}