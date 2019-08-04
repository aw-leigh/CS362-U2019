/*
 * unittest2.c -- Minion
 *
 
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "minion"

int main() {

  srand(time(NULL));
  
  int newCards = 0;
  int discarded = 1;
  int xtraCoins = 0;
  int shuffleCards = 0;

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

  int z;
  for (z = 0; z < 1000; z++)
    {
  
      // ----------- TEST 1: +1 Aciton --------------
      printf("TEST 1: extra action\n");
      // copy the game state to a test case
      memcpy(&testG, &G, sizeof(struct gameState));
      cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);
      // test for an addtional action
      if (testG.numActions == G.numActions + 1)
	printf(" - Passed, player granted additional action\n");
      else
	printf(" - Failed, player not granted additional action\n");
  
  
      // ----------- TEST 2: +2 coins --------------
      printf("TEST 2: +2 coins\n");
      // copy the game state to a test case
      memcpy(&testG, &G, sizeof(struct gameState));

      int p1choice = rand() % 2;
      if (p1choice == 1)
	choice2 = 0;
      else
	choice2 = 1;
  
      cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);
      // test for additional coins
      if (testG.coins == G.coins + 2)
	printf(" - Passed, player gained 2 coins\n");
      else
	printf(" - Failed, player did not gain 2 coins\n");
  
  
      // ----------- TEST 3: player discard and draw --------------
      printf("TEST 3: player discards hand and draws 4\n");
      // copy the game state to a test case
      memcpy(&testG, &G, sizeof(struct gameState));
      int opponent = thisPlayer + 1;
      p1choice = rand() % 2;
      choice1 = p1choice;
      if (p1choice == 1)
	choice2 = 0;
      else
	choice2 = 1;
      int p2HC = rand() % 10;
      int y;
      for (y = 0; y < p2HC; y++)
	drawCard(opponent, &testG);

      cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);
      // test hand count
      if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] - 1)
	printf(" - Passed, player has one less card\n");
      else
	printf(" - Failed, player does not have one less card\n");
      // ----------- TEST 4: player drew from their deck --------------
      printf("TEST 3: player drew 4 from deck\n");
      // test deck count
      if (testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 4)
	printf(" - Passed, player's deck is 4 less\n");
      else
	printf(" - Failed, player's deck is not 4 less\n");

      // ----------- TEST 5: opponent with 5 in hand discards and draws --------------
      printf("TEST 5: opponent discards hand and draws 4\n");
      // test deck count
      if (testG.handCount[opponent] == G.handCount[opponent] - 1)
	printf(" - Passed, opponent has one less card\n");
      else
	printf(" - Failed, opponent does not have one less card\n");
      // ----------- TEST 6: player drew from their deck --------------
      printf("TEST 6: opponent draws 4 from deck\n");
      // test deck count
      if (testG.deckCount[opponent] == G.deckCount[opponent] - 4)
	printf(" - Passed, opponent's deck is 4 less\n");
      else
	printf(" - Failed, opponent's deck is not 4 less\n");
  
    }
  /*
    printf("Opponent handCount: %d\n", testG.handCount[opponent]);
    printf("Opponent deckCount: %d\n", testG.deckCount[opponent]);
    printf("Player handCount: %d\n", testG.handCount[currentPlayer]);
    printf("Player deckCount: %d\n", testG.deckCount[currentPlayer]);
    ce_Minion(choice1, choice2, &testG, handpos);
    printf("Opponent handCount: %d\n", testG.handCount[opponent]);
    printf("Opponent deckCount: %d\n", testG.deckCount[opponent]);
    printf("Player handCount: %d\n", testG.handCount[currentPlayer]);
    printf("Player deckCount: %d\n", testG.deckCount[currentPlayer]);
    */    

  printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

  
  return 0;
}
