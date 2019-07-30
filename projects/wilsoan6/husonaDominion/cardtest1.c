/*
 * cardtest1.c
 *
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNC "initializeGame"

int main() {
    int seed = 1000;
    int numPlayers = 3;  
	struct gameState testG;
	int k[10] = {adventurer, embargo, village, minion, mine, ambassador,
			baron, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &testG);

    int cardCount = 0;
    int expectedEstates = 0;

	printf("----------------- Testing Function: %s ----------------\n\n", TESTFUNC);
    
    // ***TEST***

    printf("  Number of players = %d, expected = %d\n", testG.numPlayers, numPlayers);
    assert(testG.numPlayers == numPlayers);

    for(int i = adventurer; i < treasure_map; i++){
        if(testG.supplyCount[i] == 10){
            cardCount++;
        }
    }

    printf("  Number of kingdom card piles with 10 cards = %d, expected = %d\n", cardCount, 10);
    assert(cardCount == 10);
    
    printf("  Copper pile size = %d, expected = %d\n", testG.supplyCount[copper], 60 - (7 * numPlayers));
    assert(testG.supplyCount[copper] == 60 - (7 * numPlayers));
    
    if(numPlayers == 2){
        expectedEstates = 8;
    }
    else{
        expectedEstates = 12;
    }

    printf("  Estate pile size = %d, expected = %d\n", testG.supplyCount[estate], expectedEstates);
    assert(testG.supplyCount[estate] == expectedEstates);

    printf("  P1 action count = %d, expected = %d\n", testG.numActions, 1);
    assert(testG.numActions == 1);

    printf("  P1 buys count = %d, expected = %d\n", testG.numBuys, 1);
    assert(testG.numBuys == 1);

    printf("  P1 hand size = %d, expected = %d\n",testG.handCount[testG.whoseTurn], 5);
    assert(testG.handCount[testG.whoseTurn] == 5);

    printf("  P1 deck size = %d, expected = %d\n",testG.deckCount[testG.whoseTurn], 5);
    assert(testG.deckCount[testG.whoseTurn] == 5);

    for(int i = 1; i < numPlayers; i++){
        printf("  P%d hand size = %d, expected = %d\n",i+1,testG.handCount[i], 0);
        assert(testG.handCount[i] == 0);

        printf("  P%d deck size = %d, expected = %d\n",i+1,testG.deckCount[i], 10);
        assert(testG.deckCount[i] == 10);
    }

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNC);

    return 0;
}