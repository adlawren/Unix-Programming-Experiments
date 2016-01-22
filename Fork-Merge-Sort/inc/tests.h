#ifndef __TESTS_H__
#define __TESTS_H__

// std
#include "stdio.h"

// local
#include "utilities.h"
#include "mergesort.h"

unsigned test_fork_merge_sort(unsigned test_id,
			      int *sorted_array,
			      int *array,
			      int *expected_array,
			      unsigned array_size);

int run_tests();

#endif //__TESTS_H__
