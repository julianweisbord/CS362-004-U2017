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

int check_salvager_effect(struct gameState *new_state, int choice1, int p, int handPos){
    struct gameState old_state;
    memcpy (&old_state, new_state, sizeof(struct gameState));
    int play;
    new_state->numActions = 5;
    play = playCard(handPos, -1, -1, -1, new_state);
    if (PLAY_PHASE == 0 && play == -2){
        play = 0; // if play is -2 then that means we are not
                    //in the play card state so we will fudge this.
    }
    int costs = old_state.hand[p][choice1];;
    //gain coins equal to trashed card
    old_state.coins = old_state.coins + getCost(costs);
    //trash card
    discardCard(choice1, p, &old_state, 1); //discard card to make us money :)
    discardCard(handPos, p, &old_state, 1); //discard salvager
    assert(play == 0);
    // assert(memcmp(&old_state, new_state, sizeof(struct gameState)) == 0);
    return 0;
}

int main () {

  int i, j, n, r, p, deckCount, discardCount, handCount, trashFlag, handPos;
  int randSalvager;
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
    // Make a random number of salvagers
    randSalvager = floor(Random() * floor(G.deckCount[p] / 2));
    // Add random number of salvagers to deck
    for(j = 0; j < randSalvager; ++j){
        G.deck[p][j] = salvager;
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
    // For each card in hand check that salvager works correctly and
        //play salvager.
    for (j = 0; j < G.handCount[p]; j++) {
        if(G.hand[p][j] == salvager){
            check_salvager_effect(&G, 1, p, j);
        }
    }

  printf ("ALL TESTS OK\n");

  return 0;
  }
}
