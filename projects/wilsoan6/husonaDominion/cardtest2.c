/*
 * cardtest2.c
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

#define TESTFUNC "shuffle"



int main() {
    srand(time(0));
    
    int seed = rand();
    int numPlayers = 3;  
	struct gameState beforeTestG, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, ambassador,
			baron, tribute, smithy, council_room};

    int deckCardsBefore[treasure_map+1] = {0};
    int deckCardsAfter[treasure_map+1] = {0};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &beforeTestG);

    //set each card in each player's deck to a different card
    for(int i = 0; i < numPlayers; i++){
        for(int j = 0; j < beforeTestG.deckCount[i]; j++){
            beforeTestG.deck[i][j] = j+i+1;
        }
    }

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

    for(int player = 0; player < numPlayers; player++){
        
        //theoretically, if a player had 500 card with 2-digit ids, that's 1000 characters
        char deckBefore[1000] = {0};
        char deckAfter[1000] = {0};
        
        shuffle(player, &testG);

        //increment array index that matches deck card number
        //using int array as a hashmap to track deck contents
        for(int i = 0; i < beforeTestG.deckCount[player]; i++){
            deckCardsBefore[beforeTestG.deck[player][i]]++;
        }
        for(int i = 0; i < testG.deckCount[player]; i++){
            deckCardsAfter[testG.deck[player][i]]++;
        }        

        //save deck contents to string in order
        for (int k = 0; k < beforeTestG.deckCount[player]; k++) {
            sprintf(deckBefore + strlen(deckBefore), "%.1d", beforeTestG.deck[player][k]);
        }
        for (int k = 0; k < testG.deckCount[player]; k++) {
            sprintf(deckAfter + strlen(deckAfter), "%.1d", testG.deck[player][k]);
        }
        printf("Player %d\n", player+1);
        printf("  Deck order before = %s\n", deckBefore);
        printf("  Deck order after  = %s\n", deckAfter);

        //if the number of any card type in the deck is different after shuffling, fail the assertion
        printf("  Deck contents before == deck contents after\n");
        for(int i = 0; i < treasure_map; i++){
            if(deckCardsBefore[i] != deckCardsAfter[i]){
                assert(1 == 0);
            }
        }
        
        printf("  Deck order before != deck contents after\n");
        assert(strcmp(deckBefore, deckAfter) != 0);

        //reset arrays for next loop
        for(int i = 0; i < treasure_map; i++){
            deckCardsBefore[i] = 0;
            deckCardsAfter[i] = 0;
        }
    }

    for(int i = 0; i < treasure_map; i++){
        assert(testG.supplyCount[i] == beforeTestG.supplyCount[i]);
    }

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNC);

    return 0;
}