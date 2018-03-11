#include "zeta0.h"

void testzeta0()
{
  double result = zeta0(3);
  double expected = 3.141592;
  double diff = fabs(result-expected);
  printf("Utest gives the difference between pi and  zeta0(n=3) as  %.25f\n", diff);
}

int main(int argc, char **argv)
{
  testzeta0();
}
