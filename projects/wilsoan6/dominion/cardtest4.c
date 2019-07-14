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

#define TESTFUNC "getWinners"
#define numPlayers 4 //set number of players as a constant so I don't have to allocate memory

int main() {
   
    int seed = rand();
    //int numPlayers = 4;  
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
    int players[numPlayers] = {0};
    getWinners(players, &testG);


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNC);

    return 0;
}