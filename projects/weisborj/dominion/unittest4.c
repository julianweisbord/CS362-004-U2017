// test discard card
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

int checkDiscardCard(int handPos, int p, struct gameState *new_state, int trashFlag) {
    struct gameState old_state;
    memcpy (&old_state, new_state, sizeof(struct gameState));
    int discard_status;

    discard_status = discardCard(handPos, p, new_state, trashFlag);
    old_state.hand[p][handPos] = -1;
    if (old_state.handCount[p] == 1 || handPos == (old_state.handCount[p] - 1)){
        //only one card in hand
        old_state.handCount[p]--;
    }
    else{
        old_state.hand[p][handPos] = old_state.hand[p][(old_state.handCount[p] - 1)];
        old_state.hand[p][old_state.handCount[p] - 1] = -1;
        old_state.handCount[p]--;
    }
    assert(discard_status == 0);
    assert(memcmp(&old_state, new_state, sizeof(struct gameState)) == 0);
    return 0;
}

int main() {

    int i, n, r, p, deckCount, discardCount, handCount, handPos, trashFlag;
    trashFlag = 1;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
    	       remodel, smithy, village, baron, great_hall};

    struct gameState G;

    printf ("Testing discardCard.\n");

    printf ("RANDOM TESTS.\n");

    SelectStream(2);
    PutSeed(3);

    for (n = 0; n < 2000; n++) {
      for (i = 0; i < sizeof(struct gameState); i++) {
        ((char*)&G)[i] = floor(Random() * 256);
      }
      p = floor(Random() * 2);
      G.deckCount[p] = floor(Random() * MAX_DECK);
      G.discardCount[p] = floor(Random() * MAX_DECK);
      G.handCount[p] = floor(Random() * MAX_HAND);
      handPos = floor(Random() * G.handCount[p]);
      checkDiscardCard(handPos, p, &G, trashFlag);
    }

    printf ("ALL TESTS OK\n");

    return 0;
}
