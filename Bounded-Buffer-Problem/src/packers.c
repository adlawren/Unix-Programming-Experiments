#include "packers.h"

/** @brief A function used to print the contents of a double ended product queue and clear the queue.
 *
 * @param product_deque Pointer to a double ended product queue.
 *
 * @param thread_id The id of the thread with which the double ended product queue is associated.
 * 
 * @returns void.
 */
void pack_products(product_deque_t *product_deque, long thread_id)
{
  char box_summary[MAX_BUFFER_SIZE],
    *box_summary_base_addr = box_summary,
    *box_summary_current_addr = box_summary,
    buffer[MAX_BUFFER_SIZE];
  sprintf(buffer, "[Packer %lu]: I have a box of products containing: ", pthread_self() % 10000);

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

  atomic_print(box_summary_base_addr);
}

void *packer_thread(void *args)
{ 
  packer_thread_args_t *packer_thread_args = (packer_thread_args_t *) args;

  product_deque_t deque;
  product_deque_init(&deque, packer_thread_args->box_size);

  product_t p;
  while (atomic_read(packer_thread_args->unpacked_products))
  {
    int i;
    for (i = 0; i < packer_thread_args->box_size; ++i)
    {
      p.id = -1;
      p.color = "";
      while (p.id == -1 && atomic_read(packer_thread_args->unpacked_products)) {
	p = product_deque_pop(packer_thread_args->deque);
      }
      
      if (p.id == -1) {
        break;
      }

      product_deque_push(&deque, &p);
      atomic_decrement(packer_thread_args->unpacked_products);
    }

    if (deque.size) pack_products(&deque, packer_thread_args->id);
  }

  pthread_exit(0);
}
