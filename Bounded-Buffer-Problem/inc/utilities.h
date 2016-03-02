#ifndef __UTILITIES_H__
#define __UTILITIES_H__

// std
#include "stdio.h"
#include "string.h"
#include "sys/mman.h"
#include "pthread.h"

// local
#include "list.h"

/** @brief Prints to contents of the given array to stdout.
 *
 * @param array The array, the contents of which will be printed.
 *
 * @param n The size of the array.
 * 
 * @return void
 */
void print_array(int * array, unsigned n);

/** @brief Determines whether or not the contents of the two given arrays are identical.
 *
 * @param array1 The first array for comparison.
 *
 * @param array2 The second array for comparison. 
 *
 * @param n The size of the array.
 * 
 * @returns unsigned One if the contents of the two arrays are identical, zero otherwise.
 */
unsigned arrays_equal(int *array1, int *array2, unsigned n);

/** @brief Returns a shared integer array, the size of which is equal to the specified size.
 *
 * @param array_size The size of the array to be allocated.
 * 
 * @return int* A pointer to the allocated shared array.
 */
int * get_shared_int_array(unsigned array_size);

/** @brief Parse the given string (assumed to contain space separated integers) into a shared array.
 *
 * @param line The string to be parsed, containing space separated integers.
 *
 * @param array_size A pointer to an integer, the value of which will be updated to the size of the array as computed during parsing.
 * 
 * @return int* A pointer to the allocated shared array.
 */
int * parse_into_shared_int_array(char *line, unsigned *array_size);

int atomic_read(int *i);

void atomic_decrement(int *i);

#endif //__UTILITIES_H__
