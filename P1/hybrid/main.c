#include "hybrid.h"

int main(int argc, char **argv)
{
  if(argc != 3){
    printf("Usage: %s <n_threads> <n_iterations>\n", argv[0]);
    exit(-1);
  }
  int size, rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int nthreads = atoi(argv[1]);
  int n = atoi(argv[2]);

  if(((size & (size-1)) != 0))
    {
      if(!rank)
	{
	  fprintf(stderr, "'%i' is not a power of two, try again with a different <p>\n", size);
	}
      return 1;
    }
  
  double result = hybridzeta(nthreads, n, size, rank);
  if (rank == 0)
    {
      printf("Result using hybrid(threads=%i, iter=%i) is, pi = %.15f \n", nthreads, n, result);
    }

  MPI_Finalize();
}
