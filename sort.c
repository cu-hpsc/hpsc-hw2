#include "parse.h"
#include "rdtsc.h"
#include "quicksort.h"
#include "radix.h"

#include <stdio.h>
#include <stdlib.h>

void init_uniform(size_t n, unsigned x[], unsigned long max)
{
  srandom(1);
  for (size_t i=0; i<n; i++)
    x[i] = (unsigned long)random() % max;
}

void validate(size_t n, unsigned x[]) {
  for (size_t i=1; i<n; i++) {
    // check for out of order
    if (x[i] < x[i-1]) {
      fprintf(stderr,"elements %zd and %zd are in the wrong order\n", i-1, i);
      exit(1);
    }
  }
}

int main(int argc, char **argv)
{
  struct args args;

  // argument parsing via parse.h
  parse_args(&args, argc, argv);

  // initialize array
  unsigned *x = malloc(sizeof(unsigned) * args.array_len);
  init_uniform(args.array_len, x, args.max_value);

  ticks_t starttick = rdtsc();
  quicksort(args.array_len, x);
  printf("quicksort: sorted %zd entries in %llu ticks\n", args.array_len, rdtsc() - starttick);
  validate(args.array_len, x);

  init_uniform(args.array_len, x, args.max_value);
  starttick = rdtsc();
  radix_sort(args.array_len, x);
  printf("radix: sorted %zd entries in %llu ticks\n", args.array_len, rdtsc() - starttick);
  validate(args.array_len, x);

  free(x);
  return 0;
}
