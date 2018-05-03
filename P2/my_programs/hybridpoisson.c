/*                      TMA4280 Introduction to supercomputing
                                   Hannelore Olsen
                                Spring semester 2018

  This program is a C program to solve the two-dimenstional Poisson equation on a 
     unit square using one-dimensional eigenvalue decompositions and fase sine 
                                    transforms.

   This particular version uses hybrid-implementation of MPI and OpenMP in order 
         to solve the problem with t threads for each of the  P processes.
                                                                                   */



//------------------------------------Header---------------------------------------------

// Include
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <omp.h>
#include <math.h>


// Definitions
typedef double real;
typedef int bool;

# define true 1
# define false 0
# define PI 3.1415926535897323846


// Function prototypes
real *make_1D_array(size_t n, bool zero);
real **make_2D_array(size_t n1, size_t n2, bool zero);
real rhs(real x, real y);
void shop_matrix(double **b, int m, int n);
int is_pow2(int n);
void par_transpose(real **bt, real **b, real *send, real *recv, int size, int m, int n, int rank);
real sol(real x, real y);
void fst_(real *v, int *n, real *w, int *nn);
void fstinv_(real *v, int *n, real *w, int *nn);


//-------------------------------------Main function--------------------------------------------
int main(int argc, char **argv)
{
  // Check input
  if (argc < 3)
    {
      printf("Not enough arguments:\n");
      printf("./hybridpoisson <problem size> <number of threads per process>\n");
    }
  
  // Initialize the MPI procedure
  int t = atoi(argv[2]);
  omp_set_num_threads(t);
  int rank;
  int size;
  MPI_Init(&argc, &argv);

  // Characteristics of the parallel procedure
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // Start time
  real time;
  if(rank == 0)
    {
      time = MPI_Wtime();
    }

  // Define grid size
  int n = atoi(argv[1]);
  int m = n-1;
  int avg = n/size;
  int nn = 4*n;
  real h = 1.0/n;

  // Unit test/check
  if (rank == 0)
    {
      printf("Size: n: %i, P: %i, Threads: t = %i\n", n, size, t);
    }
  if (!is_pow2(n))
    {
      if (rank == 0)
	{
	  printf("Problem size is not a power of 2. \n");
	}
      MPI_Abort(MPI_COMM_WORLD, MPI_ERR_DIMS);
      return 0;
    }

  // Define matrices
  real **b = make_2D_array(avg, n, false);
  real *send = make_1D_array((size_t)(avg*n), false);
  real *recv = make_1D_array((size_t)(avg*n), false);
  real **bt = make_2D_array(avg, n, false);

  //--------------------------- Verification test---------------------
  real **a_sol = make_2D_array(avg, n, false);
  real u_max = 0.0;
  real error = 0.0;
  real *x_axis = make_1D_array(avg, false);
  real *y_axis = make_1D_array(n, false);
  real **z = make_2D_array(t, nn, false);
  real *diag = make_1D_array(n, false);

  #pragma omp parallel
  {
    #pragma omp for
    for(size_t i = 0; i < avg; i++)
      {
	x_axis[i] = (i + 1 + avg*rank)*h;
      }
    #pragma omp for
    for(size_t i = 0; i < n+1; i++)
      {
	y_axis[i] = (i + 1)*h;
      }
    #pragma omp for
    for (size_t i = 0; i < n; i++)
      {
	diag[i] = 2.0*(1.0 - cos((i+1)*PI/n));
      }
#pragma omp for collapse(2)
    for (size_t i = 0; i < avg; i++)
      {
	for (size_t j = 0; j < n; j++)
	  {
	    a_sol[i][j] = sol(x_axis[i], y_axis[j]);
	    b[i][j] = h*h*rhs(x_axis[i], y_axis[j]);
	  }
      }

    // Step 1
    #pragma omp for
    for (size_t i = 0; i < avg; i++)
      {
	fst_(b[i], &n, z[omp_get_thread_num()], &nn);
      }
    #pragma omp master
    par_transpose(bt, b, send, recv, size, avg, n, rank);
    #pragma omp barrier
    #pragma omp for
    for (size_t i = 0; i < avg; i++)
      {
	fstinv_(bt[i], &n, z[omp_get_thread_num()], &nn);
      }

    // Step 2
#pragma omp for collapse(2)
    for (size_t i = 0; i < avg; i++)
      {
	for (size_t j = 0; j < n; j++)
	  {
	    bt[i][j] = bt[i][j] / (diag[i + rank*avg] + diag[j]);
	  }
      }

    // Step 3
    #pragma omp for
    for (size_t i = 0; i < avg; i++)
      {
	fst_(bt[i], &n, z[omp_get_thread_num()], &nn);
      }

    #pragma omp master
    par_transpose(b, bt, send, recv, size, avg, n, rank);
    #pragma omp barrier
    #pragma omp for
    for (size_t i = 0; i < avg; i++)
      {
	fstinv_(b[i], &n, z[omp_get_thread_num()], &nn);
      }

    // Compute max value and error of the solution
    real err = 0.0;
#pragma omp for collapse(2)
    for (size_t i = 0; i < avg; i++)
      {
	for (size_t j = 0; j < m; j++)
	  {
	    err = fabs(b[i][j] - a_sol[i][j]);
	    error = error > err ? error : err;
	    u_max = u_max > b[i][j] ? u_max : b[i][j];
	  }
      }
  }

  real u_max_tot = 0;
  real err_max_tot = 0;

  MPI_Reduce(&u_max, &u_max_tot, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
  MPI_Reduce(&error, &err_max_tot, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

  // End time and print results
  if (rank == 0){
    time = MPI_Wtime() - time;
    printf("u_max = %.15e \n", u_max_tot);
    printf("Time: %f\n", time);
    printf("Error: %.15f\n\n", err_max_tot);
  }

  // Finalize MPI procedure
  MPI_Finalize();
  return 0;
}


// -----------------------------Functions used in the main-----------------------------

// Right hand side
real rhs(real x, real y)
{
  //return 5*PI*PI*sin(PI*x)*sin(2*PI*y);
  return exp(x)*sin(2*PI*x)*sin(2*PI*y);
}

// Convergence test
real sol(real x, real y)
{
  return sin(PI*x)*sin(2*PI*y);
}

// Allocate 1D array
real *make_1D_array(size_t n, bool zero)
{
  if(zero)
    {
      return (real *)calloc(n, sizeof(real));
    }
  return (real *)malloc(n*sizeof(real));
}

// Allocate 2D array
real **make_2D_array(size_t n1, size_t n2, bool zero)
{
  real **ret = (real **)malloc(n1*sizeof(real *));
  if (zero)
    {
      ret[0] = (real *)calloc(n1*n2, sizeof(real));
    }
  else
    {
      ret[0] = (real *)malloc(n1*n2*sizeof(real));
    }
  for (size_t i = 1; i < n1; i++)
    {
      ret[i] = ret[i-1]+n2;
    }
  return ret;
}

// Print matrix
void show_matrix(real **b, int avg, int n)
{
  for (int i = 0; i < avg; i++)
    {
      for (int j = 0; j < n; j++)
	{
	  printf("%f", b[i][j]);
	}
      printf("\n");
    }
}

// Transpose matrix in paralell way
void par_transpose(real **bt, real **b, real *send, real *recv, int size, int avg, int n, int rank)
{
  size_t i;
  size_t j;
  int val = 0;
  for (i = 0; i < (size_t)avg; i++)
    {
      for (j = 0; j < (size_t)n; j++)
	{
	  send[avg*i + (j/avg)*(avg*avg) + j%avg] = b[i][j];
	}
    }
  MPI_Alltoall(&send[0], avg*avg, MPI_DOUBLE, &recv[0], avg*avg, MPI_DOUBLE, MPI_COMM_WORLD);
  for (j = 0; j < (size_t)n; j++)
    {
      for (i = 0; i < (size_t)avg; i++)
	{
	  bt[i][j] = recv[val];
	  val++;
	}
    }
}

// Check if of power 2
int is_pow2(int a)
{
  real b = log(a)/log(2);
  return floor(b) == b;
}
