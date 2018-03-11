all: test vtest

test : main.c hybridzeta.c scatter.c processzero.c compute_sum_now.c
	mpicc -o test main.c hybridzeta.c scatter.c processzero.c compute_sum_now.c -lm -fopenmp

vtest: hybridzeta.c scatter.c processzero.c compute_sum_now.c vtesthybrid.c
	mpicc -o vtest hybridzeta.c scatter.c processzero.c compute_sum_now.c vtesthybrid.c -lm -fopenmp
	mpirun -np 2 vtest
	mpirun -np 4 vtest
	mpirun -np 8 vtest
clean :
	-rm -f $(test)
	-rm -f $(vtest)

