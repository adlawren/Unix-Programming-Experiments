#include "deque_test.h"

const char *TEST_COLORS[] = {"AliceBlue","AntiqueWhite","Aqua","Aquamarine","Azure","Beige","Bisque","Black","BlanchedAlmond","Blue","BlueViolet","Brown","BurlyWood","CadetBlue","Chartreuse","Chocolate","Coral","CornflowerBlue","Cornsilk","Crimson","Cyan","DarkBlue","DarkCyan","DarkGodenRod","DarkGray","DarkGrey","DarkGreen","DarkKhaki","DarkMagenta","DarkOliveGreen","Darkorange","DarkOrchid","DarkRed","DarkSalmon","DarkSeaGreen","DarkSlateBlue","DarkSlateGray","DarkSlateGrey","DarkTurquoise","DarkViolet","DeepPink","DeepSkyBlue","DimGray","DimGrey","DodgerBlue","FireBrick","FloralWhite","ForestGreen","Fuchsia","Gainsboro","GhostWhite","God","GodenRod","Gray","Grey","Green","GreenYellow","HoneyDew","HotPink","IndianRed","Indigo","Ivory","Khaki","Lavender","LavenderBlush","LawnGreen","LemonChiffon","LightBlue","LightCoral","LightCyan","LightGodenRodYellow","LightGray","LightGrey","LightGreen","LightPink","LightSalmon","LightSeaGreen","LightSkyBlue","LightSlateGray","LightSlateGrey","LightSteelBlue","LightYellow","Lime","LimeGreen","Linen","Magenta","Maroon","MediumAquaMarine","MediumBlue","MediumOrchid","MediumPurple","MediumSeaGreen","MediumSlateBlue","MediumSpringGreen","MediumTurquoise","MediumVioletRed","MidnightBlue","MintCream","MistyRose","Moccasin","NavajoWhite","Navy","OdLace","Olive","OliveDrab","Orange","OrangeRed","Orchid","PaleGodenRod","PaleGreen","PaleTurquoise","PaleVioletRed","PapayaWhip","PeachPuff","Peru","Pink","Plum","PowderBlue","Purple","Red","RosyBrown","RoyalBlue","SaddleBrown","Salmon","SandyBrown","SeaGreen","SeaShell","Sienna","Silver","SkyBlue","SlateBlue","SlateGray","SlateGrey","Snow","SpringGreen","SteelBlue","Tan","Teal","Thistle","Tomato","Turquoise","Violet","Wheat","White","WhiteSmoke","Yellow","YellowGreen"};

typedef struct test_thread_args_t {
  long id;
  product_deque_t *deque;
} test_thread_args_t;

/** @brief The thread used during concurrent testing of the product_deque_t struct and associated functions.
 *
 * @param args Void pointer to the arguments of the thread; internally assumed to be a pointer to an test_thread_args_t struct.
 * 
 * @returns void.
 */
void *test_thread(void *args)
{
  test_thread_args_t *test_thread_args = (test_thread_args_t *) args;

  printf("Current thread id: %lu\n", test_thread_args->id);

  product_t p;
  p.color = (char *) TEST_COLORS[test_thread_args->id];
  p.id = test_thread_args->id;

  product_deque_push(test_thread_args->deque, &p);

  pthread_exit(0);
}

/** @brief Asserts that contents of the product removed from the front of the given double ended product queue are equivalent to the contents of the given product.
 *
 * @param deque Pointer to a double ended queue instance. 
 *
 * @param expected Pointer to a product, the contents of which are expected to be identical of the popped product.
 *
 * @returns void.
 */
void deque_pop_assert(product_deque_t *deque, product_t *expected)
{
  product_t product = product_deque_pop(deque);
  assert(strings_equal(expected->color, product.color));
  assert(expected->id == product.id);
}

void run_deque_tests()
{  
  unsigned queue_size = 5;

  product_deque_t deque;
  product_deque_init(&deque, queue_size);

  product_t p, expected_result;
  expected_result.color = "";
  expected_result.id = -1;
  deque_pop_assert(&deque, &expected_result);

  int i;
  for (i = 0; i < queue_size; ++i)
  {
    p.color = "Tast Color";
    p.id = i;
    product_deque_push(&deque, &p);
  }

  int j;
  for (j = 0; j < queue_size; ++j)
  {
    expected_result.color = "Tast Color";
    expected_result.id = j;
    deque_pop_assert(&deque, &expected_result);
  }

  expected_result.color = "";
  expected_result.id = -1;
  deque_pop_assert(&deque, &expected_result);

  product_deque_clear(&deque);
}

void run_threaded_deque_tests()
{
  unsigned queue_size = 5;

  product_deque_t deque;
  product_deque_init(&deque, queue_size);

  product_t expected_result;
  expected_result.color = "";
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
    printf("Next product contents: color: %s, id: %d\n", next_product.color, next_product.id);
  }

  expected_result.color = "";
  expected_result.id = -1;
  deque_pop_assert(&deque, &expected_result);

  product_deque_clear(&deque);
}
