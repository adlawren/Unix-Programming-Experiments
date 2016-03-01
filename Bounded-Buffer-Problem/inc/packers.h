// local
#include "common.h"

typedef struct packer_thread_args_t {
  long id;
} packer_thread_args_t;

void *packer_thread(void *args);
