#include "deque_test.h"

typedef struct test_thread_args_t {
  long id;
  product_deque_t *deque;
} test_thread_args_t;

void *test_thread(void *args)
{
  test_thread_args_t *test_thread_args = (test_thread_args_t *) args;
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

  /*
  product_t p;
  p.color = 1;
  p.id = 1;

  product_t expected_result;
  
  expected_result.color = 0;
  expected_result.id = -1;
  deque_pop_assert(&deque, &expected_result);

  assert(product_deque_push(&deque, &p) == 0);
  assert(product_deque_push(&deque, &p) == 0);
  assert(product_deque_push(&deque, &p) == -1);
  */
  
  // Wait for threads to complete
  pthread_exit(0); // TODO: fix; this is broken.

  int j;
  for (j = 0; j < queue_size; ++j)
  {
    expected_result.color = 1;
    expected_result.id = j;
    deque_pop_assert(&deque, &expected_result);
  }

  // TODO: remove test
  printf("Made it here\n");

  expected_result.color = 0;
  expected_result.id = -1;
  deque_pop_assert(&deque, &expected_result);

  product_deque_clear(&deque);
}
