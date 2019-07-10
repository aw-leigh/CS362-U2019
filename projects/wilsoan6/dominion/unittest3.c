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

#define TESTCARD "ambassador"

int main() {
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int beforeCards = 0, afterCards = 0, revealedCard = 0;

    int seed = 1000;
    int numPlayers = 2;  
	struct gameState afterSetupG, beforeSetupG, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, ambassador,
			baron, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &beforeSetupG);

    int currentPlayer = beforeSetupG.whoseTurn;
    int nextPlayer = currentPlayer + 1;  

    // set the first card in player's hand to be a ambassador
    // with seed 1000, hand should be: ambassador copper estate copper copper
    beforeSetupG.hand[currentPlayer][0] = ambassador;

    // uncomment the below to check initial hand
    // for(int i = 0; i < beforeSetupG.handCount[currentPlayer]; i++){
    //     printf("%d \n", beforeSetupG.hand[currentPlayer][i]);
    // } 


	printf("----------------- Testing Card: %s ----------------\n\n", TESTCARD);

	// ----------- TEST 1: discards 1 or 2 cards with enough in supply for everyone --------------
	printf("TEST 1: player discards 1 or 2 cards with enough in supply for everyone\n"); 
    
    // ***SETUP***

    // copy the un-setup state to a new test case
    // not really needed in this case, but would be useful if we were going to change
    // the supply counts in further tests
	memcpy(&afterSetupG, &beforeSetupG, sizeof(struct gameState));

    //card to reveal
    choice1 = 1;           //hand position
    revealedCard = copper; //supply enum #

    //number to return to supply
    choice2 = 2; 

    //count how many revealedCard in hand before
    for(int i = 0; i < afterSetupG.handCount[currentPlayer]; i++){
        if(afterSetupG.hand[currentPlayer][i] == revealedCard)
            beforeCards++;
    } 

    // ***TEST***

    // copy the game state to a test case
	memcpy(&testG, &afterSetupG, sizeof(struct gameState));
	cardEffect(testG.hand[currentPlayer][0], choice1, choice2, choice3, &testG, handpos, &bonus);

    for(int i = 0; i < testG.handCount[currentPlayer]; i++){
        if(testG.hand[currentPlayer][i] == revealedCard)
            afterCards++;
    } 

    printf("  Player 1 selected cards in hand before = %d, after = %d, expected = %d\n", beforeCards,
                                                                                         afterCards, 
                                                                                         beforeCards - choice2);
    assert(beforeCards - choice2 == afterCards); 

    printf("  Selected card supply before = %d, after = %d, expected = %d\n", afterSetupG.supplyCount[revealedCard],
                                                                              testG.supplyCount[revealedCard], 
                                                                              afterSetupG.supplyCount[revealedCard] + choice2 - (numPlayers - 1));
    assert(testG.supplyCount[revealedCard] == afterSetupG.supplyCount[revealedCard] + choice2 - (numPlayers - 1));

    printf("  Player 2 discard size before = %d, after = %d, expected = %d\n",afterSetupG.discardCount[nextPlayer],
                                                                              testG.discardCount[nextPlayer],
                                                                              testG.discardCount[nextPlayer] - afterSetupG.discardCount[nextPlayer]);
    assert(testG.discardCount[nextPlayer] - afterSetupG.discardCount[nextPlayer] == 1); 

    printf("  Player 2 discard top card after = %d, expected = %d\n",testG.discard[nextPlayer][testG.discardCount[nextPlayer] - 1], revealedCard);
    assert(testG.discard[nextPlayer][testG.discardCount[nextPlayer] - 1] = revealedCard);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

    return 0;
}