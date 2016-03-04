#include "factory.h"

int main(int argc, char *argv[])
{
  // Ensure the appropriate number of command line arguments is provided
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

  // Ensure each argument is non-zero/in the correct range
  if (a == 0 || a > MAX_COLOR_COUNT)
  {
    fprintf(stderr, "ERROR: The number of assemblers must be greater than zero and less than or equal to 147.\n");
    return -1;
  }

  if (p == 0)
  {
    fprintf(stderr, "ERROR: The number of packers must be non-zero.\n");
    return -1;
  }
  
  if (l == 0)
  {
    fprintf(stderr, "ERROR: The size of the bounded buffer must be non-zero.\n");
    return -1;
  }

  if (n == 0)
  {
    fprintf(stderr, "ERROR: The number of products which comprise a box must be non-zero.\n");
    return -1;
  }

  if (c == 0)
  {
    fprintf(stderr, "ERROR: The number of products produced by assemblers must be non-zero.\n");
    return -1;
  }

  // Initialize the shared buffer
  product_deque_t deque;
  product_deque_init(&deque, l);

  // Variable used to indicate the total number of products yet to be packed
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

  // Wait for all products to be packed
  while (atomic_read(unpacked_products));

  // Resolve potential deadlock (s)
  int k;
  for (k = 0; k < p; ++k) {
    sem_post(&deque.full);
  }

  // Wait for the packer threads to complete
  int m;
  for (m = 0; m < p; ++m)
  {
    pthread_join(packer_threads[m], 0);
  }

  // TODO: remove?
  assert(*unpacked_products == 0);
  assert(deque.size == 0);

  free(unpacked_products);
  product_deque_clear(&deque);

  pthread_exit(0);

  return 0;
}
