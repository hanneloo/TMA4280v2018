#Makefile for mach0

all : test utest vtest

test : main.c mach0.c arctan.c
	gcc -o test  main.c mach0.c arctan.c -lm

utest : testmach0.c mach0.c arctan.c
	gcc -o utest testmach0.c mach0.c arctan.c -lm

vtest: vtestmach0.c mach0.c arctan.c
	gcc -o vtest vtestmach0.c mach0.c arctan.c -lm

clean:
	-rm -f $(test)
	-rm -f $(utest)
	-rm -f $(vtest)
	-rm -f verification.txt
