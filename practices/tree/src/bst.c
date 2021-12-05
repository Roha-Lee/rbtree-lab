#include "bst.h"
#include <stdlib.h>
#include <stdio.h>

bst * create_bst(void) {
    bst * tree = (bst *)calloc(1, sizeof(bst));
    tree->root = NULL;
    return tree;
}


void bst_insert_node(bst * tree, int key) {
    node * new_node = (node *)calloc(1, sizeof(node));
    new_node->left_child = NULL;
    new_node->right_child = NULL;
    new_node->key = key;
    
    // empty tree
    if(!tree->root){
        tree->root = new_node;
        return;
    }
    node * curr = tree->root;
    while(curr){
        if(key < curr->key){
            if(curr->left_child){
                curr = curr->left_child;
            }
            else{
                curr->left_child = new_node;
                return;
            }
        }
        else if(key > curr->key){
            if(curr->right_child){
                curr = curr->right_child;
            }
            else{
                curr->right_child = new_node;
                return;
            }
        }
        else {
            printf("[Fail] key %d is already exists!\n", key);
            return;
        }
    }
}


int bst_find_max(bst * tree) {
    if(!tree->root){
        printf("Cannot find max value from EMPTY TREE!\n");
        return -1;
    }
    node * curr = tree->root;
    while(curr->right_child){
        curr = curr->right_child;
    }
    return curr->key;
}


int bst_find_min(bst * tree) {
    if(!tree->root){
        printf("Cannot find min value from EMPTY TREE!\n");
        return -1;
    }
    node * curr = tree->root;
    while(curr->left_child){
        curr = curr->left_child;
    }
    return curr->key;
}


bool bst_find_node(bst *tree, int key) {
    if(!tree->root){
        return false;
    }
    node * curr = tree->root;
    while(curr){
        if(key < curr->key){
            if(curr->left_child){
                curr = curr->left_child;
            }
            else{
                return false;
            }
        }
        else if(key > curr->key){
            if(curr->right_child){
                curr = curr->right_child;
            }
            else{
                return false;
            }
        }
        else {
            return true;
        }
    }
    return false;
}


void _bst_print(node * curr, int tab_count) {
    if(tab_count == 1){
        printf("root: %d\n", curr->key);
    }
    if(curr->left_child){
        for(int i = 0; i < tab_count * 4; i++){
            printf(" ");
        }
        printf("left: %d\n", curr->left_child->key);
        _bst_print(curr->left_child, tab_count+1);
    }
    if(curr->right_child){
        for(int i = 0; i < tab_count * 4; i++){
            printf(" ");
        }
        printf("right: %d\n", curr->right_child->key);
        _bst_print(curr->right_child, tab_count+1);
    }
}


void bst_remove_node(bst * tree, int key){
    if(!tree->root){
        printf("[Fail] Cannot found key: %d.\n", key);
        return;
    }
    node * curr = tree->root;
    node * prev = tree->root;
    while(curr){
        if(key < curr->key){
            if(curr->left_child){
                prev = curr;
                curr = curr->left_child;
            }
            else{
                break;
            }
        }
        else if(key > curr->key){
            if(curr->right_child){
                prev = curr;
                curr = curr->right_child;
            }
            else{
                break;
            }
        }
        else {
            // 위치는 찾았고 삭제만 해주면 됨. 
            // 트리의 루트인 경우 루트값 변경 해야함. 
            if(curr == tree->root){
                break;
            }
            // 

            return;
        }
    }
    printf("[Fail] Cannot found key: %d.\n", key);
    return;
}


void bst_print(bst * tree) {
    if(!tree->root){
        printf("empty tree.\n");
        return;
    }
    _bst_print(tree->root, 1);
    printf("\n");
}