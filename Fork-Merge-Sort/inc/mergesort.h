#ifndef __MERGESORT_H__
#define __MERGESORT_H__

// std
#include "unistd.h"
#include "sys/wait.h"

// local
#include "utilities.h"

int fork_merge_sort(int *sorted_array,
		    int *array,
		    int lower_bound,
		    int upper_bound);

#endif //__MERGESORT_H__
