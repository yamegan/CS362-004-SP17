/* Card Test 1: cardSmithy()

 Basic Requirements:
- Current player should receive exactly 3 cards.
- 3 cards should come from his own draw deck.
- No state change should occur for other players.
- No state change should occur to the victory card piles and kingdom card piles.
----------------------------------------------------------------------------------------------------*/

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
int numCardsHand(int player, int card, struct gameState *state) {
	int i;
	int count = 0;
	for (i = 0; i < state->handCount[player]; i++){
		if (state->hand[player][i] == card) count++;
	}
	return count;
}

int main(){
	//Game variables
	int assertAll = 0;
    int i, ctrlState, testState, handDeck;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
	int numPiles = 17;
    int thisPlayer = 0;
	int discarded = 1;
	struct gameState ctrlGame, testGame;
	//Choose kingdom cards, 10 of each
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	//Initialize Game
	initializeGame(numPlayers, k, seed, &ctrlGame);
	//Copy game state
	memcpy(&testGame, &ctrlGame, sizeof(struct gameState));
	//Play Card
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handpos, &bonus);
	
	//Current player should receive exactly 3 cards
	testState = testGame.handCount[thisPlayer];
	ctrlState = ctrlGame.handCount[thisPlayer] + 3 - discarded;
	assertAll = assertAll + assertTrue("Assert Hand Count:", testState, ctrlState);
	
	//3 cards should come from his own draw deck
	handDeck = ctrlGame.deckCount[thisPlayer] + ctrlGame.handCount[thisPlayer];
	for(i=0; i< handDeck; i++){ //Test for equal amonts of each card before and after draw
		testState = numCardsDeck(thisPlayer, i, &testGame) + numCardsHand(thisPlayer, i, &testGame);
		ctrlState = numCardsDeck(thisPlayer, i, &ctrlGame) + numCardsHand(thisPlayer, i, &ctrlGame);
		assertAll = assertAll + assertTrue("Assert Number of Cards:", testState, ctrlState);
	}
	
	//No state change should occur for other players.
	for(i=1; i< numPlayers; i++){
		printf("Player %d:\n", i);
		assertAll = assertAll + assertTrue("Assert Hand Stasis:", ctrlGame.handCount[i], testGame.handCount[i]);
		assertAll = assertAll + assertTrue("Assert Deck Stasis:", ctrlGame.deckCount[i], testGame.deckCount[i]);
		assertAll = assertAll + assertTrue("Assert Discard Stasis:", ctrlGame.discardCount[i], testGame.discardCount[i]);
	}
	//No state change should occur to the victory card piles and kingdom card piles.
	for(i=0; i< numPiles; i++){
		printf("Card %d:", i);
		assertAll = assertAll + assertTrue("Assert Supply Count:", ctrlGame.supplyCount[i], testGame.supplyCount[i]);
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