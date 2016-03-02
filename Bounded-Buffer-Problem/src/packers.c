#include "packers.h"

void pack_products(product_deque_t *product_deque, long thread_id)
{
  // TODO: Refactor? Use sprintf instead?
  //printf("[Packer %lu]: I have a box of products containing: ", thread_id);
  printf("[Packer %lu]: I have a box of products containing:\n", thread_id);
  
  product_t next_product;
  int i;
  for (i = 0; i < product_deque->size; ++i)
  {
    next_product = product_deque_pop(product_deque);
    
    printf("%s, %d\n", next_product.color, next_product.id);

    /*
    printf("%s %d", next_product.color, next_product.id);

    if (i < product_deque->size - 1)
    {
      printf(", ");
    }
    else
    {
      printf("\n");
    }
    */
  }
}

void *packer_thread(void *args)
{ 
  packer_thread_args_t *packer_thread_args = (packer_thread_args_t *) args;

  product_deque_t deque;
  product_deque_init(&deque, packer_thread_args->box_size);

  product_t p;
  while (*(packer_thread_args->unpacked_products))
  {
    int i;
    for (i = 0; i < packer_thread_args->box_size; ++i)
    {
      p.id = -1;
      p.color = "";
      while (p.id == -1) {
	p = product_deque_pop(packer_thread_args->deque);
      }
      
      // TODO: remove test
      printf("Packer (id: %lu) Obtained product with id: %d, color: %s\n", packer_thread_args->id, p.id, p.color);

      product_deque_push(&deque, &p);
      atomic_decrement(packer_thread_args->unpacked_products);
    }

    pack_products(&deque, packer_thread_args->id);
  }

  pthread_exit(0);
}
