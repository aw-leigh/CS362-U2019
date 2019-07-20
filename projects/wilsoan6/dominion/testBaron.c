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

int checkBaron(int choice1, struct gameState *post, int handPos, int currentPlayer)
{
    int r;
    r = baronUpdated(choice1, post, handPos, currentPlayer);
    
    assert(r == 0);
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
    PutSeed(-1);

    // for(int j = 0; j < 1000; j++){
    //     printf("%d ", (int)floor(Random() * 256));
    // }

    //fill gameState with completely random data
    for (n = 0; n < 2000; n++)
    {
        for (i = 0; i < sizeof(struct gameState); i++)
        {
            ((char *)&G)[i] = floor(Random() * 256);
        }

        currentPlayer = (int)floor(Random() * 4); //player 0-3

        //ensure the selected player is the one to take the turn
        G.whoseTurn = currentPlayer;

        //G.supplyCount[estate] = (int)floor(Random() * 10) % 2; //either 1 or 0 estates
        G.deckCount[currentPlayer] = floor(Random() * MAX_DECK);
        G.discardCount[currentPlayer] = floor(Random() * MAX_DECK);
        G.handCount[currentPlayer] = floor(Random() * MAX_HAND);
        G.playedCardCount = floor(Random() * MAX_HAND); //need to add this or segfault

        //put baron in player's hand and select it to be played
        handPos = floor(Random() * G.handCount[currentPlayer]);
        G.hand[currentPlayer][handPos] = baron;

        //estates are never in hand? let's hardcode one and see
        //G.hand[currentPlayer][handPos-1] = estate;

        //either try to discard or don't 
        choice1 = ((int)floor(Random() * 10) % 2); //either 1 or 0
        //printf("%d ", choice1);
        
        checkBaron(choice1, &G, handPos, currentPlayer);
    }

    printf("ALL TESTS OK\n");

    exit(0);
    
    /*
    printf("SIMPLE FIXED TESTS.\n");
    for (p = 0; p < 2; p++)
    {
        for (deckCount = 0; deckCount < 5; deckCount++)
        {
            for (discardCount = 0; discardCount < 5; discardCount++)
            {
                for (handCount = 0; handCount < 5; handCount++)
                {
                    memset(&G, 23, sizeof(struct gameState));
                    r = initializeGame(2, k, 1, &G);
                    G.deckCount[p] = deckCount;
                    memset(G.deck[p], 0, sizeof(int) * deckCount);
                    G.discardCount[p] = discardCount;
                    memset(G.discard[p], 0, sizeof(int) * discardCount);
                    G.handCount[p] = handCount;
                    memset(G.hand[p], 0, sizeof(int) * handCount);
                    checkDrawCard(p, &G);
                }
            }
        }
    }*/

    return 0;
}
