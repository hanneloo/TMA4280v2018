all: test vtest

clean:
	-rm -f $(test)
	-rm -f $(vtest)

test : main.c reduczeta1.c reduc.c scatter.c compute_sum_now.c processzero.c
	mpicc -o test main.c reduczeta1.c reduc.c scatter.c compute_sum_now.c processzero.c -lm

vtest: reduczeta1.c reduc.c scatter.c compute_sum_now.c processzero.c vtestreduc.c
	mpicc -o  vtest reduczeta1.c reduc.c scatter.c compute_sum_now.c processzero.c vtestreduc.c -lm
	mpirun -np 2 vtest
	mpirun -np 4 vtest
	mpirun -np 8 vtest
