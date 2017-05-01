/* Unit Test 3: discardCard() 
		
 Basic Requirements:
- Must remove current card from hand
- If not trashed, card must appear in played cards pile
- Last card in hand should move to current hand position
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
    int i, ctrlState, testState, curCard;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState ctrlGame, testGame;
	
	//Choose kingdom cards, 10 of each
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	//Initialize Game
	initializeGame(numPlayers, k, seed, &ctrlGame);
	//Discarding each card in hand
	for(i = 0; i < ctrlGame.handCount[thisPlayer]; i++){
		//Copy game state
		memcpy(&testGame, &ctrlGame, sizeof(struct gameState));
		//Choose card for hand position
		curCard = i;
		discardCard(curCard, thisPlayer, &testGame, 0); //Not trashed
		//Card is removed from hand
		testState = testGame.handCount[thisPlayer];
		ctrlState = ctrlGame.handCount[thisPlayer] - 1;
		assertAll = assertAll + assertTrue("Assert Card Removed:", testState, ctrlState);
		//Card added to played pile
		testState = testGame.playedCardCount;
		ctrlState = ctrlGame.playedCardCount + 1;
		assertAll = assertAll + assertTrue("Assert Card Played:", testState, ctrlState);
		//Card moved is the same card
		testState = testGame.playedCards[testGame.playedCardCount - 1];
		ctrlState = ctrlGame.hand[thisPlayer][curCard];
		assertAll = assertAll + assertTrue("Assert Same Card:", testState, ctrlState);
	}
	//Trashing each card in hand
	for(i = 0; i < ctrlGame.handCount[thisPlayer]; i++){
		//Copy game state
		memcpy(&testGame, &ctrlGame, sizeof(struct gameState));
		//Choose card for hand position
		curCard = i;
		discardCard(curCard, thisPlayer, &testGame, 1); //Trashed
		//Card is removed from existence
		testState = fullDeckCount(thisPlayer, testGame.hand[thisPlayer][i], &testGame);
		ctrlState = fullDeckCount(thisPlayer, ctrlGame.hand[thisPlayer][i], &ctrlGame) - 1;
		//printf("test %d\n", testState); printf("ctrl %d\n", ctrlState);
		assertAll = assertAll + assertTrue("Assert Card Trashed:", testState, ctrlState);
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
/*
int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag){
	//if card is not trashed, added to Played pile 
	if (trashFlag < 1){
		//add card to played pile
		state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos]; 
		state->playedCardCount++;
	}

	//set played card to -1
	state->hand[currentPlayer][handPos] = -1;

	//remove card from player's hand
	if ( handPos == (state->handCount[currentPlayer] - 1)){ 	//last card in hand array is played
		//reduce number of cards in hand
		state->handCount[currentPlayer]--;
	}
	else if ( state->handCount[currentPlayer] == 1 ){ //only one card in hand
		//reduce number of cards in hand
		state->handCount[currentPlayer]--;
	}
	else {
		//replace discarded card with last card in hand
		state->hand[currentPlayer][handPos] = state->hand[currentPlayer][ (state->handCount[currentPlayer] - 1)];
		//set last card to -1
		state->hand[currentPlayer][state->handCount[currentPlayer] - 1] = -1;
		//reduce number of cards in hand
		state->handCount[currentPlayer]--;
	}
	return 0;
}*/