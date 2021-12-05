#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>
linkedlist *generate_linkedlist(void){
    linkedlist *p = (linkedlist *)calloc(1, sizeof(linkedlist));
    p->head = NULL;
    p->tail = NULL;
    return p;
}

void _delete(node *n){
    if(n -> next){
        _delete(n->next);
    }
    printf("%d\n", n->val);
    free(n);
}

void delete_linkedlist(linkedlist *p){
    _delete(p->head);
    free(p);
}

void print_linked_list(linkedlist *p){
    printf("Linked List Data: ");
    node * curr = p->head;
    if (p->root == NULL){
        printf("EMPTY!\n");
        return;
    }

    while (curr->next != NULL) {
        printf("%d -> ", curr->val);
        curr = curr->next;
    }
    printf("%d (End)\n", curr->val);
}

node * insert(linkedlist *p, const int index, const int x){
    // 새로운 노드 생성 
    node * new_node = (node *)calloc(1, sizeof(node));
    new_node->val = x;
    new_node->next = NULL;
    
    // 리스트에 넣기
    if(!p->root) {
        p->root = new_node;
    }
    else{
        if (index == 0){
            node * temp = p->root;
            p->root = new_node;
            new_node->next = temp;    
        }
        else {
            int count = 1;
            node * curr = p->root;
            while(curr->next && count < index){
                curr = curr->next;
                count ++;
            }
            node * temp = curr->next;
            curr->next = new_node;
            new_node->next = temp;
        }
    }
    // p->num_elements += 1;
    return new_node;
}

// int find(linkedlist *p, const int x){
//     if(p->root){
//         node * curr = p->root;
//         while(curr) {
//             if (curr->val == x){
//                 return curr;
//             }
//             curr = curr->next;
//         }
//     }
// }

// node * pop(linkedlist *p, const int);
