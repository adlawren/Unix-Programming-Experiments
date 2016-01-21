#ifndef __TESTS_H__
#define __TESTS_H__

// std
#include "stdio.h"

// local
#include "utilities.h"
#include "mergesort.h"

unsigned test_fork_merge_sort(int *array,
			      int *expected_array);

void run_tests();

#endif //__TESTS_H__
