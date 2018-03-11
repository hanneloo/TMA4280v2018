#Makefile for zeta0

all: test utest vtest

test : main.c zeta0.c
	gcc -o test main.c zeta0.c -lm

utest : zeta0.c testzeta0.c
	gcc -o utest zeta0.c testzeta0.c -lm

vtest : zeta0.c vtestzeta0.c
	gcc -o vtest zeta0.c vtestzeta0.c -lm

clean:
	-rm -f $(test)
	-rm -f $(utest)
	-rm -f $(vtest)
	-rm -f verification.txt
