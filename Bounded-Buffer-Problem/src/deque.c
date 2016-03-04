#include "deque.h"

void product_deque_init(product_deque_t *deque, unsigned max_size)
{
  sem_init(&deque->full, 0, 0);
  sem_init(&deque->empty, 0, max_size);
  
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, 0);
  pthread_mutex_lock(&mutex);

  deque->products = (product_t *) malloc(sizeof(product_t) * max_size);
  deque->size = 0;
  deque->max_size = max_size;
}

int product_deque_push(product_deque_t *deque, product_t* to_add)
{
  sem_wait(&deque->empty);

  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, 0);
  pthread_mutex_lock(&mutex);

  if (deque->size >= deque->max_size) {
    return -1;
  }
  
  deque->products[deque->size].color = to_add->color;
  deque->products[deque->size].id = to_add->id;
  ++deque->size;

  sem_post(&deque->full);

  return 0;
}

product_t product_deque_pop(product_deque_t *deque)
{
  sem_wait(&deque->full);

  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, 0);
  pthread_mutex_lock(&mutex);

  product_t to_return;
  if (deque->size > 0)
  {
    to_return = deque->products[0];

    int i;
    for (i = 0; i < deque->size - 1; ++i)
    {
      deque->products[i] = deque->products[i + 1];
    }
    
    --deque->size;
  }
  else
  {
    to_return.color = "";
    to_return.id = -1;
  }

  sem_post(&deque->empty);

  return to_return;
}

void product_deque_clear(product_deque_t *deque)
{
  sem_destroy(&deque->full);
  sem_destroy(&deque->empty);

  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, 0);
  pthread_mutex_lock(&mutex);
  
  free(deque->products);
  deque->products = 0;
}
