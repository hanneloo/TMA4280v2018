all: test vtest

clean:
	-rm -f $(test)
	-rm -f $(vtest)

test : main.c rootzeta1.c scatter.c compute_sum_now.c processzero.c
	mpicc -o test main.c rootzeta1.c scatter.c compute_sum_now.c processzero.c -lm

vtest: rootzeta1.c scatter.c compute_sum_now.c processzero.c vtestzeta1.c
	mpicc -o  vtest rootzeta1.c scatter.c compute_sum_now.c processzero.c vtestzeta1.c -lm
	mpirun -np 2 vtest
	mpirun -np 4 vtest
	mpirun -np 8 vtest
