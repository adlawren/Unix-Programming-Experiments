#ifndef __UTILITIES_H__
#define __UTILITIES_H__

// std
#include "stdio.h"

// sys
#include "string.h"
#include "sys/mman.h"
#include "pthread.h"

// local
#include "product.h"

/** @brief Determines whether or not the contents of the two given strings are identical.
 *
 * @param str_a The first string for comparison.
 *
 * @param str_b The second string for comparison.
 * 
 * @returns size_t One if the contents of the two strings are identical, zero otherwise.
 */
size_t strings_equal(char *str_a, char *str_b);

/** @brief Determines whether or not the contents of the two given products are identical.
 *
 * @param str_a The first product for comparison.
 *
 * @param str_b The second product for comparison.
 * 
 * @returns size_t One if the contents of the two products are identical, zero otherwise.
 */
size_t products_equal(product_t *product_a, product_t *product_b);

/** @brief Reads the numerical value associated with the given integer pointer after constructing a mutex to prohibit concurrent access to the pointer.
 *
 * @param i Pointer to an integer value.
 * 
 * @returns int The value associated with the given integer pointer.
 */
int atomic_read(int *i);

/** @brief Decrements the numerical value associated with the given integer pointer after constructing a mutex to prohibit concurrent access to the pointer.
 *
 * @param i Pointer to an integer value.
 * 
 * @returns void.
 */
void atomic_decrement(int *i);

#endif //__UTILITIES_H__
