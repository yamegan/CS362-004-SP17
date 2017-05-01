/* Card Test 4: cardSeaHag()
		
 Basic Requirements:
- Other players must discard top card
- Other players gain a curse card into their draw deck
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
    int i, ctrlState, testState;
    int handpos = 2, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = MAX_PLAYERS;
	//int numPiles = 17;
    //int thisPlayer = 0;
	struct gameState ctrlGame, testGame;
	//Choose kingdom cards, 10 of each
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	//Initialize Game
	initializeGame(numPlayers, k, seed, &ctrlGame);
	//Copy game state
	memcpy(&testGame, &ctrlGame, sizeof(struct gameState)); 
	//Play Card
	cardEffect(sea_hag, choice1, choice2, choice3, &testGame, handpos, &bonus);
	
	//For opponents, top deck card goes to discard pile
	for(i = 1; i < numPlayers; i++){
		testState = testGame.discard[i][testGame.discardCount[i] - 1];
		ctrlState = ctrlGame.deck[i][ctrlGame.deckCount[i] - 1];
		//printf("test %d\n", testState); printf("ctrl %d\n", ctrlState);
		assertAll = assertAll + assertTrue("Assert Same Card:", testState, ctrlState);
	}
	//For opponents, top deck card becomes a curse card
	for(i = 1; i < numPlayers; i++){
		testState = testGame.deck[i][testGame.deckCount[i] - 1];
		ctrlState = curse;
		//printf("test %d\n", testState); printf("ctrl %d\n", ctrlState);
		assertAll = assertAll + assertTrue("Assert Curse Card:", testState, ctrlState);
	}

	#if (PRINT == 1)//Display error result
	if(assertAll == 0){
		printf("--- CARD TEST SUCCESS: NO ERRORS ---\n");
	} else {
		printf("--- CARD TEST FAILED: FOUND ERRORS ---\n");
	}
	#endif
	return 0;
}