#include "mergesort.h"

void merge_sort(int *sorted_array,
		int *array,
		int lower_bound,
		int upper_bound)
{
  return;
}

int fork_merge_sort(int *sorted_array,
		    int *array,
		    int lower_bound,
		    int upper_bound)
{
	if (upper_bound - lower_bound == 1)
	{
		sorted_array[0] = array[lower_bound];
		return 0;
	}

	int pivot = lower_bound + (upper_bound - lower_bound) / 2;
	
	// Sort left half
	int left_half[pivot - lower_bound];

	pid_t pid = 0;
	if ((pid = fork()) == 0)
	{
	  merge_sort(left_half, array, lower_bound, pivot);
	  return pid;
	}
	else if (pid == -1)
	{
	  return pid;
	}
	
	// Sort right half
	int right_half[upper_bound - pivot];

	if ((pid = fork()) == 0)
	{
	  merge_sort(right_half, array, pivot, upper_bound);
	  return pid;
	}
	else if (pid == -1)
	{
	  return pid;
	}

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
		else if (left_half[min_left_index] < right_half[min_right_index])
		{
			sorted_array[i] = left_half[min_left_index++];
		} else {
			sorted_array[i] = right_half[min_right_index++];
		}
	}

	return pid;
}
