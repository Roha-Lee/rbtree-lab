#ifndef _STACK_H_
#define _STACK_H_
#include "linked_list.h"
#include <stddef.h>
#include <stdbool.h>

typedef struct stack{
  linkedlist * data;
} stack;

// 스택 생성, 삭제 
stack * create_stack();
void delete_stack(stack *);
// 스택 코어 기능
bool stack_is_empty(stack *);
void stack_push(stack *, int);
void stack_pop(stack *);
node* stack_top(stack *);
// 유틸
void stack_print(stack *st);

#endif  
