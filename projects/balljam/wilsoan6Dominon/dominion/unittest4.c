/*
 * unittest4.c -- Tribute
 *
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "tribute"

int main() { /*
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;*/
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    //    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		 sea_hag, tribute, smithy, council_room};
    
    int nextPlayer = thisPlayer + 1;

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    //    printf("DECKSIZE: %d\n", G.deckCount[thisPlayer]);

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
   
    // ----------- TEST 1: duplicates --------------
    printf("TEST 1: duplicate cards\n");
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deckCount[nextPlayer] = 10;
    testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 1] = silver;
    testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 2] = silver;
    //    printf("%d \n", testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 1]);
    //    printf("%d \n", testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 2]);
    printf(" - before Tribute:\n    coins: %d\n    actions: %d\n    handCount: %d\n", testG.coins, testG.numActions, testG.handCount[thisPlayer]);
    printf(" - calling Tribute...\n");
    cardEffect(tribute, choice1, choice2, choice3, &testG,handpos, &bonus);
    printf(" - after Tribute:\n    coins: %d\n    actions: %d\n    handCount: %d\n", testG.coins, testG.numActions, testG.handCount[thisPlayer]);
    // compare
    if (testG.coins == G.coins + 2)
      printf(" - Passed, player receieved 2 coins from duplicate Silver\n");
    else
      printf(" - Failed, player did not receive 2 coins from duplicate Silver\n");

    
    // ----------- TEST 2: same type --------------
    printf("TEST 2: same type of cards\n");
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deckCount[nextPlayer] = 10;
    testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 1] = baron;
    testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 2] = smithy;
    printf(" - before Tribute:\n    coins: %d\n    actions: %d\n    handCount: %d\n", testG.coins, testG.numActions, testG.handCount[thisPlayer]);
    printf(" - calling Tribute...\n");
    cardEffect(tribute, choice1, choice2, choice3, &testG,handpos, &bonus);
    printf(" - after Tribute:\n    coins: %d\n    actions: %d\n    handCount: %d\n", testG.coins, testG.numActions, testG.handCount[thisPlayer]);
    // compare
    if (testG.numActions == G.numActions + 4)
      printf(" - Passed, player receives 4 actions from 2 action cards\n");
    else
      printf(" - Failed, player did not receive 4 actions from 2 action cards\n");

    // ----------- TEST 3: one duel type --------------
    printf("TEST 3: one duel type\n");
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deckCount[nextPlayer] = 10;
    testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 1] = great_hall;
    testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 2] = baron;
    printf(" - before Tribute:\n    coins: %d\n    actions: %d\n    handCount: %d\n", testG.coins, testG.numActions, testG.handCount[thisPlayer]);
    printf(" - calling Tribute...\n");
    cardEffect(tribute, choice1, choice2, choice3, &testG,handpos, &bonus);
    printf(" - after Tribute:\n    coins: %d\n    actions: %d\n    handCount: %d\n", testG.coins, testG.numActions, testG.handCount[thisPlayer]);
    // compare
    if (testG.numActions == G.numActions + 4 && testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2)
      printf(" - Passed, player receives 4 actions and 2 cards\n");
    else
      printf(" - Failed, player did not receive 4 actions and 2 cards\n");
    
    // ----------- TEST 4: treasure and action --------------
    printf("TEST 4: treasure and action\n");
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deckCount[nextPlayer] = 10;
    testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 1] = copper;
    testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 2] = baron;
    printf(" - before Tribute:\n    coins: %d\n    actions: %d\n    handCount: %d\n", testG.coins, testG.numActions, testG.handCount[thisPlayer]);
    printf(" - calling Tribute...\n");
    cardEffect(tribute, choice1, choice2, choice3, &testG,handpos, &bonus);
    printf(" - after Tribute:\n    coins: %d\n    actions: %d\n    handCount: %d\n", testG.coins, testG.numActions, testG.handCount[thisPlayer]);
    // compare
    if (testG.numActions == G.numActions + 2 && testG.coins == G.coins + 2)
      printf(" - Passed, player receives 2 coins and 2 actions\n");
    else
      printf(" - Failed, player did not receive 2 coins and 2 actions\n");

    // ----------- TEST 5: victory and action --------------
    printf("TEST 5: victory and action\n");
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deckCount[nextPlayer] = 10;
    testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 1] = estate;
    testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 2] = baron;
    printf(" - before Tribute:\n    coins: %d\n    actions: %d\n    handCount: %d\n", testG.coins, testG.numActions, testG.handCount[thisPlayer]);
    printf(" - calling Tribute...\n");
    cardEffect(tribute, choice1, choice2, choice3, &testG,handpos, &bonus);
    printf(" - after Tribute:\n    coins: %d\n    actions: %d\n    handCount: %d\n", testG.coins, testG.numActions, testG.handCount[thisPlayer]);
    // compare
    if (testG.numActions == G.numActions + 2 && testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2)
      printf(" - Passed, player receives 2 actions and 2 cards\n");
    else
      printf(" - Failed, player did not receive 2 actions and 2 cards\n");

    // ----------- TEST 6: treasure and victroy --------------
    printf("TEST 6: treasure and victory\n");
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deckCount[nextPlayer] = 10;
    testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 1] = copper;
    testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 2] = estate;
    printf(" - before Tribute:\n    coins: %d\n    actions: %d\n    handCount: %d\n", testG.coins, testG.numActions, testG.handCount[thisPlayer]);
    printf(" - calling Tribute...\n");
    cardEffect(tribute, choice1, choice2, choice3, &testG,handpos, &bonus);
    printf(" - after Tribute:\n    coins: %d\n    actions: %d\n    handCount: %d\n", testG.coins, testG.numActions, testG.handCount[thisPlayer]);
    // compare
    if (testG.coins == G.coins + 2 && testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2)
      printf(" - Passed, player receives 2 coins and 2 cards\n");
    else
      printf(" - Failed, player did not receive 2 coins and 2 cards\n");

	/*

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: choice1 = 1 = +2 cards --------------
	printf("TEST 1: choice1 = 1 = +2 cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 2;
	xtraCoins = 0;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
	assert(testG.coins == G.coins + xtraCoins);

	// ----------- TEST 2: choice1 = 2 = +2 coins --------------
	printf("TEST 2: choice1 = 2 = +2 coins\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 2;
	cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 0;
	xtraCoins = 2;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
	assert(testG.coins == G.coins + xtraCoins);

	// ----------- TEST 3: choice1 = 3 = trash two cards --------------

	printf("TEST 3: choice1 = 3 = trash two cards\n");
	choice1 = 3;

	// cycle through each eligible combination of 2 cards to trash
	for (i=1; i<G.handCount[thisPlayer]; i++) {
		for (j=i+1; j<G.handCount[thisPlayer]; j++) {

			G.hand[thisPlayer][0] = steward;
			G.hand[thisPlayer][1] = copper;
			G.hand[thisPlayer][2] = duchy;
			G.hand[thisPlayer][3] = estate;
			G.hand[thisPlayer][4] = feast;

			// copy the game state to a test case
			memcpy(&testG, &G, sizeof(struct gameState));

			printf("starting cards: ");
			for (m=0; m<testG.handCount[thisPlayer]; m++) {
				printf("(%d)", testG.hand[thisPlayer][m]);
			}
			printf("; ");

			choice2 = j;
			choice3 = i;
			remove1 = testG.hand[thisPlayer][i];
			remove2 = testG.hand[thisPlayer][j];
			cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

			printf("removed: (%d)(%d); ", remove1, remove2);
			printf("ending cards: ");

			// tests that the removed cards are no longer in the player's hand
			for (m=0; m<testG.handCount[thisPlayer]; m++) {
				printf("(%d)", testG.hand[thisPlayer][m]);
				assert(testG.hand[thisPlayer][m] != remove1);
				assert(testG.hand[thisPlayer][m] != remove2);
			}
			printf(", expected: ");
			for (m=1; m<G.handCount[thisPlayer]; m++) {
				if (G.hand[thisPlayer][m] != G.hand[thisPlayer][i] && G.hand[thisPlayer][m] != G.hand[thisPlayer][j]) {
					printf("(%d)", G.hand[thisPlayer][m]);
				}
			}
			printf("\n");

			// tests for the appropriate number of remaining cards
			newCards = 0;
			xtraCoins = 0;
			discarded = 3;
			if (i==1 && j==2) {
				printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
				printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
			}
			assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
			assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
		}

	}

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	*/
	return 0;
}


