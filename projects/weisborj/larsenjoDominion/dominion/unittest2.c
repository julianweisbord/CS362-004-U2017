// Updates and improvements to draw card
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int checkDrawCard(int p, struct gameState *new_state) {
  struct gameState old_state;
  memcpy (&old_state, new_state, sizeof(struct gameState));

  int r;
  //  printf ("drawCard PRE: p %d HC %d DeC %d DiC %d\n",
  //	  p, old_state.handCount[p], old_state.deckCount[p], old_state.discardCount[p]);

  r = drawCard (p, new_state);

    assert(new_state->discardCount[p] >= 0 && "Discard count less than zero!");
    assert(new_state->deckCount[p] >= 0 && "Deck Count less than zero!");

    if (old_state.deckCount[p] > 0 && old_state.discardCount[p] >= 0) {
      old_state.handCount[p]++;
      old_state.hand[p][old_state.handCount[p]-1] = old_state.deck[p][old_state.deckCount[p]-1];
      old_state.deckCount[p]--;
    }
    else if (old_state.discardCount[p] > 0) {
      memcpy(old_state.deck[p], new_state->deck[p], sizeof(int) * old_state.discardCount[p]);
      memcpy(old_state.discard[p], new_state->discard[p], sizeof(int)*old_state.discardCount[p]);
      old_state.hand[p][new_state->handCount[p]-1] = new_state->hand[p][new_state->handCount[p]-1];
      old_state.handCount[p]++;
      old_state.deckCount[p] = old_state.discardCount[p]-1;
      old_state.discardCount[p] = 0;
    }
    else if (old_state.discardCount[p] == 0 && old_state.deckCount[p] == 0){
      //Do nothing
    }
    assert(new_state->discardCount[p] >= 0 && "Discard count less than zero!");
    assert(new_state->deckCount[p] >= 0 && "Deck Count less than zero!");
    assert (r == 0);

    assert(memcmp(&old_state, new_state, sizeof(struct gameState)) == 0);
}

int main () {

  int i, n, r, p, deckCount, discardCount, handCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing drawCard.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);
  // Here we generate a lot of test cases by using brute force
  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    checkDrawCard(p, &G);
  }

  printf ("ALL TESTS OK\n");

  return 0;
}
