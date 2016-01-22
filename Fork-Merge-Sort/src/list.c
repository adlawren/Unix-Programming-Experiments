#include "list.h"

void int_list_init(int_list *list)
{
  list->head = 0;
  list->tail = 0;
  list->size = 0;
}

void int_list_add(int_list *list, int to_add)
{
  int_node *new_node = (int_node *) malloc(sizeof(int_node));
  new_node->next = 0;
  new_node->data = to_add;

  if (list->head == 0)
  {
    list->head = new_node;
  }
  else if (list->tail == 0)
  {
    list->tail = new_node;
    list->head->next = list->tail;
  }
  else
  {
    list->tail->next = new_node;
    list->tail = new_node;
  }

  ++list->size;
}

unsigned int_list_remove(int_list *list, int to_remove)
{
  int_node *prev_node = 0, *next_node = list->head;
  while (next_node)
  {
    if (next_node->data == to_remove)
    {
      if (prev_node)
      {
	prev_node->next = next_node->next;
      }
      else
      {
	list->head = next_node->next;
      }
      
      free(next_node);
      --list->size;

      return 1;
    }
    
    prev_node = next_node;
    next_node = next_node->next;
  }

  return 0;
}

void int_list_clear(int_list *list)
{
  int_node *prev_node = 0, *next_node = list->head;
  while (next_node)
  {
    prev_node = next_node;
    next_node = next_node->next;

    free(prev_node);
  }

  list->size = 0;
}
