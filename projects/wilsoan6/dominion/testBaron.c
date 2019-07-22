#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int checkBaron(int choice1, struct gameState *afterTest, int handPos, int currentPlayer)
{
    int r;
    int addEstate = 1; 
    struct gameState beforeTest;
    memcpy (&beforeTest, afterTest, sizeof(struct gameState));

    r = baronUpdated(choice1, afterTest, handPos, currentPlayer);

    discardCard(handPos, currentPlayer, &beforeTest, 0);
    beforeTest.numBuys++;

    if (choice1 > 0){
        for(int i = 0; i < beforeTest.handCount[currentPlayer]; i++){
            if(beforeTest.hand[currentPlayer][i] == estate){
                beforeTest.coins += 4; //Add 4 coins to the amount of coins
                beforeTest.discard[currentPlayer][beforeTest.discardCount[currentPlayer]] = beforeTest.hand[currentPlayer][i];
                beforeTest.discardCount[currentPlayer]++;
                for (int p = i; p < beforeTest.handCount[currentPlayer]; p++)
                {
                    beforeTest.hand[currentPlayer][p] = beforeTest.hand[currentPlayer][p + 1];
                }
                beforeTest.hand[currentPlayer][beforeTest.handCount[currentPlayer]] = -1;
                beforeTest.handCount[currentPlayer]--;
                addEstate = 0;
                break;
            }
        }
    }
    if(addEstate == 1){
        if(beforeTest.supplyCount[estate] > 0)
        {
            gainCard(estate, &beforeTest, 0, currentPlayer);
        }
    }
    
    assert(r == 0);
    assert(memcmp(&beforeTest, afterTest, sizeof(struct gameState)) == 0);

    return 0;
}

int main()
{

    int i, n, handPos, currentPlayer, choice1;

    //int k[10] = {adventurer, council_room, feast, gardens, mine,
    //             remodel, smithy, village, baron, great_hall};

    struct gameState G;

    printf("Testing baron.\n");
    printf("RANDOM TESTS.\n");

    SelectStream(2);
    PutSeed(27);

    //fill gameState with completely random data
    for (n = 0; n < 200000; n++)
    {
        for (i = 0; i < sizeof(struct gameState); i++)
        {
            ((char*)&G)[i] = floor(Random() * 256);
        }

        currentPlayer = (int)floor(Random() * 4); //player 0-3

        //ensure the selected player is the one to take the turn
        G.whoseTurn = currentPlayer;

        //ensure decks are realistic sizes
        G.deckCount[currentPlayer] = floor(Random() * MAX_DECK);
        G.discardCount[currentPlayer] = floor(Random() * MAX_DECK);
        G.handCount[currentPlayer] = floor(Random() * MAX_HAND);
        G.playedCardCount = floor(Random() * MAX_HAND); //need to add this or segfault

        //completely random card data ranges between -1.8B to 1.8B ish
        //need to modify hand values to get a realistic chance of holding an estate / having estates run out
        
        G.supplyCount[estate] = 32767 - (int)floor(Random() * 65536); //set estate supply between -32768 to 32767 (2-byte signed int range)
        if(i % 500 == 0){
            G.supplyCount[estate] = 0; //set it to 0 every 500 iterations
        }


        for(int i = 0; i < G.handCount[currentPlayer]; i++){ //set card to between -32768 to 32767
            G.hand[currentPlayer][i] = 32767 - (int)floor(Random() * 65536);
        }

        //put baron in player's hand and select it to be played
        handPos = floor(Random() * G.handCount[currentPlayer]);
        G.hand[currentPlayer][handPos] = baron;

        //either try to discard or don't 
        choice1 = 32767 - (int)floor(Random() * 65536); //choice1 to between -32768 to 32767
        
        checkBaron(choice1, &G, handPos, currentPlayer);
    }

    printf("ALL TESTS OK\n");

    // for (i = 0; i < sizeof(struct gameState); i++)
    // {
    //     printf("%d ",((char *)&G)[i]);
    // }
    // for(int i = 0; i < G.handCount[currentPlayer]; i++){ //set card to between 0-255
    //     printf("%d ",G.hand[currentPlayer][i]);
    // }    
   
    return 0;
}
