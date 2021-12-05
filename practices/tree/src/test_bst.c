#include "bst.h"
#include <stdio.h>
void test_1() {
    // 1. 트리 생성 & 노드 삽입 & 트리 출력 테스트
    // 빈 트리 출력 테스트 
    printf("running test_1\n");
    bst *tree = create_bst();
    bst_print(tree);
    // 트리 생성 및 출력 테스트 
    int tree_elems[10] = {3, 5, 1, 2, 0, 4, 6, 9, 7, 10};
    for(int i = 0; i < 10; i++){
        bst_insert_node(tree, tree_elems[i]);
    }
    bst_print(tree);
    remove_bst(tree);
}


void test_2() {
    // 2. 트리 최대값 & 최소값 & 특정값 찾기 테스트 
    printf("running test_2\n");
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
    remove_bst(tree);

    // 빈 트리에서 테스트
    bst *tree2 = create_bst();
    bst_print(tree2);
    printf("max key of tree: %d\n", bst_find_max(tree2));
    printf("min key of tree: %d\n", bst_find_min(tree2));
    printf("result of find key 8 : %s\n", bst_find_node(tree2, 8) ? "true" : "false");
    printf("result of find key 10 : %s\n", bst_find_node(tree2, 10) ? "true" : "false");
    remove_bst(tree2);
}


void test_3(){
    // 3. 노드 삭제 테스트 
    printf("running test_3\n");

    // case 1. 자식이 없는 노드 삭제 테스트 
    printf("[case 1]\n");
    bst *tree = create_bst();
    int tree_elems[10] = {3, 5, 1, 2, 0, 4, 6, 9, 7, 10};
    for(int i = 0; i < 10; i++){
        bst_insert_node(tree, tree_elems[i]);
    }
    bst_print(tree);
    bst_remove_node(tree, 10);
    bst_remove_node(tree, 0);
    bst_remove_node(tree, 2);
    bst_remove_node(tree, 7);
    bst_remove_node(tree, 9);
    bst_print(tree);
    remove_bst(tree);

    bst * tree1 = create_bst();
    bst_insert_node(tree1, 10);
    bst_insert_node(tree1, 20);
    bst_insert_node(tree1, 1);
    bst_print(tree1);
    bst_remove_node(tree1, 1);
    bst_print(tree1);
    bst_remove_node(tree1, 20);
    bst_print(tree1);
    bst_remove_node(tree1, 10);
    bst_print(tree1);
    remove_bst(tree1);

    // case 1-1. 트리의 유일한 노드 삭제 테스트 
    printf("[case 1-1]\n");
    bst *tree2 = create_bst();
    bst_insert_node(tree2, 10);
    bst_print(tree2);
    bst_remove_node(tree2, 10);
    bst_remove_node(tree2, 10);
    bst_print(tree2);
    remove_bst(tree2);

    // case 2. 왼쪽 노드만 있는 경우 & 루트 x
    printf("[case 2]\n");
    bst *tree3 = create_bst();
    bst_insert_node(tree3, 10);
    bst_insert_node(tree3, 5);
    bst_insert_node(tree3, 1);
    bst_insert_node(tree3, 3);
    bst_insert_node(tree3, 2);
    bst_insert_node(tree3, 4);
    bst_print(tree3);
    bst_remove_node(tree3, 5);
    bst_print(tree3);
    // case 2. 왼쪽 노드만 있는 경우 & 루트 o
    bst_remove_node(tree3, 10);
    bst_print(tree3);
    remove_bst(tree3);

    // case 2. 오른쪽 노드만 있는 경우 & 루트 x
    bst *tree4 = create_bst();
    bst_insert_node(tree4, 1);
    bst_insert_node(tree4, 5);
    bst_insert_node(tree4, 10);
    bst_insert_node(tree4, 8);
    bst_insert_node(tree4, 7);
    bst_insert_node(tree4, 9);
    bst_print(tree4);
    bst_remove_node(tree4, 5);
    bst_print(tree4);
    // case 2. 오른쪽 노드만 있는 경우 & 루트 o
    bst_remove_node(tree4, 1);
    bst_print(tree4);
    remove_bst(tree4);

    // case 3. 두 자식 모두 있는 경우 
    // 지우려는 노드 우측 자식의 좌측 자식이 없는 경우
    bst *tree5 = create_bst();
    bst_insert_node(tree5, 10);
    bst_insert_node(tree5, 20);
    bst_insert_node(tree5, 1);
    bst_print(tree5);
    bst_remove_node(tree5, 10);
    bst_print(tree5);
    remove_bst(tree5);

    // 지우려는 노드 우측 자식의 좌측 자식이 있는 경우
    bst *tree6 = create_bst();
    bst_insert_node(tree6, 10);
    bst_insert_node(tree6, 20);
    bst_insert_node(tree6, 1);
    bst_insert_node(tree6, 15);
    bst_insert_node(tree6, 30);
    bst_insert_node(tree6, 17);
    bst_print(tree6);
    bst_remove_node(tree6, 10);
    bst_print(tree6);
    remove_bst(tree6);

    // 지우려는 노드 우측 자식의 좌측 자식이 없는 경우
    bst *tree7 = create_bst();
    bst_insert_node(tree7, 10);
    bst_insert_node(tree7, 20);
    bst_insert_node(tree7, 1);
    bst_insert_node(tree7, 30);
    bst_print(tree7);
    bst_remove_node(tree7, 10);
    bst_print(tree7);
    remove_bst(tree7);
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