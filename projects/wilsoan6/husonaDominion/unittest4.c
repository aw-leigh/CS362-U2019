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

#define TESTCARD "tribute"

int main() {
    int tributeRevealedCards[2] = {-1, -1};
    int numTreasure = 0, numAction = 0, numVictory = 0;

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;  
	struct gameState afterSetupG, beforeSetupG, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, ambassador,
			baron, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &beforeSetupG);

    int currentPlayer = beforeSetupG.whoseTurn;
    int nextPlayer = currentPlayer + 1;  

    // set the first card in player's hand to be a tribute
    // with seed 1000, hand should be: tribute copper estate copper copper
    beforeSetupG.hand[currentPlayer][0] = tribute;

    // uncomment the below to check initial hand
    // for(int i = 0; i < beforeSetupG.handCount[currentPlayer]; i++){
    //     printf("%d \n", beforeSetupG.hand[currentPlayer][i]);
    // } 


	printf("----------------- Testing Card: %s ----------------\n\n", TESTCARD);

	// ----------- TEST 1: discards 1 or 2 cards with enough in supply for everyone --------------
	printf("TEST 1: next player has 2+ cards\n"); 
    
    // ***SETUP***

    // copy the un-setup state to a new test case
    // not really needed in this case, but would be useful if we were going to change
    // the supply counts in further tests
	memcpy(&afterSetupG, &beforeSetupG, sizeof(struct gameState));

    //P2 deck:  adventurer, estate, estate, copper, copper, copper, 
    //          copper, estate, copper, copper, 
    afterSetupG.deck[nextPlayer][afterSetupG.deckCount[nextPlayer]-1] = copper;
    afterSetupG.deck[nextPlayer][afterSetupG.deckCount[nextPlayer]-2] = adventurer;

    // printf("  P2 deck count : %d\n",afterSetupG.deckCount[nextPlayer]);
    // for(int i = afterSetupG.deckCount[nextPlayer] - 1; i >= 0 ; i--){
    //     printf("  P2 deck card %d: %d\n",10-i,afterSetupG.deck[nextPlayer][i]);
    // }

    // ***TEST***

    // copy the game state to a test case
	memcpy(&testG, &afterSetupG, sizeof(struct gameState));
	cardEffect_tribute(testG.hand[currentPlayer][0], choice1, choice2, choice3, &testG, handpos, &bonus, tributeRevealedCards);

    // printf("P2 deck count: %d\n",testG.deckCount[nextPlayer]);
    // for(int i = 0; i < testG.deckCount[nextPlayer]; i++){
    //     printf("P2 deck card %d:%d\n",i,testG.deck[nextPlayer][i]);
    // }
    printf("  Revealed cards: %d, %d\n", tributeRevealedCards[0], tributeRevealedCards[1]);

    printf("  P2 discard top = %d, expected = %d\n", testG.discard[nextPlayer][testG.discardCount[nextPlayer] - 1],
                                                     afterSetupG.deck[nextPlayer][afterSetupG.deckCount[nextPlayer] - 2]);
    assert(testG.discard[nextPlayer][testG.discardCount[nextPlayer] - 1] == afterSetupG.deck[nextPlayer][afterSetupG.deckCount[nextPlayer] - 2]);
    
    printf("  P2 discard 2nd top = %d, expected = %d\n",testG.discard[nextPlayer][testG.discardCount[nextPlayer] - 2],
                                                        afterSetupG.deck[nextPlayer][afterSetupG.deckCount[nextPlayer] - 1]);
    assert(testG.discard[nextPlayer][testG.discardCount[nextPlayer] - 2] == afterSetupG.deck[nextPlayer][afterSetupG.deckCount[nextPlayer] - 1]);

    //count how much stuff player is supposed to recieve
    if(tributeRevealedCards[0] == copper || 
       tributeRevealedCards[0] == silver || 
       tributeRevealedCards[0] == gold)
    {
        numTreasure++;
    }
    else if(tributeRevealedCards[0] == estate || 
            tributeRevealedCards[0] == duchy || 
            tributeRevealedCards[0] == province || 
            tributeRevealedCards[0] == gardens || 
            tributeRevealedCards[0] == great_hall)
    {
        numVictory++;
    }
    else if(tributeRevealedCards[0] != curse && tributeRevealedCards[0] != -1){
        numAction++;
    }

    if((tributeRevealedCards[1] != -1) && (tributeRevealedCards[1] != tributeRevealedCards[0]))
    {
        if( tributeRevealedCards[1] == copper || 
            tributeRevealedCards[1] == silver || 
            tributeRevealedCards[1] == gold)
        {
            numTreasure++;
        }
        else if(tributeRevealedCards[1] == estate || 
            tributeRevealedCards[1] == duchy || 
            tributeRevealedCards[1] == province || 
            tributeRevealedCards[1] == gardens || 
            tributeRevealedCards[1] == great_hall)
        {
            numVictory++;
        }
        else if(tributeRevealedCards[0] != curse){
            numAction++;
        }        
    }

    printf("  Revealed cards: Action = %d, Victory = %d, Treasure = %d\n", numAction, numVictory, numTreasure);

    printf("  Actions before = %d, after = %d, expected = %d\n", afterSetupG.numActions, testG.numActions, afterSetupG.numActions + (numAction * 2));
    assert(testG.numActions == afterSetupG.numActions + (numAction * 2));
  
    printf("  Cards   before = %d, after = %d, expected = %d\n", afterSetupG.handCount[currentPlayer], testG.handCount[currentPlayer], afterSetupG.handCount[currentPlayer] + (numVictory * 2) - 1);
    assert(testG.handCount[currentPlayer] == afterSetupG.handCount[currentPlayer] + (numVictory * 2) - 1);
    
    printf("  Coins   before = %d, after = %d, expected = %d\n", afterSetupG.coins, testG.coins, afterSetupG.coins + (numTreasure * 2));
    assert(testG.coins == afterSetupG.coins + (numTreasure * 2));
  
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

    return 0;
}