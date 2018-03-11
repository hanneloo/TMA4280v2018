#include "mach0.h"

void testmach0()
{
  double result = mach0(3);
  double expected = 3.141592;
  double epsilon = 0.001;
  double diff = fabs(result-expected);
  assert(diff <= epsilon);
  printf("Utest gives the difference between pi and  mach0(n=3) as  %.25f\n", diff);
}

int main(int argv, char **argc)
{
  testmach0();
}
