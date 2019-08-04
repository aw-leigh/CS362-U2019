/*
 * unittest3 -- Ambassador
 *
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
  int newCards = 0;
  int discarded = 1;
  int xtraCoins = 0;
  int shuffledCards = 0;
  
  int i, j, m;
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0;
  int *bonus = 0;
  int remove1, remove2;
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
  struct gameState G, testG;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy, ambassador};

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);
  //int currentPlayer = whoseTurn(&G);
  
  printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    
  // establish a dummy hand
  G.hand[thisPlayer][0] = ambassador;
  G.hand[thisPlayer][1] = copper;
  G.hand[thisPlayer][2] = estate;
  G.hand[thisPlayer][3] = estate;
  G.hand[thisPlayer][4] = village;
  
  // ----------- TEST 1 - 2: player reveals card, selects 0-1 copies --------------
  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  printf(" - Player's hand has:  ");
  for (int k = 0; k < 5; k++)
    printf("%d ", testG.hand[thisPlayer][k]);
  printf("\n");
  //loop through choosing 0, 1, or 2 copies
  for (int j = 0; j < 2; j++)
    {
      printf("TEST %d: player reveals a card, selects %d copies\n", j+1, j);
      // loop throught the other 4 cards
      for (int i = 1; i < 5; i++)
	{
	  memcpy(&testG, &G, sizeof(struct gameState));
	  choice1 = i;
	  choice2 = j;
	  int goodRun = cardEffect(ambassador, choice1, choice2, choice3, &testG, handpos, bonus);
	  printf(" - Returns %d with card %d\n", goodRun, choice1);
	  if (goodRun == 0)
	    printf(" - Passed %d copy/copies\n", j);
	  else
	    printf(" - Failed %d copy/copies, returned %d \n", j, goodRun);
	  
	  printf(" - player handCount is %d\n", testG.handCount[thisPlayer]);
	}
    }
  
  // ----------- TEST 3, ask for 2 valid copies --------------
  printf("TEST 3: player reveals a card, selects 2copies\n");
  memcpy(&testG, &G, sizeof(struct gameState));
  choice1 = 2;
  choice2 = 2;
  int goodRun = cardEffect(ambassador, choice1, choice2, choice3, &testG, handpos, bonus);
  if (goodRun == 0)
    printf(" - Passed 2 copies\n");
  else
    printf(" - Failed 2 copies, Ambassador returned %d \n", goodRun);
  
  // ----------- TEST 4, ask for invalid numer of copies --------------
  printf("TEST 4: player reveals a card, doesn't have enough copies\n");
  memcpy(&testG, &G, sizeof(struct gameState));
  choice1 = 4;
  choice2 = 2;
  goodRun = cardEffect(ambassador, choice1, choice2, choice3, &testG, handpos, bonus);
  if (goodRun == -1)
    printf(" - Passed, returned error");
  else
    printf(" - Failed, returned 0");
  printf("\n");
  
  // ----------- TEST 5, send card to Supply --------------
  printf("TEST 5: Send card to Supply\n");
  memcpy(&testG, &G, sizeof(struct gameState));
  choice1 = 1;
  choice2 = 1;
  int supCount = testG.supplyCount[testG.hand[thisPlayer][choice1]];
  printf(" - Before call supply is %d\n", supCount);
  goodRun = cardEffect(ambassador, choice1, choice2, choice3, &testG, handpos, bonus);
  supCount = testG.supplyCount[testG.hand[thisPlayer][choice1]];
  printf(" - After call supply is %d\n", supCount);
  
  
  // ----------- TEST 6, opponent receives a copy --------------
  printf("TEST 6: opponent receieves copy of card\n");
  memcpy(&testG, &G, sizeof(struct gameState));
  choice1 = 1;
  choice2 = 1;
  int opponent = thisPlayer + 1;
  // give the opponent a dummy hand
  testG.hand[opponent][0] = ambassador;
  testG.hand[opponent][1] = copper;
  testG.hand[opponent][2] = estate;
  testG.hand[opponent][3] = estate;
  testG.hand[opponent][4] = village;
  // confirm hand
  printf(" - Before Ambassador, opponent's hand has: ");
  for (int i = 0; i < 5; i++)
    printf("%d ", testG.hand[opponent][i]);
  printf("\n");
  cardEffect(ambassador, choice1, choice2, choice3, &testG, handpos, bonus);
  printf(" - After Ambassador, opponent's hand has: ");
  for (int i = 0; i < 5; i++)
    printf("%d ", testG.hand[opponent][i]);
  printf("\n");
  

    
  printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


