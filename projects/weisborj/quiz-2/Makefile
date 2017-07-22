testme: testme.c
	gcc testme.c -o testme.o

test: testme
	./testme.o
all: testme test

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out
