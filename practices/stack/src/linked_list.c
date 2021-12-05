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
    // printf("%d 노드 삭제 완료\n", n->val);
    free(n);
}

void delete_linkedlist(linkedlist *p){
    if(p->head){
        _delete(p->head);
    }
    // printf("연결 리스트 삭제 완료\n");
    free(p);
}

void print_linked_list(linkedlist *p){
    printf("Linked List Data: ");
    node * curr = p->head;
    if (p->head == NULL){
        printf("EMPTY!\n");
        return;
    }

    while (curr->next != NULL) {
        printf("%d -> ", curr->val);
        curr = curr->next;
    }
    printf("%d (End)\n", curr->val);
}
void prepend(linkedlist *p, const int x){
    node * new_node = (node *)calloc(1, sizeof(node));
    new_node->val = x;
    new_node->next = p->head;
    if(!p->head){
        p->tail = new_node;
    }
    p->head = new_node;
}

void append(linkedlist * p, const int x){
    node * new_node = (node *)calloc(1, sizeof(node));
    new_node->val = x;
    new_node->next = NULL;
    if(!(p->tail)){
        p->head = new_node;
        p->tail = new_node;
    }
    else{
        p->tail->next = new_node;
        p->tail = new_node;
    }
}

void pop(linkedlist *p){
    if(!p->tail){
        return;
    }
    remove_node(p, p->tail);
}

void pop_first(linkedlist *p){
    if(!p->head){
        return;
    }
    remove_node(p, p->head);
}

node* head(linkedlist *p){
    return p->head;
}

node* tail(linkedlist *p){
    return p->tail;
}

void remove_node(linkedlist *p, node * rm_node){
    if(!p || !p->head){
        return;
    }
    if(p->head == rm_node){
        if(p->tail == rm_node){
            p->head = NULL;
            p->tail = NULL;

        }
        else{
            p->head = p->head->next;
        }
        free(rm_node);
        return;
    }

    node * curr = p->head;
    while(curr->next && curr->next != rm_node){        
        curr = curr->next;
    }
    // 지우려는 노드 없는 경우 
    if(curr == p->tail){
        return;
    }
    node * next_node = curr->next->next;
    curr->next = next_node;
    if (!next_node) {
        p->tail = curr;
    }
    free(rm_node);
}
