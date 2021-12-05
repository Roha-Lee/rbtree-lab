#include "stack.h"
#include "linked_list.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    stack* st = create_stack();
    stack_push(st, 1);
    stack_push(st, 3);
    stack_push(st, 4);
    stack_push(st, 5);
    stack_print(st);
    stack_pop(st);
    stack_pop(st);
    stack_push(st, 6);
    printf("stack's last element: %d\n", stack_top(st)->val);
    stack_push(st, 7);
    stack_print(st);
    stack_pop(st);
    printf("stack's last element: %d\n", stack_top(st)->val);
    stack_pop(st);
    stack_pop(st);
    stack_pop(st);
    stack_print(st);
    stack_pop(st);
    stack_pop(st);
    return 0;
}