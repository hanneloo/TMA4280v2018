#include "mach2.h"

void vtestmach2();

int main (int argc, char **argv) {
  vtestmach2();
}

void vtestmach2()
{
  int nthreads, n;

  if (((nthreads & (nthreads-1)) != 0))
    {
      fprintf(stderr, "'%i' is not a power of two, try again with a different <p>\n", nthreads);
    }

  char *test_name = "mach2 vtest";
  char *log_rel_path = "vtest.txt";
  char *log_abs_path;

  FILE *log = NULL;

  log = fopen(log_rel_path, "a");
  for (int j = 1; j<=3; j++)
    {
      int nthreads = pow(2,j);
      for (int k = 1; k <= 24; k++)
	{
	  int n = pow(2,k);
	  double t1 = omp_get_wtime();
	  double result = mach2(nthreads, n);
	  double t2 = omp_get_wtime();
	  double time = t2-t1;
	  double diff = fabs(result-M_PI);
	  fprintf(log, "%s nthreads=%i: computed=%.20f, error=%.20f, time=%.20f,  n=%i\n",test_name, nthreads, result, diff, time, n);	
	}
      log_abs_path = realpath(log_rel_path, NULL);
      printf("%s nthreads=%i results written to: %s\n", test_name, nthreads, log_abs_path);
      free(log_abs_path);
    }
  fclose(log);
}
