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

int atomic_read(int *i)
{
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, 0);
  pthread_mutex_lock(&mutex);

  return *i;
}

void atomic_decrement(int *i)
{
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, 0);
  pthread_mutex_lock(&mutex);

  --(*i);
}
