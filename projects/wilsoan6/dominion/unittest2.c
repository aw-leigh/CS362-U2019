/*
 * unittest1.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "minion"

int main() {
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

    int seed = 1000;
    int numPlayers = 3;  
	struct gameState beforeTestG, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, ambassador,
			baron, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &beforeTestG);

    int currentPlayer = beforeTestG.whoseTurn;
    int nextPlayer = currentPlayer + 1;  

    // set the first card in player's hand to be a minion
    // with seed 1000, hand should be: minion copper estate copper copper
    beforeTestG.hand[testG.whoseTurn][0] = minion;

    // uncomment the below to check initial hand

    //for(int i = 0; i < beforeTestG.handCount[beforeTestG.whoseTurn]; i++){
    //    printf("%d \n", beforeTestG.hand[beforeTestG.whoseTurn][i]);
    //} 

	printf("----------------- Testing Card: %s ----------------\n\n", TESTCARD);

	// ----------- TEST 1: +1 action --------------
	printf("TEST 1: +1 action\n");    

	// copy the game state to a test case
	memcpy(&testG, &beforeTestG, sizeof(struct gameState));
	choice1 = 1;
	cardEffect(testG.hand[testG.whoseTurn][0], choice1, choice2, choice3, &testG, handpos, &bonus);
   
    printf("  Actions = %d, expected = %d\n", testG.numActions, beforeTestG.numActions + 1);
    assert(testG.numActions == beforeTestG.numActions + 1);

	// ----------- TEST 2: +2 coins --------------
	printf("TEST 2: +2 coins\n");    

	// copy the game state to a test case
	memcpy(&testG, &beforeTestG, sizeof(struct gameState));
	choice1 = 1;

	cardEffect(testG.hand[testG.whoseTurn][0], choice1, choice2, choice3, &testG, handpos, &bonus);
   
    printf("  Coins = %d, expected = %d\n", testG.coins, beforeTestG.coins + 2);
    assert(testG.coins == beforeTestG.coins + 2);
 
	// ----------- TEST 3: discard entire hand and draw 4 --------------
	printf("TEST 3: Discard entire hand and draw 4\n");   
	printf(" Before:\n");   
	printf("  Number of cards in hand, minus the minion = %d\n", beforeTestG.handCount[beforeTestG.whoseTurn] - 1);   
	printf("  Number of cards in discard pile = %d\n", beforeTestG.discardCount[beforeTestG.whoseTurn]);   
	printf("  Number of cards in played pile = %d\n", beforeTestG.discardCount[beforeTestG.whoseTurn]);   

	memcpy(&testG, &beforeTestG, sizeof(struct gameState));
	choice1 = 2;

	cardEffect(testG.hand[testG.whoseTurn][0], choice1, choice2, choice3, &testG, handpos, &bonus);
    printf(" After:\n"); 
    printf("  Discard pile count: %d, expected = %d\n", testG.discardCount[testG.whoseTurn], beforeTestG.discardCount[beforeTestG.whoseTurn] + beforeTestG.handCount[beforeTestG.whoseTurn] - 1);
    assert(testG.discardCount[testG.whoseTurn] == beforeTestG.discardCount[beforeTestG.whoseTurn] + beforeTestG.handCount[beforeTestG.whoseTurn] - 1); //don't count the minion card itself

    printf("  Played pile count: %d, expected = %d\n", testG.playedCardCount, beforeTestG.playedCardCount + 1);
    assert(testG.playedCardCount == beforeTestG.playedCardCount + 1);

    printf("  Top of played pile: %d, expected = %d\n", testG.playedCards[testG.playedCardCount - 1], minion);
    assert(testG.playedCards[testG.playedCardCount - 1] == minion);  

	printf("  Number of cards in hand after = %d, expected = 4\n", testG.handCount[testG.whoseTurn], 4);   
    assert(testG.handCount[testG.whoseTurn] == 4);

	// ----------- TEST 4: opponets with < 5 cards do nothing --------------
	printf("TEST 4: Opponents with < 5 cards do nothing\n");   

    for (int i = 0; i < 4; i++)
    {
        drawCard(nextPlayer, &beforeTestG);
    } 

	memcpy(&testG, &beforeTestG, sizeof(struct gameState));
	choice1 = 2;

   
	printf(" Before:\n"); 
    printf("  Next player hand count = %d\n", beforeTestG.handCount[nextPlayer]);
	printf("  Next player cards in discard pile = %d\n", beforeTestG.discardCount[nextPlayer]);   
	printf("  Next player cards in deck = %d\n", beforeTestG.deckCount[nextPlayer]);

	cardEffect(testG.hand[testG.whoseTurn][0], choice1, choice2, choice3, &testG, handpos, &bonus);

    printf(" After:\n"); 
    printf("  Next player hand count = %d, expected = %d\n", testG.handCount[nextPlayer], beforeTestG.handCount[nextPlayer]);
    assert(testG.handCount[nextPlayer] == beforeTestG.handCount[nextPlayer]);
	printf("  Next player cards in discard pile = %d, expected = %d\n", testG.discardCount[nextPlayer], beforeTestG.discardCount[nextPlayer]);   
    assert(testG.discardCount[nextPlayer] == beforeTestG.discardCount[nextPlayer]);	
    printf("  Next player cards in deck = %d, expected = %d\n", testG.deckCount[nextPlayer], beforeTestG.deckCount[nextPlayer]);   
    assert(testG.deckCount[nextPlayer] == beforeTestG.deckCount[nextPlayer]);	

	// ----------- TEST 5: opponets with 5+ cards discard all and draw 4 --------------
	printf("TEST 5: Opponents with 5+ cards discard entire hand and draw 4\n");   

    for (int i = 0; i < 1; i++)
    {
        drawCard(nextPlayer, &beforeTestG);
    }

    for (int i = 0; i < 7; i++)
    {
        drawCard(nextPlayer + 1, &beforeTestG);
    }     

	memcpy(&testG, &beforeTestG, sizeof(struct gameState));
	choice1 = 2;

   
	printf(" Before:\n"); 
    printf("  Next player hand count = %d\n", beforeTestG.handCount[nextPlayer]);
	printf("  Next player cards in discard pile = %d\n", beforeTestG.discardCount[nextPlayer]);   
	printf("  Next player cards in deck = %d\n", beforeTestG.deckCount[nextPlayer]);
    
    //printf("  Next next player hand count = %d\n", beforeTestG.handCount[nextPlayer+1]);
	//printf("  Next next player cards in discard pile = %d\n", beforeTestG.discardCount[nextPlayer+1]);   
	//printf("  Next next player cards in deck = %d\n", beforeTestG.deckCount[nextPlayer+1]);

	cardEffect(testG.hand[testG.whoseTurn][0], choice1, choice2, choice3, &testG, handpos, &bonus);

    printf(" After:\n"); 
    printf("  Next player hand count = %d, expected = 4\n", testG.handCount[nextPlayer]);
    assert(testG.handCount[nextPlayer] == 4);
	printf("  Next player cards in discard pile = %d, expected = %d\n", testG.discardCount[nextPlayer], beforeTestG.discardCount[nextPlayer] + beforeTestG.handCount[nextPlayer]);   
    assert(testG.discardCount[nextPlayer] == beforeTestG.discardCount[nextPlayer] + beforeTestG.handCount[nextPlayer]);	
    printf("  Next player cards in deck = %d, expected = %d\n", testG.deckCount[nextPlayer], beforeTestG.deckCount[nextPlayer] - 4);   
    assert(testG.deckCount[nextPlayer] == beforeTestG.deckCount[nextPlayer] - 4);	

    //TODO: account for shuffling if next players don't have 4 cards in the deck after discarding
    //printf("  Next next player hand count = %d, expected = 4\n", testG.handCount[nextPlayer+1]);
    //assert(testG.handCount[nextPlayer+1] == 4);
	//printf("  Next next player cards in discard pile = %d, expected = %d\n", testG.discardCount[nextPlayer+1], beforeTestG.discardCount[nextPlayer+1] + beforeTestG.handCount[nextPlayer+1]);   
    //assert(testG.discardCount[nextPlayer+1] == beforeTestG.discardCount[nextPlayer+1] + beforeTestG.handCount[nextPlayer+1]);	
    //printf("  Next next player cards in deck = %d, expected = %d\n", testG.deckCount[nextPlayer+1], beforeTestG.deckCount[nextPlayer+1] - 4);   
    //assert(testG.deckCount[nextPlayer+1] == beforeTestG.deckCount[nextPlayer+1] - 4);	

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

    return 0;
}