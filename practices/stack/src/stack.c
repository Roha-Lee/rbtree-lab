#include "stack.h"
#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// 스택 생성, 삭제 
stack * create_stack(void){
    stack * st = (stack *)calloc(1, sizeof(stack));
    st->data = (linkedlist *)calloc(1, sizeof(linkedlist));
    return st;
}

void delete_stack(stack * st){
    while (!stack_is_empty(st)){
        stack_pop(st);
    }
    free(st);
}

// 스택 코어 기능
bool stack_is_empty(stack * st){
    if (!st->data->head){
        return true;
    }
    return false;
}

void stack_push(stack * st, int x){
    append(st->data, x);
}

void stack_pop(stack *st){
    pop(st->data);
}

node* stack_top(stack *st){
    return st->data->tail;
}
// 유틸
void stack_print(stack *st){
    node * curr = st->data->head;
    printf("stack: ");
    if (!curr) {
        printf("EMPTY!\n");    
        return;
    }

    while(curr->next){
        printf("%d -> ", curr->val);
        curr = curr->next;
    }
    printf("%d (end)\n", curr->val);
}
