/*
 * unittest5.c -- Mine
 *
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "mine"

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    
    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    // ----------- TEST 1: copper -> silver --------------
    printf("TEST 1: copper -> silver\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.hand[thisPlayer][0] = copper;
    // print hand before call
    printf(" - ");
    for (int i = 0; i < testG.handCount[thisPlayer]; i++)
      printf("%d ", testG.hand[thisPlayer][i]);
    printf("\n");
    choice1 = 0; //trade the copper
    choice2 = 5; //look for silver
    printf(" - calling Mine...\n");
    cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
    // print hand after call
    printf(" - ");
    for (int i = 0; i < testG.handCount[thisPlayer]; i++)
      printf("%d ", testG.hand[thisPlayer][i]);
    printf("\n");
    if (testG.hand[thisPlayer][0] == silver)
      printf(" - Passed, copper to silver\n");
    else
      printf(" - Failed, no copper to silver\n");
    
    // ----------- TEST 2: silver -> gold --------------
    printf("TEST 2: silver -> gold\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.hand[thisPlayer][0] = silver;
    // print hand before call
    printf(" - ");
    for (int i = 0; i < testG.handCount[thisPlayer]; i++)
      printf("%d ", testG.hand[thisPlayer][i]);
    printf("\n");
    choice1 = 0; //trade the silver
    choice2 = 6; //look for gold
    printf(" - calling Mine...\n");
    cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
    // print hand after call
    printf(" - ");
    for (int i = 0; i < testG.handCount[thisPlayer]; i++)
      printf("%d ", testG.hand[thisPlayer][i]);
    printf("\n");
    if (testG.hand[thisPlayer][0] == gold)
      printf(" - Passed, silver to gold\n");
    else
      printf(" - Failed, no silver to gold\n");

    // ----------- TEST 3: gold -> copper --------------
    printf("TEST 3: gold -> copper\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.hand[thisPlayer][0] = gold;
    // print hand before call
    printf(" - ");
    for (int i = 0; i < testG.handCount[thisPlayer]; i++)
      printf("%d ", testG.hand[thisPlayer][i]);
    printf("\n");
    choice1 = 0; //trade the gold
    choice2 = 4; //look for copper
    printf(" - calling Mine...\n");
    cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
    // print hand after call
    printf(" - ");
    for (int i = 0; i < testG.handCount[thisPlayer]; i++)
      printf("%d ", testG.hand[thisPlayer][i]);
    printf("\n");
    if (testG.hand[thisPlayer][0] == copper)
      printf(" - Passed, gold to copper\n");
    else
      printf(" - Failed, no gold to copper\n");

    // ----------- TEST 4: copper -> gold --------------
    printf("TEST 4: copper -> gold\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.hand[thisPlayer][0] = copper;
    // print hand before call
    printf(" - ");
    for (int i = 0; i < testG.handCount[thisPlayer]; i++)
      printf("%d ", testG.hand[thisPlayer][i]);
    printf("\n");
    choice1 = 0; //trade the copper
    choice2 = 6; //look for gold
    printf(" - calling Mine...\n");
    cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
    // print hand after call
    printf(" - ");
    for (int i = 0; i < testG.handCount[thisPlayer]; i++)
      printf("%d ", testG.hand[thisPlayer][i]);
    printf("\n");
    if (testG.hand[thisPlayer][0] == copper)
      printf(" - Passed, copper can't be swapped to gold\n");
    else
      printf(" - Failed, lost copper\n");

    // ----------- TEST 7: copper -> silver --------------
    printf("TEST 7: retain constant number of cards under control\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.hand[thisPlayer][0] = copper;
    choice1 = 0; //trade the copper
    choice2 = 5; //look for silver
    int totalCardsB = testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer] + testG.playedCardCount + testG.handCount[thisPlayer];
    printf(" - calling Mine...\n");
    cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
    // print hand after call
    int totalCardsA = testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer] + testG.playedCardCount + testG.handCount[thisPlayer];
    if (totalCardsA == totalCardsB)
      printf(" - Passed, same number of cards\n");
    else
      printf(" - Failed, not the same number of cards\n");

    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
    

    return 0;
}


