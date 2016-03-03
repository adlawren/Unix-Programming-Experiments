#include "list_test.h"

void run_list_tests()
{
  // Test Parameters
  int product_count = 100;
  char *color = "Test Color";

  product_list_t product_list;
  product_list_init(&product_list);

  assert(product_list.size == 0);

  product_t p, expected_product;
  p.color = color;
  p.id = 0;

  product_list_add(&product_list, p);

  assert(product_list.size == 1);

  p = product_list_remove(&product_list, p);

  expected_product.color = color;
  expected_product.id = 0;
  assert(products_equal(&p, &expected_product));

  assert(product_list.size == 0);

  int j;
  for (j = 0; j < product_count; ++j)
  {
    p.color = color;
    p.id = j;

    product_list_add(&product_list, p);
  }

  int k;
  for (k = 0; k < product_count; ++k)
  {
    p.color = color;
    p.id = k;
    p = product_list_remove(&product_list, p);

    expected_product.color = color;
    expected_product.id = k;
    assert(products_equal(&p, &expected_product));

    assert(product_list.size == product_count - (k + 1));
  }

  assert(product_list.size == 0);

  product_list_clear(&product_list);
}
