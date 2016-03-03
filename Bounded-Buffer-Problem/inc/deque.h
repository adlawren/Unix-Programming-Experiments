#ifndef __DEQUE_H__
#define __DEQUE_H__

// std
#include "stdio.h"
#include "stdlib.h"

// sys
#include "pthread.h"

// local
#include "product.h"
#include "utilities.h"

typedef struct product_deque_t {
  product_t *products;
  unsigned size, max_size;
} product_deque_t;

/** @brief Initializes the given double ended queue.
 *
 * @param deque Pointer to a double ended queue instance.
 *
 * @param max_size The fixed size of the queue. 
 * 
 * @returns void.
 */
void product_deque_init(product_deque_t *deque, unsigned max_size);

/** @brief Attempts to add the given product to the end of the double ended queue.
 *
 * @param deque Pointer to a double ended queue instance.
 * 
 * @param to_add Pointer to a product instance.
 *
 * @returns int Returns 0 if the given product was successfully added to the double ended queue, -1 otherwise.
 */
int product_deque_push(product_deque_t *deque, product_t *to_add);

/** @brief Returns and removes the product from the front of the double ended queue.
 *
 * @param deque Pointer to a double ended queue instance.
 * 
 * @returns product_t Returns the product which was at the front of the double ended queue, if the queue is empty at the time of invocation, a product with an id of -1 is returned.
 */
product_t product_deque_pop(product_deque_t *deque);

/** @brief Removes all products from the double ended queue.
 *
 * @param deque Pointer to a double ended queue instance.
 * 
 * @returns void.
 */
void product_deque_clear(product_deque_t *deque);

#endif //__DEQUE_H__
