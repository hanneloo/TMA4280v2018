#include "hello.h"
#include "goodbye.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
  if(argc < 2)
    {
      printf("Invalid number of arguments\n");
      return 1;
    }
  int v = atoi(argv[1]);
  if((v % 2) == 1)
    {
      print_hello();
    }
  else
    {
      print_goodbye();
    }
  return 0;
}
