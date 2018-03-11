#include "reduc.h"

int main(int argc, char **argv)
{
  if(argc != 2)
    {
      printf("Usage: %s <n_iterations>\n", argv[0]);
      exit(-1);
    }

  int size, rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int n = atoi(argv[1]);
 
  if (((size & (size-1)) != 0))
  {
    if(!rank)
      {
	fprintf(stderr, "'%i' is not a power of two, try again with a different <p>\n", size);
      }
    return 1;
  }
  
  double result = reduczeta1(n, size, rank);
  if (rank == 0)
    {
      printf("Result of pi using reduc at rank %d: %.15f \n", rank, result);
    }

  //vtestzeta1();
  MPI_Finalize();

}
