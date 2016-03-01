#include "packers.h"

void *packer_thread(void *args)
{
  packer_thread_args_t *packer_thread_args = (packer_thread_args_t *) args;

  // TODO: remove test
  printf("I'm packer thread %lu\n", packer_thread_args->id);

  pthread_exit(0);
}
