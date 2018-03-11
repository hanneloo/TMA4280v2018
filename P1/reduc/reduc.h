#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <mpi.h>

void processzero(int n, double *values);
double compute_sum_now(double *local_values, int count);
void scatter(double *local_values, double *values, int local_count);
double reduczeta1(int iterations, int size, int rank);
double reduc(int size, int rank, double sum_now);

