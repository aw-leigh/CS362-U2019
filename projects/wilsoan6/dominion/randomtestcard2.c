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

int checkMinion(int choice1, struct gameState *afterTest, int handPos, int currentPlayer)
{
    int r;
    struct gameState beforeTest;
    memcpy (&beforeTest, afterTest, sizeof(struct gameState));

    r = minionUpdated(choice1, afterTest, handPos, currentPlayer);

    beforeTest.numActions++;
    discardCard(handPos, currentPlayer, &beforeTest, 0);
    if(choice1 == 1){
        beforeTest.coins += 2;
    }
    else{
       
        while(numHandCards(&beforeTest) > 0)
        {
            discardCard(0, currentPlayer, &beforeTest, 1); //AW 7-1-2019: always discard first card (handPos->0)
        }

        //draw 4
        for (int i = 0; i < 4; i++)
        {
            drawCard(currentPlayer, &beforeTest);
        }

        //other players discard hand and redraw if hand size > 4
        for (int i = 0; i < beforeTest.numPlayers; i++)
        {
            if(i != currentPlayer)
            {
                if (beforeTest.handCount[i] > 4)
                {
                    //discard hand
                    while (beforeTest.handCount[i] > 0)
                    {
                        discardCard(0, i, &beforeTest, 1); //AW 7-1-2019: always discard first card handPos->0
                    }

                    //draw 4
                    for (int j = 0; j < 4; j++)
                    {
                        drawCard(i, &beforeTest);
                    }
                }
            }
        }
    }

    assert(r == 0);
    assert(beforeTest.playedCardCount == afterTest->playedCardCount);
    assert(beforeTest.numActions == afterTest->numActions);
    assert(beforeTest.coins == afterTest->coins);
    assert(beforeTest.handCount[currentPlayer] == afterTest->handCount[currentPlayer]);
    assert(beforeTest.deckCount[currentPlayer] == afterTest->deckCount[currentPlayer]);
    assert(beforeTest.discardCount[currentPlayer] == afterTest->discardCount[currentPlayer]);

    if(memcmp(&beforeTest, afterTest, sizeof(struct gameState)) != 0){
        return 1;
    }

    return 0;
}

int main()
{

    int i, n, handPos, currentPlayer, choice1;
    int errors = 0;

    //int k[10] = {adventurer, council_room, feast, gardens, mine,
    //             remodel, smithy, village, baron, great_hall};

    struct gameState G;

    printf("Testing minion.\n");
    printf("RANDOM TESTS.\n");

    SelectStream(2);
    PutSeed(27);

    //fill gameState with completely random data
    for (n = 0; n < 20000; n++)
    {
        for (i = 0; i < sizeof(struct gameState); i++)
        {
            ((char*)&G)[i] = floor(Random() * 256);
        }

        G.numPlayers = (int)floor(Random() * 3) + 2; //2-4 players
        currentPlayer = (int)floor(Random() * G.numPlayers); //valid current player

        //ensure the selected player is the one to take the turn
        G.whoseTurn = currentPlayer;

        //ensure decks are realistic sizes for each player
        for(int i = 0; i < G.numPlayers; i++){
            G.deckCount[i] = floor(Random() * (MAX_DECK/2));
            G.discardCount[i] = floor(Random() * (MAX_DECK/2));
            G.handCount[i] = floor(Random() * (MAX_HAND/2));
        }
        G.playedCardCount = floor(Random() * MAX_HAND); //need to add this or segfault

        //completely random card data ranges between -1.8B to 1.8B ish
        //need to modify hand values to get a realistic chance of holding an estate / having estates run out

        for(int i = 0; i < G.handCount[currentPlayer]; i++){ //set card to between -32768 to 32767
            G.hand[currentPlayer][i] = 32767 - (int)floor(Random() * 65536);
        }

        //put minion in player's hand and select it to be played
        handPos = floor(Random() * G.handCount[currentPlayer]);
        G.hand[currentPlayer][handPos] = minion;

        //either try to discard or don't 
        choice1 = (int)floor(Random() * 2) + 1; //choice1 must be either 1 or 2
        
        errors += checkMinion(choice1, &G, handPos, currentPlayer);
    }
    if(errors == 0){
        printf("ALL TESTS OK\n");
    }else{
        printf("Number of nonmatching states: %d\n", errors);
    }

    // for (i = 0; i < sizeof(struct gameState); i++)
    // {
    //     printf("%d ",((char *)&G)[i]);
    // }
    // for(int i = 0; i < G.handCount[currentPlayer]; i++){ //set card to between 0-255
    //     printf("%d ",G.hand[currentPlayer][i]);
    // }    
   
    return 0;
}
