#ifndef _BST_H_
#define _BST_H_

#include <stddef.h>
#include <stdbool.h>

typedef struct node {
  int key;
  struct node *left_child, *right_child;
} node;

typedef struct {
  node *root;
} bst;

// 생성/삭제
bst * create_bst();

// 코어기능 
void bst_insert_node(bst *, int);
void bst_remove_node(bst *, int);
int bst_find_max(bst *);
int bst_find_min(bst *);
bool bst_find_node(bst *, int);

// 유틸
void bst_print(bst *);
#endif  
