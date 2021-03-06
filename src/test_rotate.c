#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

void _right_rotation(rbtree * , node_t *);
void _left_rotation(rbtree * , node_t *);

void _rbtree_print(rbtree * tree, node_t * curr, int tab_count) {
    if(tree->nil == curr){
        return;
    }
    if(tab_count == 1){
        printf("root: %d(%s)\n", curr->key, curr->color == RBTREE_BLACK ? "black" : "red");
    }
    if(curr->left){
        for(int i = 0; i < tab_count * 4; i++){
            printf(" ");
        }
        printf("left: %d(%s)\n", curr->left->key, curr->left->color == RBTREE_BLACK ? "black" : "red");
        _rbtree_print(tree, curr->left, tab_count+1);
    }
    if(curr->right){
        for(int i = 0; i < tab_count * 4; i++){
            printf(" ");
        }
        printf("right: %d(%s)\n", curr->right->key, curr->right->color == RBTREE_BLACK ? "black" : "red");
        _rbtree_print(tree, curr->right, tab_count+1);
    }
}


void rbtree_print(rbtree * tree) {
    if(!tree->root){
        printf("empty tree.\n");
        return;
    }
    _rbtree_print(tree, tree->root, 1);
    printf("\n");
}

rbtree* make_testcase_rbtree(){
    rbtree *t = new_rbtree();
    t->root = (node_t *)calloc(1, sizeof(node_t));
    t->root->key = 10;
    t->root->parent=t->nil;

    node_t *left_node = (node_t *)calloc(1, sizeof(node_t));
    node_t *right_node = (node_t *)calloc(1, sizeof(node_t));

    left_node->key = 5;
    right_node->key = 15;
    left_node->parent = t->root;
    right_node->parent = t->root;
    t->root->left = left_node;
    t->root->right = right_node;

    node_t *left_left_node = (node_t *)calloc(1, sizeof(node_t));
    node_t *left_right_node = (node_t *)calloc(1, sizeof(node_t));
    node_t *right_left_node = (node_t *)calloc(1, sizeof(node_t));
    node_t *right_right_node = (node_t *)calloc(1, sizeof(node_t));
    
    left_left_node->key = 1;
    left_right_node->key = 8;
    right_left_node->key = 12;
    right_right_node->key = 16;
    left_left_node->parent = left_node;
    left_right_node->parent = left_node;
    left_left_node->left = t->nil;
    left_left_node->right = t->nil;
    left_right_node->left = t->nil;
    left_right_node->right = t->nil;
    right_left_node->parent = right_node;
    right_right_node->parent = right_node;
    right_left_node->left = t->nil;
    right_left_node->right = t->nil;
    right_right_node->left = t->nil;
    right_right_node->right = t->nil;
    left_node->left = left_left_node;
    left_node->right = left_right_node;
    right_node->left = right_left_node;
    right_node->right = right_right_node;
    
    return t;
}
void right_rotation_test(){
    printf("right_rotation_test!\n");
    rbtree * t1 = make_testcase_rbtree();
    printf("original tree\n");
    rbtree_print(t1);
    printf("right_rotation(T, 10) -- ?????? ????????? ??????\n");
    _right_rotation(t1, t1->root);
    rbtree_print(t1);
    delete_rbtree(t1);

    rbtree * t2 = make_testcase_rbtree();
    printf("right_rotation(T, 5) -- ??????????????? ????????? ????????? ?????? ????????? ??????\n");
    _right_rotation(t2, t2->root->left);
    rbtree_print(t2);
    delete_rbtree(t2);
    rbtree * t3 = make_testcase_rbtree();
    printf("right_rotation(T, 15) -- ??????????????? ????????? ????????? ????????? ????????? ??????\n");
    _right_rotation(t3, t3->root->right);
    rbtree_print(t3);
    delete_rbtree(t3);
    printf("right rotation ????????? ??????\n");
}

void left_rotation_test(){
    printf("left_rotation_test!\n");
    rbtree *t1 = make_testcase_rbtree();
    printf("original tree\n");
    rbtree_print(t1);
    printf("left_rotation(T, 10) -- ?????? ????????? ??????\n");
    _left_rotation(t1, t1->root);
    rbtree_print(t1);
    delete_rbtree(t1);
    rbtree *t2 = make_testcase_rbtree();
    printf("left_rotation(T, 5) -- ??????????????? ????????? ????????? ?????? ????????? ??????\n");
    _left_rotation(t2, t2->root->left);
    rbtree_print(t2);
    delete_rbtree(t2);
    rbtree * t3 = make_testcase_rbtree();
    printf("left_rotation(T, 15) -- ??????????????? ????????? ????????? ????????? ????????? ??????\n");
    _left_rotation(t3, t3->root->right);
    rbtree_print(t3);
    delete_rbtree(t3);
    printf("left rotation ????????? ??????\n");
}

int main(int argc, char *argv[]) {
    right_rotation_test();
    left_rotation_test();
}