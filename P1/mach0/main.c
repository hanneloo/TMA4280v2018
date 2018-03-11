#include "mach0.h"

int main(int argc, char **argv)
{
  if (argc != 2){
    printf("Usage: %s <n_iterations>\n", argv[0]);
  }
  int n = atoi(argv[1]);
  double result = mach0(n);
  printf("Result: %.17f\n", result);
}
