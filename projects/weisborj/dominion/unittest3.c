// This will check that the kingdomCards function works
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

int main() {

	int* k = kingdomCards(
		tribute, adventurer, outpost, minion, steward, cutpurse,
		embargo, mine, gardens, council_room);

	assert(k != NULL);

	assert(k[0] == tribute && "Inccorect Card");
	assert(k[1] == adventurer && "Inccorect Card");
	assert(k[2] == outpost && "Inccorect Card");
	assert(k[3] == minion && "Inccorect Card");
	assert(k[4] == steward && "Inccorect Card");
	assert(k[5] == cutpurse && "Inccorect Card");
	assert(k[6] == embargo && "Inccorect Card");
	assert(k[7] == mine && "Inccorect Card");
	assert(k[8] == gardens && "Inccorect Card");
	assert(k[9] == council_room && "Inccorect Card");

	free(k);

	printf("kindomCards PASSED!!!\n");
	return 0;

}
