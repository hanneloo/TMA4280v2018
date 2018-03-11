all: test vtest

clean:
	-rm -f $(test)
	-rm -f $(vtest)

test : main.c zeta2.c
	gcc -o test main.c zeta2.c -lm -fopenmp

vtest: zeta2.c vtestzeta2.c
	gcc -o  vtest zeta2.c vtestzeta2.c -lm -fopenmp
