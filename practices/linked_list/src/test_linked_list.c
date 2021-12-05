#include "linked_list.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    linkedlist *p = generate_linkedlist();
    prepend(p, 1);
    prepend(p, 3);
    append(p, 4);
    append(p, 3);
    append(p, 7);
    print_linked_list(p);
    pop(p);
    pop_first(p);
    print_linked_list(p);
    pop(p);
    pop_first(p);
    print_linked_list(p);
    pop(p);
    pop_first(p);
    print_linked_list(p);
    pop(p);
    pop_first(p);
    print_linked_list(p);
    
    delete_linkedlist(p);
}