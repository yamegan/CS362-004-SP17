/* Card Test 3: cardVillage()
		
 Basic Requirements:
- 1 card from draw deck is added to hand
- Player must gain 2 actions
- Card must then go to discard pile
-------------------------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
// set PRINT to 0 to remove printfs from output
#define PRINT 1

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

int main(){
	//Game variables
	int assertAll = 0;
    int ctrlState, testState;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
	//int numPiles = 17;
    int thisPlayer = 0;
	struct gameState ctrlGame, testGame;
	//Choose kingdom cards, 10 of each
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	//Initialize Game
	initializeGame(numPlayers, k, seed, &ctrlGame);
	//Copy game state
	memcpy(&testGame, &ctrlGame, sizeof(struct gameState));
	//Play Card
	cardEffect(village, choice1, choice2, choice3, &testGame, handpos, &bonus);
	
	//Card from draw deck is added to hand
	testState = testGame.hand[thisPlayer][testGame.handCount[thisPlayer] - 1];
	ctrlState = ctrlGame.deck[thisPlayer][testGame.deckCount[thisPlayer] - 1];
	assertAll = assertAll + assertTrue("Assert Same Card:", testState, ctrlState);
	
	//Player gains 2 actions
	testState = testGame.numActions;
	ctrlState = ctrlGame.numActions + 2;
	assertAll = assertAll + assertTrue("Assert +Actions:", testState, ctrlState);
	
	//Played card discarded
	testState = testGame.discard[thisPlayer][testGame.discardCount[thisPlayer] -1];
	ctrlState = ctrlGame.hand[thisPlayer][handpos];
	//printf("test %d\n", testState); printf("ctrl %d\n", ctrlState);
	assertAll = assertAll + assertTrue("Assert Card Discarded:", testState, ctrlState);
	
	#if (PRINT == 1)//Display error result
	if(assertAll == 0){
		printf("--- CARD TEST SUCCESS: NO ERRORS ---\n");
	} else {
		printf("--- CARD TEST FAILED: FOUND ERRORS ---\n");
	}
	#endif
	return 0;
}