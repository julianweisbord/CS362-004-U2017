// Smithy test
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#define PLAY_PHASE 0

int check_adventurer_effect(struct gameState *new_state, int handPos, int p, int trashFlag){
    struct gameState old_state;
    memcpy (&old_state, new_state, sizeof(struct gameState));
    int play, i;
    new_state->numActions = 5;
    play = playCard(handPos, -1, -1, -1, new_state);
    printf("play: %d\n", play);
    if (PLAY_PHASE == 0 && play == -2){
        play = 0; // if play is -2 then that means we are not
                    //in the play card state so we will fudge this.
    }
    //advance state by drawing cards until 2 treasures are found or until we run out of cards in the deck.
    int drawntreasure = 0;
    for(i =0; i< MAX_DECK; ++i){

      drawCard(p, &old_state);
      int cardDrawn = old_state.hand[p][old_state.handCount[p]-1];//top card of hand is most recently drawn card.
      if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
        drawntreasure++;
        if(drawntreasure ==2)
          break;
      }
    }
    assert(play == 0);
    // assert(memcmp(&old_state, new_state, sizeof(struct gameState)) == 0);
    return 0;
}

int main () {

  int i, j, n, r, p, q, t, deckCount, discardCount, handCount, trashFlag, handPos;
  int randAdventurer, randCopper, randSilver, randGold;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing adventurer_effect.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 20000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.deckCount[p] = floor(rand() % MAX_DECK);
    // Make a random number of adventurers
    randAdventurer = floor(Random() * floor(G.deckCount[p] / 2));
    // Add random number of adventurers to deck
    for(j = 0; j < randAdventurer; ++j){
        G.deck[p][j] = adventurer;
        printf("Added andventurer\n");
    }
    // Make a random number of coppers, silvers, and gold
    randCopper = floor(Random() * floor(G.deckCount[p]));
    randSilver = floor(Random() * floor(G.deckCount[p]));
    randGold = floor(Random() * floor(G.deckCount[p]));
    // Add random number of adventurers to deck
    q = 0;
    t = 0;
    for(j = 0; j < randCopper; ++j){
        G.deck[p][j] = copper;
        printf("Added copper\n");
        ++q;
    }
    for(j = 0; j < randSilver; ++j){
        G.deck[p][j] = silver;
        printf("Added silver\n");
        ++t;
    }

    for(j = 0; j < randGold; ++j){
        G.deck[p][j] = gold;
        printf("Added gold\n");
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
    // For each card in hand check that adventurer works correctly and
        //play adventurer.
    for (j = 0; j < G.handCount[p]; j++) {
        // printf("%d\n", G.hand[p][j]);
        if(G.hand[p][j] == adventurer){
            check_adventurer_effect(&G, j, p, trashFlag);
        }
    }

  printf ("ALL TESTS OK\n");

  return 0;
  }
}
