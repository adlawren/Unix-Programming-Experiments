#ifndef __DEQUE_H__
#define __DEQUE_H__

// std
#include "stdio.h"
#include "stdlib.h"

// misc
#include "string.h"
#include "ctype.h"

typedef struct dynamic_string_array_t {
  size_t size, max_size, max_string_size;
  char **array;
} dynamic_string_array_t;

/** @brief Initializes the given double ended queue.
 *
 * @param deque Pointer to a double ended queue instance.
 *
 * @param max_size The fixed size of the queue. 
 * 
 * @returns void.
 */
void dynamic_string_array_init(dynamic_string_array_t *string_array, size_t initial_max_size, size_t max_string_size);

/** @brief Attempts to add the given product to the end of the double ended queue.
 *
 * @param deque Pointer to a double ended queue instance.
 * 
 * @param to_add Pointer to a product instance.
 *
 * @returns int Returns 0 if the given product was successfully added to the double ended queue, -1 otherwise.
 */
void dynamic_string_array_push(dynamic_string_array_t *string_array, char *to_add);

/** @brief Returns and removes the product from the front of the double ended queue.
 *
 * @param deque Pointer to a double ended queue instance.
 * 
 * @returns product_t Returns the product which was at the front of the double ended queue, if the queue is empty at the time of invocation, a product with an id of -1 is returned.
 */
void dynamic_string_array_pop(dynamic_string_array_t *string_array, char *result);

void dynamic_string_array_sort(dynamic_string_array_t *string_array);

/** @brief Removes all products from the double ended queue.
 *
 * @param deque Pointer to a double ended queue instance.
 * 
 * @returns void.
 */
void dynamic_string_array_clear(dynamic_string_array_t *string_array);

#endif //__DEQUE_H__
