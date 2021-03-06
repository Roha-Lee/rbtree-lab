#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <stddef.h>

typedef struct node {
  int val;
  struct node *next;
} node;

typedef struct {
  node *head, *tail;
} linkedlist;

linkedlist * generate_linkedlist(void);

void delete_linkedlist(linkedlist *);
void print_linked_list(linkedlist *);
void prepend(linkedlist *, const int);
void append(linkedlist *, const int);
void pop(linkedlist *);
void pop_first(linkedlist *);
node* head(linkedlist *);
node* tail(linkedlist *);
void remove_node(linkedlist *, node *);
#endif  
