#include "utilities.h"

void print_array(int *array, unsigned n)
{
  // printf("\n-----Array Contents-----\n");
  
  int i = 0;
  for (i = 0; i < n; ++i)
  {
    printf("%d ", array[i]);
  }
  
  printf("\n");

  // printf("\n----------\n");
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

int * get_shared_int_array(unsigned array_size)
{
  void *array = 0;
  if ((array = mmap(0, array_size * sizeof(int), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0)) == 0)
  {
    fprintf(stderr, "ERROR: failed to initailize shared memory.\n");
    return 0;
  }

  return (int *) array;
}

int * parse_into_shared_int_array(char *line, unsigned *array_size)
{
  // Use linked list to buffer the integers
  int_list list;
  int_list_init(&list);

  char *temp;
  char *token = strtok(line, " ");
  while (token)
  {
    int_list_add(&list, (int) strtol(token, &temp, 10));
    token = strtok(NULL, " ");
  }

  *array_size = list.size;

  // Initialize shared memory.
  void *array = 0;
  if ((array = mmap(0, list.size * sizeof(int), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0)) == 0)
  {
    printf("ERROR: failed to initailize shared memory.\n");
    return 0;
  }
  
  int *int_array = (int *) array;

  int i = 0;
  while (list.head)
  {
    int_array[i++] = list.head->data;
    int_list_remove(&list, list.head->data);
  }

  return int_array;
}
