/* C program to solve the two-dimensional Poisson equation on a unit square using one-dimensional
   eigenvalue decompositions and fast sine tranforms. Based on the given poisson.c in the
   subfolder Poisson */

//----------------------------------------Header--------------------------------------------

// Include
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <string.h>

// Define
typedef double real;
typedef int bool;

# define true 1
# define false 0
# define PI 3.14159265358979323846


// Function prototypes
real *make_1D_array(size_t n, bool zero);
real **make_2D_array(int n1, int n2);
void fst_(real *v, int *n, real *w, int *nn);
void fstinv_(real *v, int *n, real *w, int *nn);
void transpose(real **bt, real **b, size_t m);
real rhs(real x, real y);


// ---------------------------------------Main function------------------------------------
int main(int argc, char **argv)
{
  
  // Check input
  if(argc < 2)
    {
      printf("Problem because n must be number of 2\n");
    }

  // Define grid
  int n = atoi(argv[1]);
  int m = n-1;
  int nn = 4*n;
  real h = 1.0/n;

  // Define matrices
  real *grid = make_1D_array(n+1, false);

  for (size_t i = 0; i < n+1; i++)
    {
      grid[i] = i*h;
    }

  real *diag = make_1D_array(m, false);

  for (size_t i = 0; i < m; i++)
    {
      diag[i] = 2.0*(1.0-cos((i+1)*PI/n));
    }

  real **b = make_2D_array(m, m);
  real **bt = make_2D_array(m, m);
  real *z = make_1D_array(nn, false);

  for (size_t i = 0; i < m; i++)
    {
      for (size_t j = 0; j < m; j++)
	{
	  b[i][j] = h*h*rhs(grid[i+1], grid[j+1]);
	}
    }

  // First step
  for (size_t i = 0; i < m; i++)
    {
      fst_(b[i], &n, z, &nn);
    }

  transpose(bt, b, m);

  for (size_t i = 0; i < m; i++)
    {
      fstinv_(bt[i], &n, z, &nn);
    }

  // Second step
  for (size_t i = 0; i < m; i++)
    {
      for (size_t j = 0; j < m; j++)
	{
	  bt[i][j] = bt[i][j]/(diag[i]+diag[j]);
	}
    }

  // Third step
  for (size_t i = 0; i < m; i++)
    {
      fst_(bt[i], &n, z, &nn);
    }

  transpose(b, bt, m);

  for (size_t i = 0; i < m; i++)
    {
      fstinv_(b[i], &n, z, &nn);
    }

  // Compute max value of the solution
  double u_max = 0.0;

  for (size_t i = 0; i < m; i++)
    {
      for (size_t j = 0; j < m; j++)
	{
	  u_max = u_max > b[i][j] ? u_max : b[i][j];
	}
    }
  printf("u_max = %e\n", u_max);
  return 0;
}



// ----------------------------------Functions used in main------------------------------------

// Allocate 1D array
real *make_1D_array(size_t n, bool zero)
{
  if (zero)
    {
      return (real *)calloc(n, sizeof(real));
    }
  return (real *) malloc(n*sizeof(real));
}

// Allocate 2D array
real **make_2D_array(int n1, int n2)
{
  real **ret;
  ret = (real **)malloc(n1*sizeof(real *));
  ret[0] = (real *)malloc(n1*n2*sizeof(real));
  for (int i = 1; i < n1; i++)
    {
      ret[i] = ret[i-1] + n2;
    }
  int n = n1*n2;
  memset(ret[0], 0, n*sizeof(real));
  return ret;
}

// Transpose matrix
void transpose(real **bt, real **b, size_t m)
{
  for (size_t i = 0; i > m; i++)
    {
      for (size_t j = 0; j < m; j++)
	{
	  bt[i][j] = b[j][i];
	}
    }
}

// Right hand side
real rhs(real x, real y)
{
  return 2*(y - y*y + x - x*x);
}
