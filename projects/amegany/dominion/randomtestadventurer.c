/* Random Tester 3: Adventurer */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
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
int testAdventurer(struct gameState *ctrlGame,  int thisPlayer){
	//Game variables
	int assertAll = 0;
    int ctrlState, testState;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int discDeck, i;
	struct gameState testGame;
	
	//set deck full of treasure
	for(i=0; i< ctrlGame->deckCount[thisPlayer]-1; i++){
		ctrlGame->deck[thisPlayer][i] = gold;
	}
	//Copy game state
	memcpy(&testGame, ctrlGame, sizeof(struct gameState));
	//Play Card
	cardEffect(adventurer, choice1, choice2, choice3, &testGame, handpos, &bonus);
	
	//2 cards are added to hand
	testState = testGame.handCount[thisPlayer];
	ctrlState = ctrlGame->handCount[thisPlayer] + 2;
	assertAll = assertAll + assertTrue("Assert Cards Added:", testState, ctrlState);
	
	//Cards added are treasure cards
	testState = testGame.hand[thisPlayer][testGame.handCount[thisPlayer]-2]; //First Card
	if(testState == copper || testState == silver || testState == gold){
		testState = 5;
	}
	assertAll = assertAll + assertTrue("Assert Treasure Card:", testState, 5);
	
	testState = testGame.hand[thisPlayer][testGame.handCount[thisPlayer]-1];//Second Card
	if(testState == copper || testState == silver || testState == gold){
		testState = 5;
	}
	assertAll = assertAll + assertTrue("Assert Treasure Card:", testState, 5);
	
	//Non-treasure drawn, moved to discard pile
	discDeck = ctrlGame->deckCount[thisPlayer] + ctrlGame->discardCount[thisPlayer];
	for(i=0; i< discDeck-1; i++){ //Test for equal amonts of each card before and after draw 
		testState = fullDeckCount(thisPlayer, i, &testGame);
		ctrlState = fullDeckCount(thisPlayer, i, ctrlGame);
		assertAll = assertAll + assertTrue("Assert Number of Cards:", testState, ctrlState);
	}
	
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
	struct gameState ctrlGame;
	//Initialize Game
	int seed = 1000;
	int numPlayers = MAX_PLAYERS;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	initializeGame(numPlayers, k, seed, &ctrlGame);
	
	srand(time(NULL));
	int numTests = 100;
	//Fill state variables with random values
	for(test = 0; test < numTests; test++){
		player = rand() % MAX_PLAYERS;
		ctrlGame.handCount[player] = rand() % MAX_HAND;
		ctrlGame.deckCount[player] = rand() % MAX_DECK;
		ctrlGame.discardCount[player] = rand() % MAX_DECK;
		result += testAdventurer(&ctrlGame, 0);
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