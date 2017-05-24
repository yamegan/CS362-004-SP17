/* Random Tester 1: Smithy */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include<time.h>
#include <stdlib.h>
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
int numCardsHand(int player, int card, struct gameState *state) {
	int i;
	int count = 0;
	for (i = 0; i < state->handCount[player]; i++){
		if (state->hand[player][i] == card) count++;
	}
	return count;
}
int testSmithy(struct gameState *ctrlGame, int thisPlayer, int handpos) {
	//Game variables
	int assertAll = 0;
    int i, ctrlState, testState, handDeck;
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int numPlayers = MAX_PLAYERS;
	int discarded = 1;
	char buffer[32];
	struct gameState testGame;
	
	//Copy game state
	memcpy(&testGame, ctrlGame, sizeof(struct gameState));	
	//Play Card
	cardEffect(smithy, choice1, choice2, choice3, &testGame, handpos, &bonus);
	
	//Current player should receive exactly 3 cards
	testState = testGame.handCount[thisPlayer];
	ctrlState = ctrlGame->handCount[thisPlayer] + 3 - discarded;
	assertAll = assertAll + assertTrue("Assert Hand Count:", testState, ctrlState);
	
	//3 cards should come from his own draw deck
	handDeck = ctrlGame->deckCount[thisPlayer] + ctrlGame->handCount[thisPlayer];
	for(i=0; i< handDeck; i++){ //Test for equal amonts of each card before and after draw
		testState = numCardsDeck(thisPlayer, i, &testGame) + numCardsHand(thisPlayer, i, &testGame);
		ctrlState = numCardsDeck(thisPlayer, i, ctrlGame) + numCardsHand(thisPlayer, i, ctrlGame);
		assertAll = assertAll + assertTrue("Assert Number of Cards:", testState, ctrlState);
	}
	//No state change should occur for other players.
	for(i=1; i< numPlayers; i++){
		memset(buffer, '\0', sizeof(buffer));
		sprintf(buffer, "Assert Player %d Hand Stasis:", i);
		assertAll = assertAll + assertTrue(buffer, ctrlGame->handCount[i], testGame.handCount[i]);
		memset(buffer, '\0', sizeof(buffer));
		sprintf(buffer, "Assert Player %d Deck Stasis:", i);
		assertAll = assertAll + assertTrue(buffer, ctrlGame->deckCount[i], testGame.deckCount[i]);
		memset(buffer, '\0', sizeof(buffer));
		sprintf(buffer, "Assert Player %d Discard Stasis:", i);
		assertAll = assertAll + assertTrue(buffer, ctrlGame->discardCount[i], testGame.discardCount[i]);
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
	int  handpos = 0;
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
		result += testSmithy(&ctrlGame, player, handpos);
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