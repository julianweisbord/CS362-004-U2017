// Quick adventurer test
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

int main (int argc, char** argv) {
  struct gameState *G = newGame();

  int players = 2;
  int seed = 4;

  int kingdom[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy};

  //Test game initialized correctly
  int status = initializeGame(players, kingdom, seed, G);
  assert(status == 0 && "Initialize Failed");

  //
  int choice = 0;
  buyCard(adventurer, G);
  int results = cardEffect(adventurer, choice, choice, choice, G, 0, NULL);
  assert(results == 0 && "Adventurer card effect failed");

  printf("Adventurer card tested and passes!");
  return 0;
}
