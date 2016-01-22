#include "tests.h"

unsigned test_fork_merge_sort(unsigned test_id,
			      int *sorted_array,
			      int *array,
			      int *expected_array,
			      unsigned array_size)
{
  pid_t pid = 0;
  if ((pid = fork_merge_sort(sorted_array, array, 0, array_size)) <= 0)
  {
    return pid;
  }

  if(arrays_equal(sorted_array, expected_array, array_size)) printf("Test case '%d' successful.\n", test_id);
  else
  {
    printf("FAILURE: Test case '%d' unsuccessful.\n\n", test_id);
    
    printf("Got:\n");
    print_array(sorted_array, array_size);
    
    printf("Expected:\n");
    print_array(expected_array, array_size);
  }

  return pid;
}

int run_tests()
{
  pid_t pid = 0;
  {
    const unsigned SIZE = 2;
    int *sorted_array = get_shared_int_array(SIZE);
    int *array = get_shared_int_array(SIZE);
    array[0] = 1;
    array[1] = 0;

    int *expected_array = get_shared_int_array(SIZE);
    expected_array[0] = 0;
    expected_array[1] = 1;
    
    if ((pid = test_fork_merge_sort(1, sorted_array, array, expected_array, SIZE)) <= 0)
    {
      return pid;
    }
  }

  {
    const unsigned SIZE = 3;
    int *sorted_array = get_shared_int_array(SIZE);
    int *array = get_shared_int_array(SIZE);
    array[0] = 1;
    array[1] = 2;
    array[2] = 0;

    int *expected_array = get_shared_int_array(SIZE);
    expected_array[0] = 0;
    expected_array[1] = 1;
    expected_array[2] = 2;
    
    if ((pid = test_fork_merge_sort(2, sorted_array, array, expected_array, SIZE)) <= 0)
    {
      return pid;
    }
  }

  {
    const unsigned SIZE = 4;
    int *sorted_array = get_shared_int_array(SIZE);
    int *array = get_shared_int_array(SIZE);
    array[0] = -10;
    array[1] = -15;
    array[2] = 10;
    array[3] = 5;

    int *expected_array = get_shared_int_array(SIZE);
    expected_array[0] = -15;
    expected_array[1] = -10;
    expected_array[2] = 5;
    expected_array[3] = 10;
    
    if ((pid = test_fork_merge_sort(3, sorted_array, array, expected_array, SIZE)) <= 0)
    {
      return pid;
    }
  }

  {
    const unsigned SIZE = 9;
    int *sorted_array = get_shared_int_array(SIZE);
    int *array = get_shared_int_array(SIZE);
    array[0] = 9;
    array[1] = 0;
    array[2] = -5;
    array[3] = 45;
    array[4] = -18;
    array[5] = 23;
    array[6] = 15;
    array[7] = 88;
    array[8] = 56;

    int *expected_array = get_shared_int_array(SIZE);
    expected_array[0] = -18;
    expected_array[1] = -5;
    expected_array[2] = 0;
    expected_array[3] = 9;
    expected_array[4] = 15;
    expected_array[5] = 23;
    expected_array[6] = 45;
    expected_array[7] = 56;
    expected_array[8] = 88;
    
    if ((pid = test_fork_merge_sort(4, sorted_array, array, expected_array, SIZE)) <= 0)
    {
      return pid;
    }
  }

  return pid;
}
