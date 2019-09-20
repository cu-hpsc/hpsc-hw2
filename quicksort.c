#include "quicksort.h"
#include "selection_sort.h"

// return estimate of the median of the array
static inline size_t median_estimate(size_t n, const unsigned x[]) {
  return x[n/2]; // can be a very poor estimate
}

// partition so that
//   x[i] < pivot for i < left
//   x[i] >= pivot for i >= right
static void partition(size_t n, unsigned x[], unsigned pivot, size_t *left, size_t *right) {
  size_t l = 0, r = n-1;
  while (1) {
    while (x[l] < pivot) l++;
    while (x[r] > pivot) r--;
    if (l >= r) {r++; break;}
    swap(&x[l], &x[r]);
    l++;
    r--;
  }
  *left = l;
  *right = r;
}

// sort array of length n in increasing order
void quicksort(size_t n, unsigned x[]) {
  if (n < 8) {
    selection_sort(n, x);
  } else {
    unsigned pivot = median_estimate(n, x);
    size_t left, right;
    partition(n, x, pivot, &left, &right);
    quicksort(left, x);
    quicksort(n - right, x + right);
  }
}
