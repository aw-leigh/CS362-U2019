/*
 * unittest1.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "baron"

int main() {
    int estatesBefore = 0;
    int estatesAfter = 0;
    int baronsInHandBefore = 0;
    int baronsInHandAfter = 0;

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
	struct gameState beforeTestG, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, ambassador,
			baron, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &beforeTestG);

    // set the first card in player's hand to be a baron
    // with seed 1000, hand should be: baron copper estate copper copper
    beforeTestG.hand[testG.whoseTurn][0] = baron;

    // uncomment the below to check initial hand

    //for(int i = 0; i < beforeTestG.handCount[beforeTestG.whoseTurn]; i++){
    //    printf("%d \n", beforeTestG.hand[beforeTestG.whoseTurn][i]);
    //} 

	printf("----------------- Testing Card: %s ----------------\n\n", TESTCARD);

	// ----------- TEST 1: discard: +1 buy --------------
	printf("TEST 1: DISCARD = +1 buy\n");    

	// copy the game state to a test case
	memcpy(&testG, &beforeTestG, sizeof(struct gameState));
	choice1 = 1;
	cardEffect(testG.hand[testG.whoseTurn][0], choice1, choice2, choice3, &testG, handpos, &bonus);
   
    printf("  Buys = %d, expected = %d\n", testG.numBuys, beforeTestG.numBuys + 1);
    assert(testG.numBuys == beforeTestG.numBuys + 1);

	// ----------- TEST 2: discard: baron and estate removed from hand --------------
	printf("TEST 2: DISCARD = estate and baron removed from hand\n");    

	// copy the game state to a test case
	memcpy(&testG, &beforeTestG, sizeof(struct gameState));
	choice1 = 1;
    estatesBefore = 0;
    estatesAfter = 0;

    for(int i = 0; i < beforeTestG.handCount[beforeTestG.whoseTurn]; i++){
        if(beforeTestG.hand[beforeTestG.whoseTurn][i] == estate){
            estatesBefore++;
        }
        else if(beforeTestG.hand[beforeTestG.whoseTurn][i] == baron){
            baronsInHandBefore++;
        }
    }    

	cardEffect(testG.hand[testG.whoseTurn][0], choice1, choice2, choice3, &testG, handpos, &bonus);

    for(int i = 0; i < testG.handCount[testG.whoseTurn]; i++){
        if(testG.hand[testG.whoseTurn][i] == estate){
            estatesAfter++;
        }
        else if(testG.hand[testG.whoseTurn][i] == baron){
            baronsInHandAfter++;
        }
    }    

    printf("  Estates in hand: before = %d, after = %d\n", estatesBefore, estatesAfter);    
    assert(estatesBefore == estatesAfter + 1);    
    
    printf("  Barons in hand: before = %d, after = %d\n", baronsInHandBefore, baronsInHandAfter);      
    assert(baronsInHandBefore == baronsInHandAfter + 1);

    printf("  Cards in hand: before = %d, after = %d\n", beforeTestG.handCount[beforeTestG.whoseTurn], testG.handCount[testG.whoseTurn]);
    assert(beforeTestG.handCount[beforeTestG.whoseTurn] == testG.handCount[testG.whoseTurn] + 2);

	// ----------- TEST 3: discard: estate is at the top of the discarded pile --------------
	printf("TEST 3: DISCARD = estate is at the top of the discarded pile\n");   

	memcpy(&testG, &beforeTestG, sizeof(struct gameState));
	choice1 = 1;

	cardEffect(testG.hand[testG.whoseTurn][0], choice1, choice2, choice3, &testG, handpos, &bonus);
    printf("  Discard pile count: %d, expected = %d\n", testG.discardCount[testG.whoseTurn], beforeTestG.discardCount[beforeTestG.whoseTurn] + 1);
    assert(testG.discardCount[testG.whoseTurn] == beforeTestG.discardCount[beforeTestG.whoseTurn] + 1);
    printf("  Top of discard pile: %d, expected = %d\n", testG.discard[testG.whoseTurn][testG.discardCount[testG.whoseTurn] - 1], estate);
    assert(testG.discard[testG.whoseTurn][testG.discardCount[testG.whoseTurn] - 1] == estate);

	// ----------- TEST 4: discard: baron is at the top of the played pile --------------
	printf("TEST 4: DISCARD = baron is at the top of the played pile\n");   

	memcpy(&testG, &beforeTestG, sizeof(struct gameState));
	choice1 = 1;
    
    cardEffect(testG.hand[testG.whoseTurn][0], choice1, choice2, choice3, &testG, handpos, &bonus);
    printf("  Played pile count: %d, expected = %d\n", testG.playedCardCount, beforeTestG.playedCardCount + 1);
    assert(testG.playedCardCount == beforeTestG.playedCardCount + 1);

    printf("  Top of played pile: %d, expected = %d\n", testG.playedCards[testG.playedCardCount - 1], baron);
    assert(testG.playedCards[testG.playedCardCount - 1] == baron);

	// ----------- TEST 5: discard: +4 coins --------------
	printf("TEST 5: DISCARD = +4 coins\n");   

	memcpy(&testG, &beforeTestG, sizeof(struct gameState));
	choice1 = 1;
	cardEffect(testG.hand[testG.whoseTurn][0], choice1, choice2, choice3, &testG, handpos, &bonus);
   
    printf("  Coins = %d, expected = %d\n", testG.coins, beforeTestG.coins + 4);
    assert(testG.coins == beforeTestG.coins + 4);

    // ----------- TEST 6: +1 buy on not discard --------------
	printf("TEST 6: NOT DISCARD = +1 buy\n");    

	memcpy(&testG, &beforeTestG, sizeof(struct gameState));
	choice1 = 0;
	cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);
   
    printf("  Buys = %d, expected = %d\n", testG.numBuys, beforeTestG.numBuys + 1);
    assert(testG.numBuys == beforeTestG.numBuys + 1);

    // ----------- TEST 7: Gain an estate --------------
	printf("TEST 7: NOT DISCARD = +1 estate\n");    
    choice1 = 0;
    estatesBefore = 0;
    estatesAfter = 0;

    for(int i = 0; i < beforeTestG.discardCount[beforeTestG.whoseTurn]; i++){
        if(beforeTestG.discard[beforeTestG.whoseTurn][i] == estate){
            estatesBefore++;
        }
    }  

	cardEffect(testG.hand[testG.whoseTurn][0], choice1, choice2, choice3, &testG, handpos, &bonus);

    for(int i = 0; i < testG.discardCount[testG.whoseTurn]; i++){
        if(testG.discard[testG.whoseTurn][i] == estate){
            estatesAfter++;
        }
    }  

    printf("  Estates in discard: before = %d, after = %d\n", estatesBefore, estatesAfter);    
    assert(estatesBefore == estatesAfter - 1);    
    printf("  Estates in supply: before = %d, after = %d\n", beforeTestG.supplyCount[estate], testG.supplyCount[estate]);
    assert(beforeTestG.supplyCount[estate] == testG.supplyCount[estate] + 1);        


	// ----------- TEST 8: falls back to not discard if no estates --------------
	printf("TEST 8: SPECIAL = falls back to not discard if no estates\n");   

    beforeTestG.hand[testG.whoseTurn][2] = copper;

	memcpy(&testG, &beforeTestG, sizeof(struct gameState));
	choice1 = 1;
    estatesBefore = 0;
    estatesAfter = 0;

    for(int i = 0; i < beforeTestG.handCount[beforeTestG.whoseTurn]; i++){
        if(beforeTestG.hand[beforeTestG.whoseTurn][i] == estate){
            estatesBefore++;
        }
    }

    printf("  Estates in hand before: %d\n", estatesBefore);

	cardEffect(testG.hand[testG.whoseTurn][0], choice1, choice2, choice3, &testG, handpos, &bonus);

    for(int i = 0; i < testG.discardCount[testG.whoseTurn]; i++){
        if(testG.discard[testG.whoseTurn][i] == estate){
            estatesAfter++;
        }
    }  

    printf("  Estates in discard after: %d\n", estatesAfter);

    printf("  Buys = %d, expected = %d\n", testG.numBuys, beforeTestG.numBuys + 1);
    assert(testG.numBuys == beforeTestG.numBuys + 1);
    printf("  Estates in discard: before = %d, after = %d\n", estatesBefore, estatesAfter);    
    assert(estatesBefore == estatesAfter - 1);    
    printf("  Estates in supply: before = %d, after = %d\n", beforeTestG.supplyCount[estate], testG.supplyCount[estate]);
    assert(beforeTestG.supplyCount[estate] == testG.supplyCount[estate] + 1);   

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

    return 0;
}