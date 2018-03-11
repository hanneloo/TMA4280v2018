#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <mpi.h>

void processzero(int n, double *values);
double compute_sum_now(double *local_values, int count);
double rootzeta1(int iterations, int size, int rank);
void scatter(double *local_values, double *values, int local_count);
