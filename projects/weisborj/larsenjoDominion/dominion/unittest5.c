/*
 * unittest1.c
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

/*
int whoseTurn(struct gameState *state) 
  return state->whoseTurn;
*/
  
struct gameState* g = malloc(sizeof(struct gameState));
printf("********Testing whoseTurn()********\n");
int i;

for(i = 1; i < 4; i++)
{
    g->whoseTurn = i;
    if(whoseTurn(g) == i)
        printf("Test %d passed\n", i);
    else
        printf("Test %d failed\n", i);
}

g->whoseTurn = 1000;
if(whoseTurn(g) == 1000)
    printf("Function allows excessively high values\n");
else
    printf("Test 4 passed\n");
g->whoseTurn = -1;
if(whoseTurn(g) == -1)
    printf("Function allows negative values\n");
else
    printf("Test 5 passed\n");

g->whoseTurn = 'a';
if(whoseTurn(g) == 'a')
    printf("Function allows letters\n");
else
    printf("Test 6 passed\n");

g->whoseTurn = "abc";
if(whoseTurn(g) == "abc")
    printf("Function allows strings\n");
else
    printf("Test 7 passed\n");

printf("********whoseTurn() tests complete********\n\n");
}//end main
