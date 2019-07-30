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

int checkTribute(struct gameState *afterTest, int handPos, int currentPlayer, int nextPlayer, int tributeRevealedCards[])
{
    int r;
    struct gameState beforeTest;
    memcpy (&beforeTest, afterTest, sizeof(struct gameState));

    r = tributeUpdated(afterTest, handPos, currentPlayer, nextPlayer, tributeRevealedCards);

    if((beforeTest.discardCount[nextPlayer] + beforeTest.deckCount[nextPlayer]) <= 1){
        if(beforeTest.discardCount[nextPlayer] > 0){
            tributeRevealedCards[0] = beforeTest.discard[nextPlayer][beforeTest.discardCount[nextPlayer] - 1];
        }else{
            tributeRevealedCards[0] = beforeTest.deck[nextPlayer][beforeTest.deckCount[nextPlayer] - 1];
            beforeTest.discard[nextPlayer][beforeTest.discardCount[nextPlayer]] = tributeRevealedCards[0];
            beforeTest.discardCount[nextPlayer]++;
            beforeTest.deckCount[nextPlayer]--;
        }
    }else{
        for (int i = 0; i < 2; i++){
            //ensure there are cards in hand
            shuffleDeckIfEmpty(&beforeTest, nextPlayer);

            //copy top card of deck to revealed cards
            tributeRevealedCards[i] = beforeTest.deck[nextPlayer][beforeTest.deckCount[nextPlayer] - 1];

            //move it to the discard pile
            beforeTest.discard[nextPlayer][beforeTest.discardCount[nextPlayer]] = beforeTest.deck[nextPlayer][beforeTest.deckCount[nextPlayer] - 1];
            beforeTest.discardCount[nextPlayer]++;

            //remove it from the deck
            beforeTest.deck[nextPlayer][beforeTest.deckCount[nextPlayer] - 1] = -1;
            beforeTest.deckCount[nextPlayer]--;
        }
    }
    if (tributeRevealedCards[0] == tributeRevealedCards[1]){
        tributeRevealedCards[1] = -1;
    }

    for (int i = 0; i < 2; i++)
    {  
        if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold)
        { //Treasure cards
            beforeTest.coins += 2;
        }
        else if(tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall)
        { //Victory Card Found
            drawCard(currentPlayer, &beforeTest);
            drawCard(currentPlayer, &beforeTest);
        }
        else if(tributeRevealedCards[i] == curse)
        { //Curses do nothing
        }
        else if(tributeRevealedCards[i] != -1)
        { //Action Card
            beforeTest.numActions += 2;
        }
    }

    discardCard(handPos, currentPlayer, &beforeTest, 0);

    //printf("%d:%d\n", tributeRevealedCards[0], tributeRevealedCards[1]);
    assert(r == 0);
    assert(beforeTest.playedCardCount == afterTest->playedCardCount);
    assert(beforeTest.numActions == afterTest->numActions);
    assert(beforeTest.coins == afterTest->coins);
    assert(beforeTest.handCount[currentPlayer] == afterTest->handCount[currentPlayer]);
    assert(beforeTest.deckCount[currentPlayer] == afterTest->deckCount[currentPlayer]);
    assert(beforeTest.discardCount[currentPlayer] == afterTest->discardCount[currentPlayer]);
    assert(beforeTest.handCount[nextPlayer] == afterTest->handCount[nextPlayer]);
    assert(beforeTest.deckCount[nextPlayer] == afterTest->deckCount[nextPlayer]);
    assert(beforeTest.discardCount[nextPlayer] == afterTest->discardCount[nextPlayer]);
    assert(beforeTest.hand[currentPlayer][beforeTest.handCount[currentPlayer]-1] == afterTest->hand[currentPlayer][afterTest->handCount[currentPlayer]-1]);
    assert(beforeTest.hand[currentPlayer][beforeTest.handCount[currentPlayer]-2] == afterTest->hand[currentPlayer][afterTest->handCount[currentPlayer]-2]);

    //assert(memcmp(&beforeTest, afterTest, sizeof(struct gameState)) == 0);
    if(memcmp(&beforeTest, afterTest, sizeof(struct gameState)) != 0){
        return 1;
    }

    return 0;
}

int main()
{

    int i, n, handPos, currentPlayer, nextPlayer, errors;
    int tributeRevealedCards[2] = {0};
    tributeRevealedCards[0] = 32767 - (int)floor(Random() * 65536);
    tributeRevealedCards[1] = 32767 - (int)floor(Random() * 65536);

    errors = 0;

    //int k[10] = {adventurer, council_room, feast, gardens, mine,
    //             remodel, smithy, village, baron, great_hall};

    struct gameState G;

    printf("Testing Tribute.\n");
    printf("RANDOM TESTS.\n");

    SelectStream(2);
    PutSeed(22);

    //fill gameState with completely random data
    for (n = 0; n < 20000; n++)
    {
        for (i = 0; i < sizeof(struct gameState); i++)
        {
            ((char*)&G)[i] = floor(Random() * 256);
        }

        currentPlayer = (int)floor(Random() * 4); //player 0-3
        nextPlayer = (currentPlayer + 1) % 4;

        //ensure the selected player is the one to take the turn
        G.whoseTurn = currentPlayer;

        //ensure decks are realistic sizes
        G.deckCount[currentPlayer] = floor(Random() * MAX_DECK);
        G.discardCount[currentPlayer] = floor(Random() * MAX_DECK);
        G.handCount[currentPlayer] = floor(Random() * MAX_HAND);
        G.playedCardCount = floor(Random() * MAX_HAND); //need to add this or segfault

        G.deckCount[nextPlayer] = floor(Random() * MAX_DECK);
        G.discardCount[nextPlayer] = floor(Random() * MAX_DECK);
        G.handCount[nextPlayer] = floor(Random() * MAX_HAND);

        //completely random card data ranges between -1.8B to 1.8B ish
        for(int i = 0; i < G.handCount[currentPlayer]; i++){ //set card to between -32768 to 32767
            G.hand[currentPlayer][i] = 32767 - (int)floor(Random() * 65536);
        }
        for(int i = 0; i < G.deckCount[nextPlayer]; i++){ //set card to between -32768 to 32767
            G.deck[nextPlayer][i] = 32767 - (int)floor(Random() * 65536);
        }
        for(int i = 0; i < G.discardCount[nextPlayer]; i++){ //set card to between -32768 to 32767
            G.discard[nextPlayer][i] = 32767 - (int)floor(Random() * 65536);
        }

        //put tribute in player's hand and select it to be played
        handPos = floor(Random() * G.handCount[currentPlayer]);
        G.hand[currentPlayer][handPos] = tribute;
        
        errors += checkTribute(&G, handPos, currentPlayer, nextPlayer, tributeRevealedCards);
        //printf("Finished test %d\n", n);
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
