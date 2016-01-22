#include "list_tests.h"

// TODO: refactor; currently unbuilt

// Test list implementation.
int_list list;
int_list_init(&list);
  
int_list_add(&list, 0);
  
printf("New list size: %d\n", list.size);
  
if (int_list_remove(&list, 0))
  {
    printf("Remove successful\n");
  }

printf("New list size: %d\n", list.size);

int_list_clear(&list);

int_list_add(&list, 0);
int_list_add(&list, 1);
int_list_add(&list, 2);
int_list_add(&list, 3);

printf("New list size: %d\n", list.size);

if (int_list_remove(&list, 5))
  {
    printf("Remove successful\n");
  }

if (int_list_remove(&list, 0))
  {
    printf("Remove successful\n");
  }

if (int_list_remove(&list, 3))
  {
    printf("Remove successful\n");
  }

printf("New list size: %d\n", list.size);

int_list_clear(&list);
  
printf("New list size: %d\n", list.size);
