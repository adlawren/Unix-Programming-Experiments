#include "deque_test.h"

const char *COLORS[] = {"AliceBlue","AntiqueWhite","Aqua","Aquamarine","Azure","Beige","Bisque","Black","BlanchedAlmond","Blue","BlueViolet","Brown","BurlyWood","CadetBlue","Chartreuse","Chocolate","Coral","CornflowerBlue","Cornsilk","Crimson","Cyan","DarkBlue","DarkCyan","DarkGodenRod","DarkGray","DarkGrey","DarkGreen","DarkKhaki","DarkMagenta","DarkOliveGreen","Darkorange","DarkOrchid","DarkRed","DarkSalmon","DarkSeaGreen","DarkSlateBlue","DarkSlateGray","DarkSlateGrey","DarkTurquoise","DarkViolet","DeepPink","DeepSkyBlue","DimGray","DimGrey","DodgerBlue","FireBrick","FloralWhite","ForestGreen","Fuchsia","Gainsboro","GhostWhite","God","GodenRod","Gray","Grey","Green","GreenYellow","HoneyDew","HotPink","IndianRed","Indigo","Ivory","Khaki","Lavender","LavenderBlush","LawnGreen","LemonChiffon","LightBlue","LightCoral","LightCyan","LightGodenRodYellow","LightGray","LightGrey","LightGreen","LightPink","LightSalmon","LightSeaGreen","LightSkyBlue","LightSlateGray","LightSlateGrey","LightSteelBlue","LightYellow","Lime","LimeGreen","Linen","Magenta","Maroon","MediumAquaMarine","MediumBlue","MediumOrchid","MediumPurple","MediumSeaGreen","MediumSlateBlue","MediumSpringGreen","MediumTurquoise","MediumVioletRed","MidnightBlue","MintCream","MistyRose","Moccasin","NavajoWhite","Navy","OdLace","Olive","OliveDrab","Orange","OrangeRed","Orchid","PaleGodenRod","PaleGreen","PaleTurquoise","PaleVioletRed","PapayaWhip","PeachPuff","Peru","Pink","Plum","PowderBlue","Purple","Red","RosyBrown","RoyalBlue","SaddleBrown","Salmon","SandyBrown","SeaGreen","SeaShell","Sienna","Silver","SkyBlue","SlateBlue","SlateGray","SlateGrey","Snow","SpringGreen","SteelBlue","Tan","Teal","Thistle","Tomato","Turquoise","Violet","Wheat","White","WhiteSmoke","Yellow","YellowGreen"};

typedef struct test_thread_args_t {
  long id;
  product_deque_t *deque;
} test_thread_args_t;

void *test_thread(void *args)
{
  test_thread_args_t *test_thread_args = (test_thread_args_t *) args;

  printf("Current thread id: %lu\n", test_thread_args->id);

  product_t p;
  p.color = (char *) COLORS[test_thread_args->id];
  p.id = test_thread_args->id;

  product_deque_push(test_thread_args->deque, &p);

  pthread_exit(0);
}

size_t equal_str(char *str_a, char * str_b)
{
  char *a_ptr = str_a, *b_ptr = str_b;
  while (*a_ptr != '\0')
  {
    if (*a_ptr != *b_ptr)
    {
      return 0;
    }

    ++a_ptr;
    ++b_ptr;
  }

  return 1;
}

void deque_pop_assert(product_deque_t *deque, product_t *expected)
{
  product_t product = product_deque_pop(deque);
  assert(equal_str(expected->color, product.color));
  assert(expected->id == product.id);
}

void run_deque_tests()
{
  unsigned queue_size = 25;

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
    printf("Next product contents: color: %s, id: %lu\n", next_product.color, next_product.id);
  }

  expected_result.color = "";
  expected_result.id = -1;
  deque_pop_assert(&deque, &expected_result);

  product_deque_clear(&deque);
}
