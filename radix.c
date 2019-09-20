#include <stdlib.h>
#include <limits.h>

#include "selection_sort.h"

typedef unsigned UInt;

static inline int getbin(UInt x, unsigned shift) {
  unsigned mask = 0xff;
  return (x >> shift) & mask;
}

static void sort_radix_internal(size_t n, UInt x[], unsigned shift) {
  const int nbins = 256;
  size_t cursor[256],end[256] = {};

  for (size_t i=0; i<n; i++) end[getbin(x[i], shift)]++;
  cursor[0] = 0;
  for (int i=1; i<nbins; i++) {
    cursor[i] = end[i-1];
    end[i] += end[i-1];
  }
  for (int bin=0; bin<nbins; bin++) {
    for ( ; cursor[bin] != end[bin]; cursor[bin]++) {
      int i = cursor[bin];
      for (int t = getbin(x[i], shift); t != bin; t = getbin(x[i], shift)) {
        int j = cursor[t]++;
        swap(&x[i], &x[j]);
      }
    }
  }
  if (shift > 0) {
    for (int bin=0; bin<256; bin++) {
      int binstart = bin == 0 ? 0 : cursor[bin-1];
      int binsize = cursor[bin] - binstart;
      if (binsize > 64) {
        sort_radix_internal(binsize, x + binstart, shift-CHAR_BIT);
      } else if (binsize > 1) {
        selection_sort(binsize, x + binstart);
      }
    }
  }
}

void radix_sort(size_t n, unsigned x[]) {
  sort_radix_internal(n, x, (sizeof(x[0]) - 1)*CHAR_BIT);
}
