#include "deque.h"

int product_deque_advance(product_deque_t *deque)
{
  if (deque->size > 0)
  {
    int i;
    for (i = 0; i < deque->size - 1; ++i)
    {
      deque->products[i] = deque->products[i + 1];
    }

    return 0;
  }

  return -1;
}

void product_deque_init(product_deque_t *deque, unsigned max_size)
{
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, 0);
  pthread_mutex_lock(&mutex);

  deque->products = (product_t *) malloc(sizeof(product_t) * max_size);
  deque->size = 0;
  deque->max_size = max_size;
}

int product_deque_push(product_deque_t *deque, product_t* to_add)
{
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, 0);
  pthread_mutex_lock(&mutex);

  if (deque->size >= deque->max_size) {
    return -1;
  }

  deque->products[deque->size].color = to_add->color;
  deque->products[deque->size].id = to_add->id;
  ++deque->size;

  return 0;
}

product_t product_deque_pop(product_deque_t *deque)
{
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, 0);
  pthread_mutex_lock(&mutex);

  product_t to_return;

  if (deque->size > 0)
  {
    to_return = deque->products[0];

    // product_deque_advance(deque);
    // Or, alternatively:
    int i;
    for (i = 0; i < deque->size - 1; ++i)
    {
      deque->products[i] = deque->products[i + 1];
    }
    
    --deque->size;
  }
  else
  {
    to_return.color = 0;
    to_return.id = -1;
  }

  return to_return;

  product_t p;
  p.color = (unsigned char) 1;
  p.id = 1;

  return p;
}

void product_deque_clear(product_deque_t *deque)
{
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, 0);
  pthread_mutex_lock(&mutex);

  free(deque->products);
  deque->products = 0;
}
