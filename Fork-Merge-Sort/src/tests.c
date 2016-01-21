#include "tests.h"

// TODO: implement
unsigned test_fork_merge_sort(int *array,
			      int *expected_array)
{
  return 0;
}

void run_tests()
{
	{
		int array[1] = {1};

		int sorted_array[1];
		merge_sort(sorted_array, array, 0, 1);

		int expected_array[1] = {1};

        	if(arrays_equal(array, expected_array, 1)) printf("Test case 1 successful.\n");
	        else
		{
			printf("FAILURE: Test case 1 unsuccessful.\n");
			print_array(sorted_array, 1);
		}
	}

	{
		const int size = 2;
		int array[size];
		array[0] = 1;
		array[1] = 0;

		int sorted_array[size];
		merge_sort(sorted_array, array, 0, size);

		int expected_array[size];
		expected_array[0] = 0;
		expected_array[1] = 1;

		if (arrays_equal(sorted_array, expected_array, size)) printf("Test case 2 successful.\n");
		else
		{
			printf("FAILURE: Test case 2 unsuccessful.\n");
			print_array(sorted_array, size);
		}
	}

	{
		const int size = 3;
                int array[size];
                array[0] = 1;
                array[1] = 2;
		array[2] = 0;

                int sorted_array[size];
                merge_sort(sorted_array, array, 0, size);

                int expected_array[size];
                expected_array[0] = 0;
                expected_array[1] = 1;
		expected_array[2] = 2;

                if (arrays_equal(sorted_array, expected_array, size)) printf("Test case 3 successful.\n");
                else
                {
                        printf("FAILURE: Test case 2 unsuccessful.\n");
                        print_array(sorted_array, size);
                }

	}

	{
		const int size = 4;
                int array[size];
                array[0] = -10;
                array[1] = -15;
		array[2] = 10;
		array[3] = 5;

                int sorted_array[size];
                merge_sort(sorted_array, array, 0, size);

                int expected_array[size];
                expected_array[0] = -15;
                expected_array[1] = -10;
		expected_array[2] = 5;
		expected_array[3] = 10;

                if (arrays_equal(sorted_array, expected_array, size)) printf("Test case 4 successful.\n");
                else
                {
                        printf("FAILURE: Test case 4 unsuccessful.\n");
                        print_array(sorted_array, size);
                }

	}

	{
		const int size = 9;
                int array[size];
                array[0] = 9;
                array[1] = 0;
		array[2] = -5;
		array[3] = 45;
		array[4] = -18;
		array[5] = 23;
		array[6] = 15;
		array[7] = 88;
		array[8] = 56;

                int sorted_array[size];
                merge_sort(sorted_array, array, 0, size);

                int expected_array[size];
                expected_array[0] = -18;
                expected_array[1] = -5;
		expected_array[2] = 0;
		expected_array[3] = 9;
		expected_array[4] = 15;
		expected_array[5] = 23;
		expected_array[6] = 45;
		expected_array[7] = 56;
		expected_array[8] = 88;

                if (arrays_equal(sorted_array, expected_array, size)) printf("Test case 5 successful.\n");
                else
                {
                        printf("FAILURE: Test case 5 unsuccessful.\n");
                        print_array(sorted_array, size);
                }

	}
}
