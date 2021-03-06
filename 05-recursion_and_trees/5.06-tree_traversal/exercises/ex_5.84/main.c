#include <stdlib.h>
#include <stdio.h> 
#include "item.h"
#include "list.h"
#include "stack.h"

#define MAX 8

/*
                E
              /   \
	     /     \
            D       H
           / \     / \
          B       F
         / \     / \
        A   C       G
       / \ / \     / \

*/

void traverse(link h, void (*visit)(link))
{
  link last_visited = NULL, peek_node;
  
  STACKinit(MAX);

  while (!STACKempty() || h != NULL)
    {
      if (h != NULL)
	{
	  STACKpush(h);
	  h = h->l;
	}
      else
	{
	  peek_node = STACKpeek();
	  if (peek_node->r != NULL && last_visited != peek_node->r)
	    h = peek_node->r;
	  else
	    {
	      (*visit)(STACKpop());
	      last_visited = peek_node;
	    }
	}
    }
}  

void print_node(link node)
{
  print_item(node->item);
}

int main(void) 
{
  link root, left, right;

  root = new_node('E');
  add_left_leaf(root, 'D');
  add_right_leaf(root, 'H');
  left = root->l;
  add_left_leaf(left, 'B');
  left = left->l;
  add_left_leaf(left, 'A');
  add_right_leaf(left, 'C');
  right = root->r;
  add_left_leaf(right, 'F');
  right = right->l;
  add_right_leaf(right, 'G');

  traverse(root, print_node);
  printf("\n");
  return 0;
}
