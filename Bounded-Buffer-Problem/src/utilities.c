#include "utilities.h"

size_t strings_equal(char *str_a, char * str_b)
{
  char *a_ptr = str_a, *b_ptr = str_b;
  while (*a_ptr != '\0')
  {
    if (*a_ptr != *b_ptr)
    {
      return 0;
    }

    ++a_ptr;
    ++b_ptr;
  }

  return 1;
}

size_t products_equal(product_t *product_a, product_t *product_b)
{
  if (!strings_equal(product_a->color, product_b->color))
  {
    return 0;
  }

  if (product_a->id != product_b->id)
  {
    return 0;
  }

  return 1;
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
