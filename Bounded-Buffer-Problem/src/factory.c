#include "factory.h"

int main(int argc, char *argv[])
{
  // Ensure the appropriate number of command line arguments is provided.
  if (argc != 6)
  {
    fprintf(stderr, "ERROR: Five command line arguments must be given.\n");
    return -1;
  }

  // Place the command line parameters into the respective variables
  char *temp;
  unsigned a = strtol(argv[1], &temp, 10),
    p = strtol(argv[2], &temp, 10),
    l = strtol(argv[3], &temp, 10),
    n = strtol(argv[4], &temp, 10),
    c = strtol(argv[5], &temp, 10);

  // Initialize the shared buffer
  product_deque_t deque;
  product_deque_init(&deque, l);

  // Variable used to indicate the total number of products yet to be packed.
  int *unpacked_products = (int *) malloc(sizeof(int));
  *unpacked_products = a * c;

  // Create assembler threads
  pthread_t assembler_threads[a];
  assembler_thread_args_t assembler_thread_args[a];

  int i;
  for (i = 0; i < a; ++i)
  {
    assembler_thread_args[i].id = i;
    assembler_thread_args[i].product_count = c;
    assembler_thread_args[i].deque = &deque;
    if (pthread_create(&assembler_threads[i], 0, assembler_thread, (void *) &assembler_thread_args[i]))
    {
      fprintf(stderr, "ERROR: pthread creation failed\n");
      return -1;
    }
  }

  // Create packer threads
  pthread_t packer_threads[p];
  packer_thread_args_t packer_thread_args[p];

  int j;
  for (j = 0; j < p; ++j)
  {
    packer_thread_args[j].id = j;
    packer_thread_args[j].box_size = n;
    packer_thread_args[j].unpacked_products = unpacked_products;
    packer_thread_args[j].deque = &deque;
    if (pthread_create(&packer_threads[j], 0, packer_thread, (void *) &packer_thread_args[j]))
    {
      fprintf(stderr, "ERROR: pthread creation failed\n");
      return -1;
    }
  }

  // Wait for the packer threads to complete
  int k;
  for (k = 0; k < p; ++k)
  {
    pthread_join(packer_threads[k], 0);
  }

  // TODO: remove?
  assert(*unpacked_products == 0);
  assert(deque.size == 0);

  free(unpacked_products);
  product_deque_clear(&deque);

  pthread_exit(0);

  return 0;
}
