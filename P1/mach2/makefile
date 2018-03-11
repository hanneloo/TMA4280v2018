all: test vtest

clean:
	-rm -f $(test)
	-rm -f $(vtest)

test : main.c mach2.c arctan.c
	gcc -o test main.c mach2.c arctan.c -lm -fopenmp

vtest: mach2.c vtestmach2.c arctan.c
	gcc -o  vtest mach2.c vtestmach2.c arctan.c -lm -fopenmp
