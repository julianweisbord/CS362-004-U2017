// Check that isGameOver works
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>



int main(){
  int over_status;
  struct gameState old_state;

  int k[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  initializeGame(2, k, 2, &old_state);
  // Game is over when 3 supplies are empty
  old_state.supplyCount[1] = 0;
  old_state.supplyCount[4] = 0;
  old_state.supplyCount[7] = 0;

  over_status = isGameOver(&old_state);
  assert(over_status == 1 && "Game not over");
  // Restart game
  initializeGame(2, k, 2, &old_state);

  // If there are no more provinces, the game ends
  old_state.supplyCount[province] = 0;

  over_status = isGameOver(&old_state);
  assert(over_status == 1 && "Game not over");

  printf("isGameOver PASSED!!!\n");

  return 0;
}
