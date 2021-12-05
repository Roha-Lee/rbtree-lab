#include "bst.h"
#include <stdio.h>
void test_1() {
    // 1. 트리 생성 & 노드 삽입 & 트리 출력 테스트
    // 빈 트리 출력 테스트 
    bst *tree = create_bst();
    bst_print(tree);
    // 트리 생성 및 출력 테스트 
    int tree_elems[10] = {3, 5, 1, 2, 0, 4, 6, 9, 7, 10};
    for(int i = 0; i < 10; i++){
        bst_insert_node(tree, tree_elems[i]);
    }
    bst_print(tree);
}


void test_2() {
    // 2. 트리 최대값 & 최소값 & 특정값 찾기 테스트 
    bst *tree = create_bst();
    int tree_elems[10] = {3, 5, 1, 2, 0, 4, 6, 9, 7, 10};
    for(int i = 0; i < 10; i++){
        bst_insert_node(tree, tree_elems[i]);
    }
    bst_print(tree);
    printf("max key of tree: %d\n", bst_find_max(tree));
    printf("min key of tree: %d\n", bst_find_min(tree));
    printf("result of find key 8 : %s\n", bst_find_node(tree, 8) ? "true" : "false");
    printf("result of find key 10 : %s\n", bst_find_node(tree, 10) ? "true" : "false");
    
    // 빈 트리에서 테스트
    bst *tree2 = create_bst();
    bst_print(tree2);
    printf("max key of tree: %d\n", bst_find_max(tree2));
    printf("min key of tree: %d\n", bst_find_min(tree2));
    printf("result of find key 8 : %s\n", bst_find_node(tree2, 8) ? "true" : "false");
    printf("result of find key 10 : %s\n", bst_find_node(tree2, 10) ? "true" : "false");
}


void test_3(){
    // 3. 노드 삭제 테스트 
}

int main(int argc, char *argv[]) {
    // 1. 트리 생성 & 노드 삽입 & 트리 출력 테스트
    test_1();

    // 2. 트리 최대값 & 최소값 & 특정값 찾기 테스트 
    test_2();
     
    // 3. 노드 삭제 테스트 
    test_3();
    return 0;
}