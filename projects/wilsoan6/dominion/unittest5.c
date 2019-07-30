/*
 * unittest1.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "mine"

int main() {
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;  
	struct gameState beforeTestG, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, ambassador,
			baron, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &beforeTestG);

    int currentPlayer = beforeTestG.whoseTurn;

    // set the first card in player's hand to be a tribute
    // with seed 1000, hand should be: mine copper estate copper copper
    beforeTestG.hand[currentPlayer][0] = mine;
    choice1 = 1;
    choice2 = silver;

    // uncomment the below to check initial hand
    // for(int i = 0; i < beforeTestG.handCount[currentPlayer]; i++){
    //     printf("%d \n", beforeTestG.hand[currentPlayer][i]);
    // } 


	printf("----------------- Testing Card: %s ----------------\n\n", TESTCARD);
/* */
	// ----------- TEST 1: discards 1 or 2 cards with enough in supply for everyone --------------
	printf("TEST 1: trash copper for silver, with enough silvers in supply\n"); 
    
    // ***SETUP***

    // copy the initial state to a new test case
	memcpy(&testG, &beforeTestG, sizeof(struct gameState));

    // ***TEST***

	cardEffect(testG.hand[currentPlayer][0], choice1, choice2, choice3, &testG, handpos, &bonus);

    // for(int i = 0; i < testG.handCount[currentPlayer]; i++){
    //     printf("%d \n", testG.hand[currentPlayer][i]);
    // }

    printf("  Player hand top card = %d, expected = %d\n", testG.hand[currentPlayer][0], choice2);
    assert(testG.hand[currentPlayer][0] == choice2);

    printf("  Player discard pile top = %d, expected = %d\n", testG.discard[currentPlayer][testG.discardCount[currentPlayer] - 1],
                                                     beforeTestG.discard[currentPlayer][beforeTestG.discardCount[currentPlayer] - 1]);
    assert(testG.discard[currentPlayer][testG.discardCount[currentPlayer] - 1] == beforeTestG.discard[currentPlayer][beforeTestG.discardCount[currentPlayer] - 1]);
    
    printf("  Player played pile top = %d, expected = %d\n",testG.playedCards[0], mine);
    assert(testG.playedCards[0] == mine);

    printf("  Gained treasure supply before = %d, after = %d, expected = %d\n",beforeTestG.supplyCount[choice2],testG.supplyCount[choice2],beforeTestG.supplyCount[choice2] - 1);
    assert(testG.supplyCount[choice2] == beforeTestG.supplyCount[choice2] - 1);

    printf("  Trashed treasure supply before = %d, after = %d, expected = %d\n",beforeTestG.supplyCount[beforeTestG.hand[currentPlayer][choice1]],
                                                                              testG.supplyCount[beforeTestG.hand[currentPlayer][choice1]],
                                                                              beforeTestG.supplyCount[beforeTestG.hand[currentPlayer][choice1]]);
    assert(beforeTestG.supplyCount[beforeTestG.hand[currentPlayer][choice1]] == testG.supplyCount[beforeTestG.hand[currentPlayer][choice1]]);

    printf("  Supply piles of all non-treasure cards are unchanged\n");
    for(int i = 0; i < treasure_map; i++){
        if(i < copper || i > gold)
            assert(beforeTestG.supplyCount[i] == testG.supplyCount[i]);
    }

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

    return 0;
}