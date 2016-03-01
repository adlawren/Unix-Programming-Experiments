// local
#include "common.h"

typedef struct assembler_thread_args_t {
  long id;
} assembler_thread_args_t;

void *assembler_thread(void *args);
