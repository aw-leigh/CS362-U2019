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

    int cardList[16] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room, copper, silver,
			gold, estate, duchy, province};
    
    int nextPlayer = thisPlayer + 1;

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    //    printf("DECKSIZE: %d\n", G.deckCount[thisPlayer]);

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
   
    int z;
    for (z = 0; z < 100; z++)
      {
	// ----------- TEST 1: duplicates --------------
	printf("TEST 1: duplicate cards\n");
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.deckCount[nextPlayer] = 10;

	int drawnCard = rand() % 16;		
	testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 1] = cardList[drawnCard];
	drawnCard = rand() % 16;
	testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 2] = cardList[drawnCard];
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
	drawnCard = rand() % 16;
	testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 1] = cardList[drawnCard];
	drawnCard = rand() % 16;
	testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 2] = cardList[drawnCard];
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
	drawnCard = rand() % 16;
	testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 1] = cardList[drawnCard];
	drawnCard = rand() % 16;
	testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 2] = cardList[drawnCard];
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
	drawnCard = rand() % 16;
	testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 1] = cardList[drawnCard];
	drawnCard = rand() % 16;
	testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 2] = cardList[drawnCard];
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
	drawnCard = rand() % 16;
	testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 1] = cardList[drawnCard];
	drawnCard = rand() % 16;
	testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 2] = cardList[drawnCard];
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
	drawnCard = rand() % 16;
	testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 1] = cardList[drawnCard];
	drawnCard = rand() % 16;
	testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 2] = cardList[drawnCard];
	printf(" - before Tribute:\n    coins: %d\n    actions: %d\n    handCount: %d\n", testG.coins, testG.numActions, testG.handCount[thisPlayer]);
	printf(" - calling Tribute...\n");
	cardEffect(tribute, choice1, choice2, choice3, &testG,handpos, &bonus);
	printf(" - after Tribute:\n    coins: %d\n    actions: %d\n    handCount: %d\n", testG.coins, testG.numActions, testG.handCount[thisPlayer]);
	// compare
	if (testG.coins == G.coins + 2 && testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2)
	  printf(" - Passed, player receives 2 coins and 2 cards\n");
	else
	  printf(" - Failed, player did not receive 2 coins and 2 cards\n");

      }

    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
    
    return 0;
}
