# HW2: Sorting and graph coloring
## Due: 2019-09-30 (Monday)

Click to [accept this assignment](https://classroom.github.com/a/d4_gpzck)

## Using Makefiles

This homework contains several source files written using implicit
rules (`make -p -f /dev/null | less` to see them all).  It sets up
dependencies so that only files you need get recompiled.  You can also
write your own rules

```make
target : prerequisites ...
	recipe to execute
```

An example would be
```make
foo : foo.c
	gcc -O3 foo.c -o foo
```

We can also write pattern rules of the form

```make
%.o : %.c
```

which will create `foo.o` from `foo.c`.  When using pattern rules (and
also for non-pattern rules), it's useful to use special variables such as

* `$@` name of the target
* `$^` list of all prerequisites
* `$<` the first prerequisite

resulting in a pattern rule such as

```make
%: %.c
        $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@
```

Note that this has used several common variables for

* `CC`: the C compiler, e.g., `gcc`
* `CFLAGS`: flags passed to the C compiler, e.g., `-O2 -march=native -fopt-info`
* `CPPFLAGS`: flags needed for preprocessing, e.g., `-I/path/to/include -DMY_MACRO=1`
* `LDFLAGS`: flags intended for the linker, e.g., `-L/path/to/lib`
* `LDLIBS`: libraries to link, e.g., `-lblas -lm`

The above rule is bult-in so we don't have to write it.  You can see
all built-in rules by running the following (piped through `less`
because it's a lot of output).

    make -p -f /dev/null | less

The [documentation](https://www.gnu.org/software/make/manual/make.html) is comprehensive.

## Part 1: Parallel Quicksort

![Quicksort from Wikipedia](https://commons.wikimedia.org/wiki/File:Sorting_quicksort_anim.gif)

Recall from lecture that `scan` operations have logarithmic depth,
thus selection of values that satisfy a predicate also have
logarithmic depth.  The fundamental operation in quicksort is to
partition an array into items smaller than, and larger than, a chosen
pivot.

    [entries < pivot, pivot, entries >= pivot]

In `Report.ipynb`, write pseudocode for a parallel algorithm to
partition an array of length `n` in `O(log n)` computational depth
using `scan`.

If pivots are chosen well, such that the array is approximately split
in half on each iteration, what is the computational depth of a
quicksort based on the scan-based primitive?

Implement this algorithm to sort `unsigned` data in-place in ascending
order using a function with prototype

```c
void parallel_quicksort(size_t n, unsigned data[]);
```

You may base your implementation on `omp for` or `omp task`
primitives.  You may choose any deterministic method for choosing the
pivot.  Note that a reference serial implementation is given.

## Part 2: [Bitonic Sort](https://en.wikipedia.org/wiki/Bitonic_sorter)

A bitonic sort consists of a sequence of steps in which two values are
compared, and swapped if they are out of the desired order.  Every pair
at each step of the algorithm is compared (and perhaps swapped)
independently, so the DAG has `n/2` parallelism.  In `Report.ipynb`,
compare and contrast the algorithmic characteristics of bitonic sort
with parallel quicksort.  You might discuss SIMD, ILP, and/or threaded
parallel attributes.

Implement a bitonic sort using OpenMP.

```c
void bitonic_sort(size_t n, unsigned data[]);
```

## Part 3: Sorting Performance and Scaling

Compare the performance of sorting arrays using
* the provided reference `quicksort`
* your `parallel_quicksort`
* your `bitonic_sort`
* the provided (sequential) `radix_sort`

Choose what data to operate on (different length arrays, different
distributions such as random and already-sorted) and how much
parallelism to expose.  Choose at least two figure types to convey
your results in a way that enables a decision and discuss your
conclusions.

You may also consider other algorithms, including open source
implementations you find online.  Please report interesting results in
[this issue](https://github.com/cucs-hpsc/hpsc-hw2/issues/1).

### Part 4: Reproducibility

Would another class member be able to read your report and reproduce your results?
Revisit the above parts to ensure that this is indeed achievable.
In `Report.ipynb`, document any additional information that may be needed to reproduce and explain what obstacles you anticipate that may prevent reproduction.
