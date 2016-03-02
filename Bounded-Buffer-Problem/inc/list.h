#ifndef __LIST_H__
#define __LIST_H__

/*
  Implementation of a linked list in C, wherein nodes contain a single integer for data.
 */

// std
#include "stdlib.h"

// TODO: move to common.h?
#include "product.h"

// TODO: rename
typedef struct product_node_t {
  struct product_node_t *next;
  product_t data;
} product_node_t;

// TODO: rename
typedef struct product_list_t {
  product_node_t *head, *tail;
  unsigned size;
} product_list_t;

/** @brief Initializes the contents of an int_list instance.
 *
 * @param list A pointer to an int_list instance.
 *
 * @return void
 */
void product_list_init(product_list_t *list);

/** @brief Adds an int_node to the given int_list instance with the given integer value.
 *
 * @param list A pointer to an int_list instance.
 *
 * @param to_add An integer with which to construct an int_node to be added to the list.
 *
 * @return void
 */
void product_list_add(product_list_t *list, product_t to_add);

/** @brief Removes a node from the list with the given integer value.
 *
 * @param list A pointer to an int_list instance.
 * 
 * @param to_remove An integer using which an int_node in the int_list may be identified and removed.
 *
 * @return unsigned Returns 1 if an int_node was removed from the list with the given integer value, zero otherwise.
 */
product_t product_list_remove(product_list_t *list, product_t to_remove);

/** @brief Removes all nodes from the list.
 *
 * @param list A pointer to an int_list instance.
 *
 * @return void
 */
void product_list_clear(product_list_t *list);

#endif //__LIST_H__
