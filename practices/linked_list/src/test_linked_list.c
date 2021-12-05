#include "linked_list.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    linkedlist *p = generate_linkedlist();
    insert(p, 0, 10);
    insert(p, 1, 11);
    print_linked_list(p);
    // printf("num_elements: %d\n", count_elements(p));
    
    insert(p, 0, 9);
    insert(p, 1, 8);
    print_linked_list(p);
    // printf("num_elements: %d\n", count_elements(p));
    // node * node1 = find(p, 9);
    // node * node2 = find(p, 12);
    // printf("%s", node1);
    // printf("%s", node2);
    
    delete_linkedlist(p);
}