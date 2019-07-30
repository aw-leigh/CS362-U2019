CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc -o testme -g testme.c $(CFLAGS) && testme

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out testme.exe testme output.txt
