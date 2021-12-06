#include "bst.h"
#include <stdlib.h>
#include <stdio.h>

bst * create_bst(void) {
    bst * tree = (bst *)calloc(1, sizeof(bst));
    tree->root = NULL;
    return tree;
}


node* _remove_bst(node *curr){
    if(!curr->left_child && !curr->right_child){
        printf("memory free: node(%d)\n", curr->key);
        return curr;
    }
    if(curr->left_child){
        free(_remove_bst(curr->left_child));
    }
    if(curr->right_child){
        free(_remove_bst(curr->right_child));
    }
    printf("memory free: node(%d)\n", curr->key);
    return curr;   
}


void remove_bst(bst *tree){
    if(tree->root){
        free(_remove_bst(tree->root));
    }
    printf("memory free: tree\n");
    free(tree);
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


void _remove_node(bst *tree, node* prev, node* curr){
    // case 1. 자식이 없는 경우 
    if(!curr->left_child && !curr->right_child){
        if(curr == tree->root){
            tree->root = NULL;
        }

        if(prev->left_child == curr){
            prev->left_child = NULL;
        }
        else if(prev->right_child == curr){
            prev->right_child = NULL;
        }

        free(curr);
        return;
    }
    // case 2. 자식이 오른쪽만 있는 경우 
    else if(!curr->left_child){
        if(curr == tree->root){
            tree->root = curr->right_child;
        }
        else{
            if(prev->right_child == curr){
                prev->right_child = curr->right_child;
            }
            else if(prev->left_child == curr){
                prev->left_child = curr->right_child;
            }
        }
        free(curr);
    }
    // case 2. 자식이 왼쪽만 있는 경우 
    else if(!curr->right_child){
        if(curr == tree->root){
            tree->root = curr->left_child;
        }
        else{
            if(prev->right_child == curr){
                prev->right_child = curr->left_child;
            }
            else if(prev->left_child == curr){
                prev->left_child = curr->left_child;
            }
        }
        free(curr);
    }
    // case 3. 자식이 모두 있는 경우 
    else{
        node * swap_node = curr->right_child;
        node * swap_prev = curr->right_child;
        while(swap_node->left_child){
            swap_prev = swap_node;
            swap_node = swap_node->left_child;
        }
        int temp = swap_node->key;
        swap_node->key = curr->key;
        curr->key = temp;
        // 값을 바꾸었으므로 이제 swap_node를 지우는 문제로 바뀜.
        // 이 경우는 무조건 case1 또는 case2가 됨. 
        if(swap_node == swap_prev){
            if(swap_node == curr->right_child){
                curr->right_child = swap_node->right_child;
            }
            else if (swap_node == curr->left_child){
                curr->left_child = swap_node->right_child;
            }
            free(swap_node);
        }
        else{
            _remove_node(tree, swap_prev, swap_node);
        }
        
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
            _remove_node(tree, prev, curr);
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