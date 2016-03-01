#include "deque_test.h"

typedef struct test_thread_args_t {
  long id;
  product_deque_t *deque;
} test_thread_args_t;

void *test_thread(void *args)
{
  test_thread_args_t *test_thread_args = (test_thread_args_t *) args;

  // TODO: Remove; test
  printf("I'm thread %lu\n", test_thread_args->id);

  product_t p;
  p.color = 1;
  p.id = test_thread_args->id;

  product_deque_push(test_thread_args->deque, &p);

  pthread_exit(0);
}

void deque_pop_assert(product_deque_t *deque, product_t *expected)
{
  product_t product = product_deque_pop(deque);
  assert(expected->color == product.color);
  assert(expected->id == product.id);
}

void run_deque_tests()
{
  unsigned queue_size = 10;

  product_deque_t deque;
  product_deque_init(&deque, queue_size);

  product_t expected_result;
  expected_result.color = 0;
  expected_result.id = -1;
  deque_pop_assert(&deque, &expected_result);

  pthread_t test_threads[queue_size];
  test_thread_args_t test_thread_args[queue_size];

  int i;
  for (i = 0; i < queue_size; ++i)
  {
    test_thread_args[i].id = i;
    test_thread_args[i].deque = &deque;
    if (pthread_create(&test_threads[i], 0, test_thread, (void *) &test_thread_args[i]))
    {
      fprintf(stderr, "ERROR: pthread creation failed\n");
      return;
    }
  }

  int j;
  for (j = 0; j < queue_size; ++j)
  {
    pthread_join(test_threads[j], 0);
  }

  product_t next_product;
  int k;
  for (k = 0; k < queue_size; ++k)
  {
    next_product = product_deque_pop(&deque);
    printf("Next product contents: color: %d, id: %lu\n", (int) next_product.color, next_product.id);
  }

  expected_result.color = 0;
  expected_result.id = -1;
  deque_pop_assert(&deque, &expected_result);

  product_deque_clear(&deque);
}
