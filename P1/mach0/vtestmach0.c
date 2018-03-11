#include "mach0.h"

void vtestmach0()
{
  FILE *f = fopen("verification.txt", "w");
  for (int k = 1; k<= 24; k++)
    {
      int n = pow(2,k);
      double result = mach0(n);
      double diff = fabs(result - M_PI);
      fprintf(f, "The difference between pi and mach0(n=%d): %.50f\n",n,diff);
    }
  fclose(f);
  printf("Verification.txt was updated successfully.\n");
}

int main(int argv, char **argc)
{
  vtestmach0();
}
