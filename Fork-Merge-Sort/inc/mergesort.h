#ifndef __MERGESORT_H__
#define __MERGESORT_H__

// std
#include "unistd.h"
#include "sys/wait.h"

// local
#include "utilities.h"

/** @brief Tests the Fork-Merge-Sort implementation.
 *
 * @param test_id A numerical identifier for the test case.
 * 
 * @param sorted_array An integer array, the contents of which will be replaced by the sorted contents of the unsorted array.
 *
 * @param array An integer array, the contents of which are to be sorted.
 *
 * @param lower_bound The smallest index of the subarray to be sorted, inclusive.
 *
 * @param upper_bound The largest index of the subarray to be sorted, exclusive.
 *
 * @return pid_t the pid associated with the process exiting the subroutine. 
 */
pid_t fork_merge_sort(int *sorted_array,
		    int *array,
		    int lower_bound,
		    int upper_bound);

#endif //__MERGESORT_H__
