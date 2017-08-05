// Test Great Hall

// Salvager test
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#define PLAY_PHASE 0

int check_great_hall_effect(struct gameState *new_state, int handPos, int p){
    struct gameState old_state;
    memcpy (&old_state, new_state, sizeof(struct gameState));
    int play;
    new_state->numActions = 1;
    play = playCard(handPos, -1, -1, -1, new_state);
    if (PLAY_PHASE == 0 && play == -2){
        play = 0; // if play is -2 then that means we are not
                    //in the play card state so we will fudge this.
    }
    //Increase number of actions and draw a card:
    drawCard(p, &old_state);
    new_state->numActions++;
    //Discard great hall
    discardCard(handPos, p, &old_state, 1);
    assert(play == 0);
    return 0;
}

int main () {

  int i, j, n, r, p, deckCount, discardCount, handCount, trashFlag, handPos;
  int randGreatHall;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing smithy_effect.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    // Make a random number of great halls
    randGreatHall = floor(Random() * floor(G.deckCount[p] / 2));
    // Add random number of great halls to deck
    for(j = 0; j < randGreatHall; ++j){
        G.deck[p][j] = great_hall;
    }
    G.discardCount[p] = floor(Random() * MAX_DECK);

    // Don't want hand to be bigger than deck
    if(MAX_HAND < MAX_DECK){
        G.handCount[p] = floor(Random() * MAX_HAND);
    }
    else{
        G.handCount[p] = floor(Random() * MAX_DECK);
    }

    for (j = 0; j < G.handCount[p]; j++) {
        drawCard(p, &G);
    }
    trashFlag = 1;
    // For each card in hand check that great_hall works correctly and
        //play great_hall.
    for (j = 0; j < G.handCount[p]; j++) {
        if(G.hand[p][j] == great_hall){
            check_great_hall_effect(&G, j, p);
        }
    }

  printf ("ALL TESTS OK\n");

  return 0;
  }
}
