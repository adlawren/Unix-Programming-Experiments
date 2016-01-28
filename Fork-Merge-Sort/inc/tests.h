#ifndef __TESTS_H__
#define __TESTS_H__

// std
#include "stdio.h"

// local
#include "utilities.h"
#include "mergesort.h"

/** @brief Tests the Fork-Merge-Sort implementation.
 *
 * @param test_id A numerical identifier for the test case.
 *
 * @param sorted_array An integer array to be overwritten at runtime with the sorted duplicate of the unsorted array.
 *
 * @param array The integer array to be sorted.
 *
 * @param expected_array An integer array, the contents of which indicate the expected contents of the sorted array upon completion of the sorting routine.
 *
 * @param array_size The size of the array to be sorted.
 * 
 * @return pid_t the pid associated with the process exiting the subroutine.
 */
pid_t test_fork_merge_sort(unsigned test_id,
			      int *sorted_array,
			      int *array,
			      int *expected_array,
			      unsigned array_size);

/** @brief Runs several, implemented test cases.
 *
 * @return pid_t the pid associated with the process exiting the subroutine.
 */
pid_t run_tests();

#endif //__TESTS_H__
