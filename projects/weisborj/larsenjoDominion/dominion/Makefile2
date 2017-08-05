CFLAGS = -Wall -fpic -coverage -lm
TESTS = test1 test2 test3 test4 cardtest1 cardtest2 cardtest3 cardtest4
RANDTESTS = randomtest1 randomtest2 randomtestadventurer

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

unittestresults.out: all $(TESTS) runAllTests

randomtestcard1.out: all randomtest1
	-./randomtestcard1 >> randomtestcard1.out 2>&1
	gcov dominion.c -b >> randomtestcard1.out
	grep -e "function smith" dominion.c.gcov >> randomtestcard2.out
	#cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2.out: all randomtest2
	-./randomtestcard2 >> randomtestcard2.out 2>&1
	gcov dominion.c -b >> randomtestcard2.out
	grep -e "function vill" dominion.c.gcov >> randomtestcard2.out
	#cat dominion.c.gcov >> randomtestcard2.out

randomtestadventurer.out: all randomtestadventurer
	-./randomtestadventurer >> randomtestadventurer.out 2>&1
	gcov dominion.c -b >> randomtestadventurer.out
	grep -e "function advent" dominion.c.gcov >> randomtestadventurer.out
	#cat dominion.c.gcov >> randomtestadventurer.out

randomtestresults: all $(RANDTESTS) runRandTests

test1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

test2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)

test3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)

test4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)

randomtest1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtest2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

runAllTests:
	-./unittest1 >> unittestresult.out 2>&1
	-./unittest2 >> unittestresult.out 2>&1
	-./unittest3 >> unittestresult.out 2>&1
	-./unittest4 >> unittestresult.out 2>&1
	-./cardtest1 >> unittestresult.out 2>&1
	-./cardtest2 >> unittestresult.out 2>&1
	-./cardtest3 >> unittestresult.out 2>&1
	-./cardtest4 >> unittestresult.out 2>&1
	gcov dominion.c -b >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe badTestDrawCard
	rm -f cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4 randomtestcard1 randomtestcard2 randomtestadventurer
