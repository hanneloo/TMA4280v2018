#include "zeta0.h"

void vtestzeta0()
{
  FILE *f = fopen("verification.txt", "w");
  for (int k = 1; k<= 24; k++)
    {
      int n = pow(2,k);
      double result = zeta0(n);
      double diff = fabs(result - M_PI);
      fprintf(f, "The difference between pi and zeta0(n=%d): %.30f\n",n,diff);
    }
  fclose(f);
  printf("Verification.txt is updated successfully.\n");
}

int main (int argc, char **argv)
{
  vtestzeta0();
}
