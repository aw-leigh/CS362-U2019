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

int main() {
   
    int seed = rand();
    int numPlayers = 4;  
	struct gameState beforeTestG, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, ambassador,
			baron, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &beforeTestG);

    //remove all victory points from play
    for(int i = 1; i < numPlayers; i++){
        for(int j = 0; j < 10; j++){
            beforeTestG.deck[i][j] = 10;
        }
    }

    for(int i = 0; i < 5; i++){
        beforeTestG.hand[0][i] = 10;
        beforeTestG.deck[0][i] = 10;
    }

	// copy the game state to a test case
	memcpy(&testG, &beforeTestG, sizeof(struct gameState));

	printf("----------------- Testing Function: %s ----------------\n\n", TESTFUNC);
    
    // ***TEST***
    
    int players[4] = {0};
    getWinners(players, &testG);

    printf(" On P1's turn:\n");
    printf("  Everyone tied = everyone but P1 wins\n");
    for(int i = 0; i < numPlayers; i++){
        if(i == 0){
            assert(players[i] != 1);
        }
        else{
            assert(players[i] == 1);
        }
    }

    testG.deck[1][0] = 3;
    printf("  P1: 0, P2: 6, P3: 0, P4: 0 = P2 wins\n");    
    getWinners(players, &testG);
    for(int i = 0; i < numPlayers; i++){
        if(i != 1){
            assert(players[i] != 1);
        }
        else{
            assert(players[i] == 1);
        }
    }

    testG.deck[3][0] = 3;
    printf("  P1: 0, P2: 6, P3: 0, P4: 6 = P2 and P4 win\n\n");    
    getWinners(players, &testG);
    assert(players[0] != 1 && players[1] == 1 && players[2] != 1 && players[3] == 1);

    endTurn(&testG);

    printf(" On P2's turn:\n");
    testG.deck[3][0] = 3;
    printf("  P1: 0, P2: 6, P3: 0, P4: 6 = P4 wins\n");    
    getWinners(players, &testG);
    assert(players[0] != 1 && players[1] != 1 && players[2] != 1 && players[3] == 1);

    // for(int i = 0; i < numPlayers; i++){
    //     printf("Player %d win status: %d\n", i+1, players[i]);
    //     printf("Player %d deck hand discard: %d %d %d\n", i+1, testG.deckCount[i], testG.handCount[i], testG.discardCount[i]);
    // }

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNC);

    return 0;
}