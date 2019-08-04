unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.c rngs.o -lm
	./unittest1

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.c rngs.c -lm $(CFLAGS)
	./unittest2

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.c rngs.c -lm $(CFLAGS)
	./unittest3

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.c rngs.c -lm $(CFLAGS)
	./unittest4

unittest5: unittest5.c dominion.o rngs.o
	gcc -o unittest5 -g unittest5.c dominion.c rngs.c -lm $(CFLAGS)
	./unittest5

rc1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o -coverage -fpic -lm
	./randomtestcard1

rc2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o -coverage -fpic -lm
	./randomtestcard2

rc3: randomtestcard3.c dominion.o rngs.o
	gcc -o randomtestcard3 -g randomtestcard3.c dominion.o rngs.o -coverage -fpic -lm
	./randomtestcard3
