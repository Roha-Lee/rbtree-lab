#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
    rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
    // TODO: initialize struct if needed
    p->nil = (node_t *)calloc(1, sizeof(node_t));
    p->nil->color = RBTREE_BLACK;
    p->root = p->nil;
    return p;
}


node_t * _delete(rbtree *t, node_t * curr){
    if(curr->left == t->nil && curr->right == t->nil){
        return curr;
    }
    if(curr->left != t->nil){
        free(_delete(t, curr->left));
    }
    if(curr->right != t->nil){
        free(_delete(t, curr->right));
    }
    return curr;
}


void delete_rbtree(rbtree *t) {
    // TODO: reclaim the tree nodes's memory
    if(t->root != t->nil){
        free(_delete(t, t->root));
    }
    free(t->nil);
    free(t);
}


void _right_rotation(rbtree * tree, node_t * x){
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


void _left_rotation(rbtree * tree, node_t * x){
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


void _rb_insert_fixup(rbtree *t, node_t *curr){
    while(curr->parent->color == RBTREE_RED){
        if(curr->parent == curr->parent->parent->left){
            node_t * uncle = curr->parent->parent->right;
            // case 1
            if(uncle->color == RBTREE_RED){
                curr->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                curr->parent->parent->color = RBTREE_RED;
                curr = curr->parent->parent;
            }
            else {
                // case 2
                if(curr == curr->parent->right){
                    curr = curr->parent;
                    _left_rotation(t, curr);
                }
                // case 3
                curr->parent->color = RBTREE_BLACK;
                curr->parent->parent->color = RBTREE_RED;
                _right_rotation(t, curr->parent->parent);
            }
        }
        else{  
            node_t * uncle = curr->parent->parent->left;
            // case 1
            if(uncle->color == RBTREE_RED){
                curr->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                curr->parent->parent->color = RBTREE_RED;
                curr = curr->parent->parent;
            }
            else {
                if(curr == curr->parent->left){
                    curr = curr->parent;
                    _right_rotation(t, curr);
                }
                curr->parent->color = RBTREE_BLACK;
                curr->parent->parent->color = RBTREE_RED;
                _left_rotation(t, curr->parent->parent);
            }
        }
    }
}


node_t *rbtree_insert(rbtree *t, const key_t key) {
    // TODO: implement insert
    
    // make new_node
    node_t * new_node = (node_t *)calloc(1, sizeof(node_t));
    node_t * y = t->nil;
    node_t * x = t->root;
    while(x != t->nil){
        y = x;
        if(key < x->key){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }

    new_node->parent = y;
    if(y == t->nil){
        t->root = new_node;
    }
    else if(key < y->key){
        y->left = new_node;
    }
    else {
        y->right = new_node;
    }

    new_node->key = key;
    new_node->color = RBTREE_RED;
    new_node->left = new_node->right = t->nil;

    _rb_insert_fixup(t, new_node);
    t->root->color = RBTREE_BLACK;
    return new_node;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
    // TODO: implement find
    if(t->root == t->nil){
        return NULL;
    }
    node_t * curr = t->root;
    while(curr != t->nil){
        if(key < curr->key){
            curr = curr->left;
        }
        else if(key > curr->key){
            curr = curr->right;
        }   
        else {
            return curr;
        }
    }
    return NULL;
}

node_t *rbtree_min(const rbtree *t) {
    // TODO: implement find
    if(t->root == t->nil){
        return NULL;
    }
    node_t * curr = t->root;
    while(curr->left != t->nil){
        curr = curr->left;
    }
    return curr;
}

node_t *rbtree_max(const rbtree *t) {
    // TODO: implement find
    if(t->root == t->nil){
        return NULL;
    }
    node_t * curr = t->root;
    while(curr->right != t->nil){
        curr = curr->right;
    }
    return curr;
}


void _transplant(rbtree *t, node_t *u, node_t *v){
    if (u->parent == t->nil) {
        t->root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}


void _delete_fixup(rbtree * t, node_t *x){
    while (x!=t->root && x->color == RBTREE_BLACK){
        if (x == x->parent->left){
            node_t * w = x->parent->right;
            if (w->color == RBTREE_RED){
                w->color = RBTREE_BLACK;
                x->parent->color = RBTREE_RED;
                _left_rotation(t, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
                w->color = RBTREE_RED;
                x = x->parent;
            }
            else {
                if (w->right->color == RBTREE_BLACK){
                    w->left->color = RBTREE_BLACK;
                    w->color = RBTREE_RED;
                    _right_rotation(t, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = RBTREE_BLACK;
                w->right->color = RBTREE_BLACK;
                _left_rotation(t, x->parent);
                x = t->root;
            }
        }
        else {
            node_t * w = x->parent->left;
            if (w->color == RBTREE_RED){
                w->color = RBTREE_BLACK;
                x->parent->color = RBTREE_RED;
                _right_rotation(t, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK) {
                w->color = RBTREE_RED;
                x = x->parent;
            }
            else{
                if (w->left->color == RBTREE_BLACK){
                    w->right->color = RBTREE_BLACK;
                    w->color = RBTREE_RED;
                    _left_rotation(t, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = RBTREE_BLACK;
                w->left->color = RBTREE_BLACK;
                _right_rotation(t, x->parent);
                x = t->root;
            }
        }
    }
    x->color = RBTREE_BLACK;
}


int rbtree_erase(rbtree *t, node_t *p) {
    // TODO: implement erase
    node_t * y = p;
    node_t * x;
    color_t y_original = y->color;
    if(p->left == t->nil) {
        x = p->right;
        _transplant(t, p, p->right);
    }
    else if(p->right == t->nil){
        x = p->left;
        _transplant(t, p, p->left);
    }
    else {
        y = p->right;
        while(y->left != t->nil){
            y = y->left;
        }
        y_original = y->color;
        x = y->right;
        if(y->parent != p){
            y->right = p->left;
            y->right->parent = y;
        }
        _transplant(t, p, y);
        y->left = p->left;
        y->left->parent = y;
        y->color = p->color;
    }
    if (y_original == RBTREE_BLACK){
        _delete_fixup(t, x);
    }
    free(p);
    return 0;
}


void _rbtree_to_array(const rbtree *t, node_t * curr, key_t *arr, size_t *pcnt, const size_t n){
    if(curr == t->nil){
        return;
    }
    _rbtree_to_array(t, curr->left, arr, pcnt, n);
    if(*pcnt < n){
        arr[(*pcnt)++] = curr->key;
    }else{
        return;
    }
    _rbtree_to_array(t, curr->right, arr, pcnt, n);
}


int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
    // TODO: implement to_array
    if(t->root == t->nil){
        return 0;
    }
    else{
        size_t cnt = 0;
        _rbtree_to_array(t, t->root, arr, &cnt, n);
    }
    return 0;
}
