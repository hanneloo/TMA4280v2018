all: test vtest

clean:
	-rm -f $(test)
	-rm -f $(vtest)

test : main.c rootmach1.c scatter.c compute_sum_now.c processzero.c
	mpicc -o test main.c rootmach1.c scatter.c compute_sum_now.c processzero.c -lm

vtest: rootmach1.c scatter.c compute_sum_now.c processzero.c vtestmach1.c
	mpicc -o  vtest rootmach1.c scatter.c compute_sum_now.c processzero.c vtestmach1.c -lm
	mpirun -np 2 vtest
	mpirun -np 4 vtest
	mpirun -np 8 vtest
