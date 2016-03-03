#ifndef __PACKERS_H__
#define __PACKERS_H__

// sys
#include "pthread.h"

// local
#include "product.h"
#include "utilities.h"
#include "deque.h"

#define MAX_BUFFER_SIZE 2048
#define PACKER_SLEEP_DURATION 100

typedef struct packer_thread_args_t {
  long id;
  unsigned box_size;
  int* unpacked_products;
  product_deque_t *deque;
} packer_thread_args_t;

/** @brief The thread associated with a packer within the factory simulation.
 *
 * @param i Void pointer to the arguments of the thread; internally assumed to be a pointer to a packer_thread_args_t struct.
 * 
 * @returns void.
 */
void *packer_thread(void *args);

#endif //__PACKERS_H__
