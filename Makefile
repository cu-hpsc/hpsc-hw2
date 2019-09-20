CC = gcc
CFLAGS ?= -O3 -march=native -fopenmp -Wall
CFLAGS += -MMD -MP # generates *.d dependency files

sources.c = sort.c quicksort.c radix.c

sort : $(sources.c:%.c=%.o)

# include the dependency files if they exist
-include $(sources.c:%.c=%.d)
