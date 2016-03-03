#ifndef __LIST_H__
#define __LIST_H__

/*
  Implementation of a linked list in C, wherein nodes contain products for data.
 */

// std
#include "stdlib.h"

// local
#include "product.h"

typedef struct product_node_t {
  struct product_node_t *next;
  product_t data;
} product_node_t;

typedef struct product_list_t {
  product_node_t *head, *tail;
  unsigned size;
} product_list_t;

/** @brief Initializes the contents of a product list instance.
 *
 * @param list A pointer to a product list instance.
 *
 * @return void
 */
void product_list_init(product_list_t *list);

/** @brief Adds a new product node to the given product list instance with the values in the given product.
 *
 * @param list A pointer to a product list instance.
 *
 * @param to_add A product with which to construct a product node to be added to the product list.
 *
 * @return void
 */
void product_list_add(product_list_t *list, product_t to_add);

/** @brief Removes a node from the product list with the id of the given product.
 *
 * @param list A pointer to an product list instance.
 * 
 * @param to_remove A product using which a product node in the product list may be identified and removed.
 *
 * @return product_t Returns the product that was removed from the product list with the same id as the given product, otherwise a product with an id of -1.
 */
product_t product_list_remove(product_list_t *list, product_t to_remove);

/** @brief Removes all nodes from the list.
 *
 * @param list A pointer to a product list instance.
 *
 * @return void
 */
void product_list_clear(product_list_t *list);

#endif //__LIST_H__
