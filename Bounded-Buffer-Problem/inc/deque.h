#ifndef __DEQUE_H__
#define __DEQUE_H__

// local
#include "common.h"

typedef struct product_t {
  unsigned char color;
  long id;
} product_t;

typedef struct product_deque_t {
  product_t *products;
  unsigned size, max_size;
} product_deque_t;

void product_deque_init(product_deque_t *deque, unsigned max_size);

int product_deque_push(product_deque_t *deque, product_t *to_add);

product_t product_deque_pop(product_deque_t *deque);

void product_deque_clear(product_deque_t *deque);

#endif //__DEQUE_H__
