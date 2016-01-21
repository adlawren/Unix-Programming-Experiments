#include "utilities.h"

void print_array(int *array, unsigned n)
{
        printf("\n-----Array Contents-----\n");

        int i = 0;
        for (i = 0; i < n; ++i)
        {
                printf("%d ", array[i]);
        }

        printf("\n----------\n");
}

unsigned arrays_equal(int *array1, int *array2, unsigned n)
{
	unsigned i = 0;
	for (i = 0; i < n; ++i)
	{
		if (array1[i] != array2[i]) return 0;
	}

	return 1;
}
