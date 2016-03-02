// local
#include "common.h"

typedef struct assembler_thread_args_t {
  long id;
  unsigned product_count;
  product_deque_t *deque;
} assembler_thread_args_t;

void *assembler_thread(void *args);
