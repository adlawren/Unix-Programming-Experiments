#include "mergesort.h"

pid_t fork_merge_sort(int *sorted_array,
		    int *array,
		    int lower_bound,
		    int upper_bound)
{
	if (upper_bound - lower_bound == 1)
	{
		sorted_array[0] = array[lower_bound];
		return getpid();
	}

	int pivot = lower_bound + (upper_bound - lower_bound) / 2;
	
	// Sort left half
	// int left_half[pivot - lower_bound];
	int *left_half = get_shared_int_array(pivot - lower_bound);

	pid_t left_pid = 0;
	if ((left_pid = fork()) == 0)
	{
	  fork_merge_sort(left_half, array, lower_bound, pivot);
	  return left_pid;
	}
	else if (left_pid == -1)
	{
	  return left_pid;
	}
	
	// Sort right half
	// int right_half[upper_bound - pivot];
	int *right_half = get_shared_int_array(upper_bound - pivot);

	pid_t right_pid = 0;
	if ((right_pid = fork()) == 0)
	{
	  fork_merge_sort(right_half, array, pivot, upper_bound);
	  return right_pid;
	}
	else if (right_pid == -1)
	{
	  return right_pid;
	}

        int status;
	waitpid(left_pid, &status, 0);
	waitpid(right_pid, &status, 0);

	int min_left_index = 0, min_right_index = 0;

	int i = 0;
	for (i = 0; i < upper_bound - lower_bound; ++i)
	{
		if (min_left_index > pivot - lower_bound - 1)
		{
			sorted_array[i] = right_half[min_right_index++];
		}
		else if (min_right_index > upper_bound - pivot - 1)
		{
			sorted_array[i] = left_half[min_left_index++];
		} 
		else if (left_half[min_left_index] <= right_half[min_right_index])
		{
			sorted_array[i] = left_half[min_left_index++];
		} else {
			sorted_array[i] = right_half[min_right_index++];
		}
	}

	return getpid();
}
