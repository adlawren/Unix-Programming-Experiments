#include "list.h"

void product_list_init(product_list_t *list)
{
  list->head = 0;
  list->tail = 0;
  list->size = 0;
}

void product_list_add(product_list_t *list, product_t to_add)
{
  product_node_t *new_node = (product_node_t *) malloc(sizeof(product_node_t));
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

product_t product_list_remove(product_list_t *list, product_t to_remove)
{
  product_t result;
  result.color = "";
  result.id = -1;

  product_node_t *prev_node = 0, *next_node = list->head;
  while (next_node)
  {
    if (next_node->data.id == to_remove.id)
    {
      result = next_node->data;

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

      break;
    }
    
    prev_node = next_node;
    next_node = next_node->next;
  }

  return result;
}

void product_list_clear(product_list_t *list)
{
  product_node_t *prev_node = 0, *next_node = list->head;
  while (next_node)
  {
    prev_node = next_node;
    next_node = next_node->next;

    free(prev_node);
  }

  list->size = 0;
}
