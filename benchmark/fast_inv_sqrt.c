#include <stdio.h>

#include "../third_party/prof/prof.h"

#include "../src/fast_inv_sqrt.h"

#define quake_3_inv_sqrt Q_rsqrt

void quake_3_inv_sqrt_bench()
{
  printf("1,000,000 iterations of quake_3_inv_sqrt(42) (cycles): ");
  PROF_START();

  for (int i = 0; i < 1000000; i++)
    quake_3_inv_sqrt(42);

  PROF_STOP();
  PROF_STDOUT();
}

void fast_inv_sqrt_bench()
{
  printf("1,000,000 iterations of fast_inv_sqrt(42)    (cycles): ");
  PROF_START();

  for (int i = 0; i < 1000000; i++)
    fast_inv_sqrt(42);

  PROF_STOP();
  PROF_STDOUT();
}

int main()
{
  printf("\n");

  fast_inv_sqrt_bench();
  quake_3_inv_sqrt_bench();
  printf("\n");

  fast_inv_sqrt_bench();
  quake_3_inv_sqrt_bench();
  printf("\n");

  fast_inv_sqrt_bench();
  quake_3_inv_sqrt_bench();
  printf("\n");
}
