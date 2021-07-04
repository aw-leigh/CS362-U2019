/*
 * randomtesting -- Baron
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

#define TESTCARD "baron"

int main() {

  srand(time(NULL));

  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0;
  int *bonus = 0;
  int seed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
  struct gameState G, testG;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy, council_room};
  
  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);
  
  printf("----------------- Testing Card: %s ----------------\n", TESTCARD);


  // run 50 trials with randomness
  int i;
  for (i = 0; i < 50; i++)
    {
  
      // copy game state to a test case
      memcpy(&testG, &G, sizeof(struct gameState));

      // change the number of estates in the supply, 0 - 10
      int numEstatesSupply = rand() % 11;
      testG.supplyCount[estate] = numEstatesSupply;

      // change the number of estates in player's hand, 0 - 1 
      int numEstatesHand = rand() % 2;
      if (numEstatesHand == 0)
	{
	  testG.hand[thisPlayer][0] = copper;
	  testG.hand[thisPlayer][1] = copper;
	  testG.hand[thisPlayer][2] = copper;
	  testG.hand[thisPlayer][3] = copper;
	  testG.hand[thisPlayer][4] = copper;
	}      
      else
	{
	  testG.hand[thisPlayer][0] = estate;
	  testG.hand[thisPlayer][1] = copper;
	  testG.hand[thisPlayer][2] = copper;
	  testG.hand[thisPlayer][3] = copper;
	  testG.hand[thisPlayer][4] = copper;
	}      

      // change the player's choice, 0 - 1
      choice1 = rand() % 2;

      

      cardEffect(baron, choice1, choice2, choice3, &testG, handpos, bonus);


      printf("Testing incrementation of numBuys...\n");
      if(testG.numBuys == G.numBuys + 1)
	printf(" - Passed, player is granted 1 additional Buy\n");
      else
	printf(" - Failed, player is not granted additional Buy\n");
  
  
      // check discard option w/ estate
      printf("Testing +4 coins from discard option...\n");
      // copy game state to a test case
      memcpy(&testG, &G, sizeof(struct gameState));

      // change the number of estates in the supply, 0 - 10
      numEstatesSupply = rand() % 11;
      testG.supplyCount[estate] = numEstatesSupply;

      // change the number of estates in player's hand, 0 - 1 
      numEstatesHand = rand() % 2;
      if (numEstatesHand == 0)
	{
	  testG.hand[thisPlayer][0] = copper;
	  testG.hand[thisPlayer][1] = copper;
	  testG.hand[thisPlayer][2] = copper;
	  testG.hand[thisPlayer][3] = copper;
	  testG.hand[thisPlayer][4] = copper;
	}      
      else
	{
	  testG.hand[thisPlayer][0] = estate;
	  testG.hand[thisPlayer][1] = copper;
	  testG.hand[thisPlayer][2] = copper;
	  testG.hand[thisPlayer][3] = copper;
	  testG.hand[thisPlayer][4] = copper;
	}      

      // change the player's choice, 0 - 1
      choice1 = rand() % 2;



      // make sure player has an estate
      //    gainCard(estate, &testG, 0, currentPlayer);//Gain an estate
      cardEffect(baron, choice1, choice2, choice3, &testG, handpos, bonus);
      //    printf("After Baron: ");
      /*
	for (int i = 0; i < testG.handCount[currentPlayer]; i++)
	printf("%d ", testG.hand[currentPlayer][i]);
	printf("\n");
      */
  
      //    printf("The coins in G is %d\n", G.coins);
      //    printf("The coins in testG is %d\n", testG.coins);
      // check that the player has gained 4 coins
      if(testG.coins == G.coins + 4)
	printf(" - Passed, player has gained 4 coins\n");
      else
	printf(" - Failed, player did not gain 4 coins\n");
  
  
  
      // check discard option w/o estate
      printf("Testing gain estate option...\n");
      // copy game state to a test case
      memcpy(&testG, &G, sizeof(struct gameState));

      // change the number of estates in the supply, 0 - 10
      numEstatesSupply = rand() % 11;
      testG.supplyCount[estate] = numEstatesSupply;

      // change the number of estates in player's hand, 0 - 1 
      numEstatesHand = rand() % 2;
      if (numEstatesHand == 0)
	{
	  testG.hand[thisPlayer][0] = copper;
	  testG.hand[thisPlayer][1] = copper;
	  testG.hand[thisPlayer][2] = copper;
	  testG.hand[thisPlayer][3] = copper;
	  testG.hand[thisPlayer][4] = copper;
	}      
      else
	{
	  testG.hand[thisPlayer][0] = estate;
	  testG.hand[thisPlayer][1] = copper;
	  testG.hand[thisPlayer][2] = copper;
	  testG.hand[thisPlayer][3] = copper;
	  testG.hand[thisPlayer][4] = copper;
	}      

      // change the player's choice, 0 - 1
      choice1 = rand() % 2;

      /*
      // TESTING print out player's hand before discard
      printf("Before Baron player has: ");
      for (int i = 0; i < testG.handCount[currentPlayer]; i++)
      printf("%d ", testG.hand[currentPlayer][i]);
      printf("\n");
      // discard all cards in hand to make sure there is no estate
      printf(" - with a handCount of %d\n", testG.handCount[currentPlayer]);
      */
      printf(" - and there are %d estate card(s) in the supply\n", testG.supplyCount[estate]);
      printf(" - Run Baron()...\n");
      cardEffect(baron, choice1, choice2, choice3, &testG, handpos, bonus);
      /*
	printf("The coins in G is %d\n", G.coins);
	printf("The coins in testG is %d\n", testG.coins);
	//gainCard(estate, &testG, 0, currentPlayer);
	// TESTING print out player's hand after call
	printf("After Baron player has: "); 
	for (int i = 0; i < testG.handCount[currentPlayer]; i++)
	printf("%d ", testG.hand[currentPlayer][i]);
	printf("\n");
      */
      printf(" - and there are %d estate card(s) in the supply\n", testG.supplyCount[estate]);
      // check that the player has gained an estate
      if(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 1 && testG.supplyCount[estate] == G.supplyCount[estate] - 1)
	printf(" - Passed, player has gained an estate from supply\n");
      else
	printf(" - Failed, player did not gain an estate from supply\n");
  
      printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
    }
  
  return 0;
}
