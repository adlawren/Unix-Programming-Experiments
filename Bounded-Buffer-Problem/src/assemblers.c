#include "assemblers.h"

void *assembler_thread(void *args)
{
  assembler_thread_args_t *assembler_thread_args = (assembler_thread_args_t *) args;

  // TODO: remove test
  printf("I'm assembler thread %lu\n", assembler_thread_args->id);

  pthread_exit(0);
}
