/* Unit Test 2: updateCoins() 
		
 Basic Requirements:
- Coin count should change when hand changes
- Coin count must match value of treasure cards in hand
- Bonuses must alter coin count
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
    int ctrlState, testState, count, bonus;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState ctrlGame, testGame;
	
	//Choose kingdom cards, 10 of each
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	//Initialize Game
	initializeGame(numPlayers, k, seed, &ctrlGame);
	//Copy game state
	memcpy(&testGame, &ctrlGame, sizeof(struct gameState));
	
	//Add a copper to hand
	count = testGame.handCount[thisPlayer];
	testGame.hand[thisPlayer][count] = copper;
	testGame.handCount[thisPlayer]++;
	updateCoins(thisPlayer, &testGame, 0);
	
	testState = testGame.coins;
	ctrlState = ctrlGame.coins + 1;//Copper worth 1 coin
	assertAll = assertAll + assertTrue("Assert Copper Added:", testState, ctrlState);
	
	//Add a silver to hand
	testGame.hand[thisPlayer][count] = silver;
	updateCoins(thisPlayer, &testGame, 0);
	
	testState = testGame.coins;
	ctrlState = ctrlGame.coins + 2;//Silver worth 2 coins
	assertAll = assertAll + assertTrue("Assert Silver Added:", testState, ctrlState);
	
	//Add a gold to hand
	testGame.hand[thisPlayer][count] = gold;
	updateCoins(thisPlayer, &testGame, 0);
	
	testState = testGame.coins;
	ctrlState = ctrlGame.coins + 3;//Gold worth 3 coins
	assertAll = assertAll + assertTrue("Assert Gold Added:", testState, ctrlState);
	
	testGame.hand[thisPlayer][count] = 0;//reset hand
	//Add bonus coins
	bonus = 4;
	updateCoins(thisPlayer, &testGame, bonus);
	
	testState = testGame.coins;
	ctrlState = ctrlGame.coins + bonus;
	assertAll = assertAll + assertTrue("Assert Bonus Added:", testState, ctrlState);
	

	#if (PRINT == 1)//Display error result
	if(assertAll == 0){
		printf("--- UNIT TEST SUCCESS: NO ERRORS ---\n");
	} else {
		printf("--- UNIT TEST FAILED: FOUND ERRORS ---\n");
	}
	#endif
	return 0;
}