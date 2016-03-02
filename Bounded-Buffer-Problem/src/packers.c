#include "packers.h"

void pack_products(product_deque_t *product_deque, long thread_id)
{
  char box_summary[MAX_BUFFER_SIZE],
    *box_summary_base_addr = box_summary,
    *box_summary_current_addr = box_summary,
    buffer[MAX_BUFFER_SIZE];
  sprintf(buffer, "[Packer %lu]: I have a box of products containing: ", thread_id);

  snprintf(box_summary_current_addr, sizeof(buffer), "%s", buffer);
  box_summary_current_addr += strlen(buffer);

  product_t next_product;
  while (product_deque->size)
  {
    next_product = product_deque_pop(product_deque);

    if (product_deque->size)
    {
      sprintf(buffer, "%s %d, ", next_product.color, next_product.id);
    }
    else
    {
      sprintf(buffer, "%s %d\n", next_product.color, next_product.id);
    }

    snprintf(box_summary_current_addr, sizeof(buffer), "%s", buffer);
    box_summary_current_addr += strlen(buffer);
  }

  printf("%s", box_summary_base_addr);
}

void *packer_thread(void *args)
{ 
  packer_thread_args_t *packer_thread_args = (packer_thread_args_t *) args;

  product_deque_t deque;
  product_deque_init(&deque, packer_thread_args->box_size);

  product_t p;
  while (*(packer_thread_args->unpacked_products))
  {
    // TODO: Remove; test
    printf("[Packer %lu]: Unpacked products %d\n", packer_thread_args->id, atomic_read(packer_thread_args->unpacked_products));

    int i;
    for (i = 0; i < packer_thread_args->box_size; ++i)
    {
      p.id = -1;
      p.color = "";
      while (p.id == -1) {
	p = product_deque_pop(packer_thread_args->deque);
      }
      
      // TODO: remove test
      // printf("Packer (id: %lu) Obtained product with id: %d, color: %s\n", packer_thread_args->id, p.id, p.color);

      product_deque_push(&deque, &p);
      atomic_decrement(packer_thread_args->unpacked_products);
    }

    pack_products(&deque, packer_thread_args->id);
  }

  pthread_exit(0);
}
