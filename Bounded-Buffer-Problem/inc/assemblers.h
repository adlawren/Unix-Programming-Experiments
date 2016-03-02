// local
#include "common.h"

typedef struct assembler_thread_args_t {
  long id;
  product_deque_t *deque;
} assembler_thread_args_t;

void *assembler_thread(void *args);
