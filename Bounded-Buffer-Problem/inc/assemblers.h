// sys
#include "pthread.h"

// local
#include "deque.h"
#include "product.h"

#define MAX_COLOR_COUNT 147

typedef struct assembler_thread_args_t {
  long id;
  unsigned product_count;
  product_deque_t *deque;
} assembler_thread_args_t;

/** @brief The thread associated with an assembler within the factory simulation.
 *
 * @param args Void pointer to the arguments of the thread; internally assumed to be a pointer to an assembler_thread_args_t struct.
 * 
 * @returns void.
 */
void *assembler_thread(void *args);
