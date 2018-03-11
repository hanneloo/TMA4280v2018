#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <mpi.h>
#include <omp.h>

void scatter(double *local_values, double *values, int local_count);
void processzero(int n, double *values, int nthreads);
double hybridzeta(int nthreads, int iterations, int size, int rank);
double compute_sum_now(double *local_values, int count);
