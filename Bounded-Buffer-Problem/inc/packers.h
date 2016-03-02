#ifndef __PACKERS_H__
#define __PACKERS_H__

// local
#include "common.h"

#define PACKER_SLEEP_DURATION 100

typedef struct packer_thread_args_t {
  long id;
  product_deque_t *deque;
} packer_thread_args_t;

void *packer_thread(void *args);

#endif //__PACKERS_H__
