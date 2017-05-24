/* Card Test 2: cardAdventurer()

 Basic Requirements:
- Adds 2 treasure cards to hand
- Non-treasure cards drawn are moved from draw deck to discard pile
- New discarded cards should be same from draw deck
---------------------------------------------------------------------------------------*/

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

int numCardsDeck(int player, int card, struct gameState *state) {
	int i;
	int count = 0;
	for (i = 0; i < state->deckCount[player]; i++){
		if (state->deck[player][i] == card) count++;
	}
	return count;
}
int numCardsDiscard(int player, int card, struct gameState *state) {
	int i;
	int count = 0;
	for (i = 0; i < state->discardCount[player]; i++){
		if (state->hand[player][i] == card) count++;
	}
	return count;
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
	int discDeck, i;
	struct gameState ctrlGame, testGame;
	//Choose kingdom cards, 10 of each
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	//Initialize Game
	initializeGame(numPlayers, k, seed, &ctrlGame);
	//Copy game state
	memcpy(&testGame, &ctrlGame, sizeof(struct gameState));
	//Play Card
	cardEffect(adventurer, choice1, choice2, choice3, &testGame, handpos, &bonus);
	
	//2 cards are added to hand
	testState = testGame.handCount[thisPlayer];
	ctrlState = ctrlGame.handCount[thisPlayer] + 2;
	//printf("test %d\n", testState); printf("ctrl %d\n", ctrlState);
	assertAll = assertAll + assertTrue("Assert Cards Added:", testState, ctrlState);
	
	//Cards added are treasure cards
	testState = testGame.hand[thisPlayer][testGame.handCount[thisPlayer]-1]; //First Card
	//printf("test %d\n", testState);
	if(testState == copper || testState == silver || testState == gold){
		testState = 4;
	}
	assertAll = assertAll + assertTrue("Assert Treasure Card:", testState, 4);
	
	testState = testGame.hand[thisPlayer][testGame.handCount[thisPlayer]-2];//Second Card
	//printf("test %d\n", testState);
	if(testState == copper || testState == silver || testState == gold){
		testState = 4;
	}
	assertAll = assertAll + assertTrue("Assert Treasure Card:", testState, 4);
	
	//Non-treasure drawn, moved to discard pile
	discDeck = ctrlGame.deckCount[thisPlayer] + ctrlGame.discardCount[thisPlayer];
	for(i=0; i< discDeck; i++){ //Test for equal amonts of each card before and after draw
		testState = numCardsDeck(thisPlayer, i, &testGame) + numCardsDiscard(thisPlayer, i, &testGame);
		ctrlState = numCardsDeck(thisPlayer, i, &ctrlGame) + numCardsDiscard(thisPlayer, i, &ctrlGame);
		assertAll = assertAll + assertTrue("Assert Number of Cards:", testState, ctrlState);
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