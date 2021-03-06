#include "reduc.h"

void vtestreduc();

int main (int argc, char **argv) {
  vtestreduc();
}

void vtestreduc()
{
  int size, rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (((size & (size-1)) != 0))
    {
      if(!rank)
	{
	  fprintf(stderr, "'%i' is not a power of two, try again with a different <p>\n", size);
	}
    }

  /*FILE *f;
  if (rank == 0)
    {
      char filename[100];
      sprintf(filename, "stats/verification%d.txt", size);
      f = fopen(filename, "w");
    }*/
  char *test_name = "reduczeta1 vtest";
  char *log_rel_path = "vtest.txt";
  char *log_abs_path;

  FILE *log = NULL;

  if (!rank)
    log = fopen(log_rel_path, "a");
  for (int k = 1; k <= 24; k++)
    {
      int n = pow(2,k);
      double t1 = MPI_Wtime();
      double result = reduczeta1(n, size, rank);
      double t2 = MPI_Wtime();
      double time = t2-t1;
      if (rank == 0)
	{
	  double diff = fabs(result-M_PI);
	  fprintf(log, "%s p=%i: computed = %.20f, error=%.20f, time=%.20f, n=%i\n",test_name, size, result, diff, time, n);
	}
    }
  /*if (rank == 0)
    {
      fclose(f);
      }*/
  if (!rank)
    {
      fclose(log);
      log_abs_path = realpath(log_rel_path, NULL);
      printf("%s p=%i results written to: %s\n", test_name, size, log_abs_path);
      free(log_abs_path);
    }
  MPI_Finalize();
}
