/*
 * cardtest4.c
 *
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNC "drawCard"

int main() {
   
    int seed = rand();
    int numPlayers = 2;  
	struct gameState beforeTestG, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, ambassador,
			baron, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &beforeTestG);

    //set P1's deck to sequential cards starting from 11
    for(int i = 0; i < beforeTestG.deckCount[0]; i++){
        beforeTestG.deck[0][i] = 11+i;
    }

	// copy the game state to a test case
	memcpy(&testG, &beforeTestG, sizeof(struct gameState));

    //uncomment to show P1's hand and deck
    // for(int i = 0; i < testG.handCount[0]; i++){
    //     printf("P1 hand card %d: %d\n", i+1, testG.hand[0][i]);
    // }
    for(int i = 0; i < testG.deckCount[0]; i++){
        printf("P1 deck card %d: %d\n", i+1, testG.deck[0][i]);
    }


	printf("----------------- Testing Function: %s ----------------\n\n", TESTFUNC);
    
    // ***TEST***
    printf("  Setting P1's deck to: 15 14 13 12 11\n\n");

    printf("  Drawing a card...\n");
    drawCard(0, &testG);

    printf("  Top of P1's hand = %d, expected = %d\n",testG.hand[0][testG.handCount[0]-1], 15);
    assert(testG.hand[0][testG.handCount[0]-1] == 15);
    printf("  Top of P1's deck = %d, expected = %d\n\n",testG.deck[0][testG.deckCount[0]-1], 14);
    assert(testG.deck[0][testG.deckCount[0]-1] == 14);

    printf("  Drawing a card...\n");
    drawCard(0, &testG);

    printf("  Top of P1's hand = %d, expected = %d\n",testG.hand[0][testG.handCount[0]-1], 14);
    assert(testG.hand[0][testG.handCount[0]-1] == 14);
    printf("  Top of P1's deck = %d, expected = %d\n\n",testG.deck[0][testG.deckCount[0]-1], 13);
    assert(testG.deck[0][testG.deckCount[0]-1] == 13);

    printf("  Top of P1's hand = %d, expected = %d\n",testG.hand[0][testG.handCount[0]-1], 14);
    assert(testG.hand[0][testG.handCount[0]-1] == 14);
    printf("  Top of P1's deck = %d, expected = %d\n\n",testG.deck[0][testG.deckCount[0]-1], 13);
    assert(testG.deck[0][testG.deckCount[0]-1] == 13);

    printf("  Drawing two cards...\n");
    drawCard(0, &testG);
    drawCard(0, &testG);

    printf("  Top of P1's hand = %d, expected = %d\n",testG.hand[0][testG.handCount[0]-1], 12);
    assert(testG.hand[0][testG.handCount[0]-1] == 12);
    printf("  Top of P1's deck = %d, expected = %d\n\n",testG.deck[0][testG.deckCount[0]-1], 11);
    assert(testG.deck[0][testG.deckCount[0]-1] == 11);

    printf("  Supply piles have not changed\n");
    for(int i = 0; i < treasure_map; i++){
        assert(testG.supplyCount[i] == beforeTestG.supplyCount[i]);
    }

    printf("  P2's deck has not changed\n");
    for(int i = 0; i < beforeTestG.deckCount[1]; i++){
        assert(testG.deck[1][i] == beforeTestG.deck[1][i]);
    }

    printf("  P2's hand has not changed\n");
    for(int i = 0; i < beforeTestG.deckCount[1]; i++){
        assert(testG.hand[1][i] == beforeTestG.hand[1][i]);
    }

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNC);

    return 0;
}