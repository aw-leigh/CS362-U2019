/*
 * cardtest3.c
 *
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h> //randomize the seed to ensure a different shuffle each time

#define TESTFUNC "endTurn"

int main() {
    srand(time(0));
    
    int seed = rand();
    int numPlayers = 3;  
	struct gameState beforeTestG, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, ambassador,
			baron, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &beforeTestG);

    //display each player's deck
    // for(int i = 0; i < numPlayers; i++){
    //     for(int j = 0; j < beforeTestG.deckCount[i]; j++){
    //         printf("P%d deck card %d: %d\n", i+1, j+1, beforeTestG.deck[i][j]);
    //     }
    // }

    // for(int i = 0; i < treasure_map; i++){
    //     if(deckCardsBefore[i] > 0){
    //         printf("Number of card %d in deck = %d\n", i, deckCardsBefore[i]);
    //     }
    // }

	// copy the game state to a test case
	memcpy(&testG, &beforeTestG, sizeof(struct gameState));

	printf("----------------- Testing Function: %s ----------------\n\n", TESTFUNC);
    
    // ***TEST***
    endTurn(&testG);
    int prevPlayer = testG.whoseTurn - 1;
    int currPlayer = testG.whoseTurn;

    printf("  Previous player hand count = %d, expected %d\n",testG.handCount[prevPlayer], 0);
    assert(testG.handCount[prevPlayer] == 0);

    printf("  Previous player discard count = %d, expected %d\n",testG.discardCount[prevPlayer], beforeTestG.discardCount[prevPlayer]+beforeTestG.handCount[prevPlayer]);
    assert(testG.discardCount[prevPlayer] == beforeTestG.discardCount[prevPlayer]+beforeTestG.handCount[prevPlayer]);
    
    //ensure entire hand was correctly discarded
    for(int i = 0; i < testG.discardCount[prevPlayer]; i++){
        printf("  Previous player discard pile %dth from top = %d, expected %d\n",i+1,
        testG.discard[prevPlayer][testG.discardCount[prevPlayer]-(1+i)], beforeTestG.hand[prevPlayer][4-i]);
        assert(testG.discard[prevPlayer][testG.discardCount[prevPlayer]-(1+i)] == beforeTestG.hand[prevPlayer][4-i]);
    }


    printf("  Current player hand count = %d, expected %d\n",testG.handCount[currPlayer], 5);
    assert(testG.handCount[currPlayer] == 5);
    
    printf("  Current player action count = %d, expected %d\n",testG.numActions, 1);
    assert(testG.numActions == 1);

    printf("  Current player buy count = %d, expected %d\n",testG.numBuys, 1);
    assert(testG.numBuys == 1);

    printf("  Supply piles have not changed\n");
    for(int i = 0; i < treasure_map; i++){
        assert(testG.supplyCount[i] == beforeTestG.supplyCount[i]);
    }

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNC);

    return 0;
}