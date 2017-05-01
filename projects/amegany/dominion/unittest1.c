	/* Unit Test 1: drawCard() 
		
 Basic Requirements:
- Empty draw deck should get all cards from discard pile
- One card should go from current players draw deck to hand
- No state change should occur for any other piles
----------------------------------------------------------------------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
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

int main (){
	//Game variables
	int assertAll = 0;
    int i, ctrlState, testState, ctrlCount, testCount, drawn;
	int discardPile = 0;
	int drawPile = 0;
	char buffer[32];
    int seed = 1000;
    int numPlayers = 2;
	int numPiles = 17;
    int thisPlayer = 0;
	struct gameState ctrlGame, testGame;
	//Choose kingdom cards, 10 of each
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	
	//Initialize Game
	initializeGame(numPlayers, k, seed, &ctrlGame);
	//Copy game state
	memcpy(&testGame, &ctrlGame, sizeof(struct gameState));
	
	//Empty deck should get cards from discard pile
	if(testGame.deckCount[thisPlayer] == 0){//If draw deck is empty
		discardPile = testGame.discardCount[thisPlayer];//Store discard pile count
		printf("%d\n", discardPile);
	}
	//One card moves from deck to hand
	drawn = drawCard(thisPlayer, &testGame);
	assertAll = assertAll + assertTrue("Assert Card Drawn:", drawn, 0);
	//Check that all cards moved from discard pile
	if(discardPile){//If discard pile is empty
		drawPile = testGame.deckCount[thisPlayer];//Store draw pile count
		printf("%d\n", discardPile);
		assertAll = assertAll + assertTrue("Assert Discard Shuffled:", discardPile, drawPile);
	}
	//Get next card in test hand
	testCount = testGame.handCount[thisPlayer];
	testState = testGame.hand[thisPlayer][testCount-1];
	//Get last card in control deck
	ctrlCount = ctrlGame.handCount[thisPlayer];
	ctrlState = ctrlGame.deck[thisPlayer][ctrlCount-1];
	//Should be the same card
	assertAll = assertAll + assertTrue("Assert Same Card:", testState, ctrlState);
	
	//Intentional Bug: testGame.supplyCount[8] = testGame.supplyCount[8] - 1;
	//No state change should occur for any other piles
	for(i=0; i< numPiles; i++){
		memset(buffer, '\0', sizeof(buffer));
		sprintf(buffer, "Assert Supply Count %d:", i);
		assertAll = assertAll + assertTrue(buffer, ctrlGame.supplyCount[i], testGame.supplyCount[i]);
	}
	#if (PRINT == 1)//Display error result
	if(assertAll == 0){
		printf("--- UNIT TEST SUCCESS: NO ERRORS ---\n");
	} else {
		printf("--- UNIT TEST FAILED: FOUND ERRORS ---\n");
	}
	#endif
	return 0;
}