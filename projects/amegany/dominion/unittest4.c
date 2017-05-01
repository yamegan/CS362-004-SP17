/* Unit Test 4: gainCard() 
	
 Basic Requirements:
- New Card must come from existing deck
- Card must go to hand, deck, or discard
- State change should occur for only 'from' pile and 'to' pile
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

int main() {
	//Game variables
	int assertAll = 0;
    int i, ctrlState, testState, newCard;
    int seed = 1000;
	//int numPiles = 17;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState ctrlGame, testGame;
	
	//Choose kingdom cards, 10 of each
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	//Initialize Game
	initializeGame(numPlayers, k, seed, &ctrlGame);
	//Copy game state
	memcpy(&testGame, &ctrlGame, sizeof(struct gameState));
	for(i = 0; i < treasure_map; i++){
		if(ctrlGame.supplyCount[i] > 0){
			//Copy game state
			memcpy(&testGame, &ctrlGame, sizeof(struct gameState));
			//Gain card
			newCard = i;
			gainCard(newCard, &testGame, 0, thisPlayer);
			//Card taken from existing deck
			testState = testGame.supplyCount[i];
			ctrlState = ctrlGame.supplyCount[i] - 1;
			assertAll = assertAll + assertTrue("Assert Card From Deck:", testState, ctrlState);
		}
	}
	//Copy game state
	memcpy(&testGame, &ctrlGame, sizeof(struct gameState));
	//Gain card
	newCard = 2;
	gainCard(newCard, &testGame, 0, thisPlayer);//Discard flag
	//Card added to discard pile
	testState = testGame.discardCount[thisPlayer];
	ctrlState = ctrlGame.discardCount[thisPlayer] + 1;
	assertAll = assertAll + assertTrue("Assert Added to Discard:", testState, ctrlState);
	
	//Copy game state
	memcpy(&testGame, &ctrlGame, sizeof(struct gameState));
	//Gain card
	newCard = 2;
	gainCard(newCard, &testGame, 1, thisPlayer);//Deck flag
	//Card added to draw deck
	testState = testGame.deckCount[thisPlayer];
	ctrlState = ctrlGame.deckCount[thisPlayer] + 1;
	assertAll = assertAll + assertTrue("Assert Added to Deck:", testState, ctrlState);
	
	//Copy game state
	memcpy(&testGame, &ctrlGame, sizeof(struct gameState));
	//Gain card
	newCard = 2;
	gainCard(newCard, &testGame, 2, thisPlayer);//Discard flag
	//Card added to discard pile
	testState = testGame.handCount[thisPlayer];
	ctrlState = ctrlGame.handCount[thisPlayer] + 1;
	assertAll = assertAll + assertTrue("Assert Added to Hand:", testState, ctrlState);
	
	#if (PRINT == 1)//Display error result
	if(assertAll == 0){
		printf("--- UNIT TEST SUCCESS: NO ERRORS ---\n");
	} else {
		printf("--- UNIT TEST FAILED: FOUND ERRORS ---\n");
	}
	#endif

	return 0;
}