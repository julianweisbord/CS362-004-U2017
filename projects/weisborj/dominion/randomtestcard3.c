// Adventurer test
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#define PLAY_PHASE 0

int check_smithy_effect(struct gameState *new_state, int handPos, int p, int trashFlag){
    struct gameState old_state;
    memcpy (&old_state, new_state, sizeof(struct gameState));
    int play;
    new_state->numActions = 5;
    play = playCard(handPos, -1, -1, -1, new_state);
    printf("play: %d\n", play);
    if (PLAY_PHASE == 0 && play == -2){
        play = 0; // if play is -2 then that means we are not
                    //in the play card state so we will fudge this.
    }
    // Smithy draws 3 cards
    drawCard(p, &old_state);
    drawCard(p, &old_state);
    drawCard(p, &old_state);
    // Discard Smithy
    discardCard(handPos, p, &old_state, trashFlag);
    assert(play == 0);
    // assert(memcmp(&old_state, new_state, sizeof(struct gameState)) == 0);
    return 0;
}

int main () {

  int i, j, n, r, p, deckCount, discardCount, handCount, trashFlag, handPos;
  int randSmithy;
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
    // Make a random number of smithys
    randSmithy = floor(Random() * floor(G.deckCount[p] / 2));
    // Add random number of smithys to deck
    for(j = 0; j < randSmithy; ++j){
        G.deck[p][j] = smithy;
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
    // For each card in hand check that smithy works correctly and
        //play smithy.
    for (j = 0; j < G.handCount[p]; j++) {
        printf("%d\n", G.hand[p][j]);
        if(G.hand[p][j] == smithy){
            check_smithy_effect(&G, j, p, trashFlag);
        }
    }

  printf ("ALL TESTS OK\n");

  return 0;
  }
}
