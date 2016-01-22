#ifndef __UTILITIES_H__
#define __UTILITIES_H__

// std
#include "stdio.h"
#include "sys/mman.h"

// TODO: add description
void print_array(int * array, unsigned n);

// TODO: add description
unsigned arrays_equal(int *array1, int *array2, unsigned n);

// TODO: add description
int * get_shared_int_array(unsigned array_size);

#endif //__UTILITIES_H__
