#include "zeta0.h"

int main(int argc, char **argv)
{

  if(argc != 2)
    {
      printf("Usage: %s <n_iterations>\n", argv[0]);
    }
  int n = atoi(argv[1]);
  if(n <=0)
    {
      fprintf(stderr, "'%i' is not a positive integer\n",n);
      printf("Usage: %s <n_iterations>\n", argv[0]);
    }
  double result = zeta0(n);
  printf("Using the Riemann zeta function to calculate an approximation of pi\n");
  printf("With %d iterations, the result is: pi approx=  %.15f \n", n, result);
}
