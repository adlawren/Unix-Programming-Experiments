#include "packers.h"

void *packer_thread(void *args)
{ 
  packer_thread_args_t *packer_thread_args = (packer_thread_args_t *) args;

  // TODO: remove test
  printf("I'm packer thread %lu\n", packer_thread_args->id);

  product_t p;
  p.id = -1;
  p.color = "";
  while (p.id == -1) {
    printf("Queue size: %d\n", packer_thread_args->deque->size);

    p = product_deque_pop(packer_thread_args->deque);
    sleep(1);
  }

  // TODO: remove test
  printf("Obtained product with id: %lu, color: %s\n", p.id, p.color);

  pthread_exit(0);
}
