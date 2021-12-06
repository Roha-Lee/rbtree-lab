#include "rbtree.h"

#include <stdlib.h>


void right_rotation(rbtree * tree, node_t * x){
    node_t * y = x->left;
    x->left = y->right;
    if(y->right != tree->nil){
        y->right->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == tree->nil){
        tree->root = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
}


void left_rotation(rbtree * tree, node_t * x){
    node_t * y = x->right;
    x->right = y->left;
    if(y->left != tree->nil){
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == tree->nil){
        tree->root = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}


rbtree *new_rbtree(void) {
    rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
    // TODO: initialize struct if needed
    p->root = NULL;
    p->nil = (node_t *)calloc(1, sizeof(node_t));
    p->nil->color = RBTREE_BLACK;
    return p;
}

void delete_rbtree(rbtree *t) {
    // TODO: reclaim the tree nodes's memory
    free(t->nil);
    free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
    // TODO: implement insert
    return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
    // TODO: implement find
    return t->root;
}

node_t *rbtree_min(const rbtree *t) {
    // TODO: implement find
    return t->root;
}

node_t *rbtree_max(const rbtree *t) {
    // TODO: implement find
    return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
    // TODO: implement erase
    return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
    // TODO: implement to_array
    return 0;
}
