#ifndef selection_sort_h
#define selection_sort_h

#include <stddef.h>

// swap entries pointed to by x and y
static inline void swap(unsigned *x, unsigned *y) {
  unsigned tmp = *x;
  *x = *y;
  *y = tmp;
}

// ask for inlining because these are used for small sizes
static inline void selection_sort(size_t n, unsigned x[]) {
  for (size_t i=0; i<n; i++) {
    unsigned t = x[i];
    for (size_t j=i+1; j<n; j++) {
      if (t > x[j]) {
        swap(&x[i], &x[j]);
        t = x[i];
      }
    }
  }
}

#endif
