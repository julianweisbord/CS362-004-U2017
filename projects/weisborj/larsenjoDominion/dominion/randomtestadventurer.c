/*
 * randomtestadventurer.c
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[])
{

/*
int advent(int drawntreasure, struct gameState *state, int currentPlayer, 
    int temphand[], int cardDrawn, int z)
{        
    while(drawntreasure<2)
    {
	    if (state->deckCount[currentPlayer] <1)
        {//if the deck is empty we need to shuffle discard and add to deck
	        shuffle(currentPlayer, state);
	    }
	    drawCard(currentPlayer, state);
	    cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
	    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
	    drawntreasure++;
	    else
        {
	        temphand[z]=cardDrawn;
	        state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
	        z++;
	    }
    }
      
    while(z-1>=0)
    {
	    state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
	    z=z-1;
    }
    
    int x = 1;
    int y = 0;

    return x/y;
}
*/
  
    srand(time(NULL) + 3);
    
    struct gameState* g = malloc(sizeof(struct gameState));
    struct gameState* test = malloc(sizeof(struct gameState));

    fprintf(stderr, "********Testing advent()********\n");

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

//int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed,
//		   struct gameState *state);
    int numPlayers;
    do
    {
       numPlayers = rand() % 100;
    } while (numPlayers < 2);
    int randomSeed = rand() % 9999 + 1;    
    
    fprintf(stderr, "numPlayers: %d, randomSeed: %d\n", numPlayers, randomSeed);

    initializeGame(numPlayers, k, randomSeed, g);
    memcpy(test, g, sizeof(struct gameState));

    int currentPlayer;
    do
    {
        currentPlayer = rand() % 100;
    } while (currentPlayer > numPlayers);

    int temphand[MAX_HAND];
    int cardDrawn = rand() % 50;
    int drawnTreasure = rand() % 8;
    fprintf(stderr, "cardDrawn: %d, drawnTreasure: %d\n", cardDrawn, drawnTreasure);
//int advent(int drawntreasure, struct gameState *state, int currentPlayer, 
//    int temphand[], int cardDrawn, int z)
    if( advent(drawnTreasure, g, currentPlayer, temphand, cardDrawn, 0) != 0)
        fprintf(stderr,"Bad return value\n");
    else
        fprintf(stderr,"Good return value\n");

    //test the hand count
    if(g->handCount[currentPlayer] == test->handCount[currentPlayer]+1)
        fprintf(stderr,"Test 1 passed\n");
    else
        fprintf(stderr,"Test 1 failed\n");

    //test that deck count was decremented by at least 2
    if(g->deckCount[currentPlayer] < test->deckCount[currentPlayer]-1)
        fprintf(stderr,"Test 2 passed\n");
    else
        fprintf(stderr,"Test 2 failed\n");

    int secondPlayer;
    do
    {
        secondPlayer = rand() % 100;
    } while (secondPlayer == currentPlayer || secondPlayer > numPlayers);

    //test that othe player not changed
    if(g->handCount[secondPlayer] == test->handCount[secondPlayer])
        fprintf(stderr,"Test 3 passed\n");
    else
        fprintf(stderr,"Test 3 failed\n");

    //trash flag set properly
    if(g->playedCardCount > test->playedCardCount)
        fprintf(stderr,"Test 4 passed\n");
    else
        fprintf(stderr,"Trash flag error\n");

/*Card drawn may have been coins
    //test coin count decremented by 6
    if(g->coins < test->coins - 6)
        fprintf(stderr,"Test 4 passed\n");
    else
        fprintf(stderr,"Test 4 failed\n");
*/

    fprintf(stderr, "********advent() tests complete********\n\n");
}//end main

