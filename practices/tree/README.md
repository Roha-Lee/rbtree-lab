# C 언어로 이진 탐색 트리 구현해보기 :christmas_tree:
- **연습 3)** 이진 탐색 트리 C언어로 구현해보기 

# 이진 탐색트리 특징 :speech_balloon:
1. 노드의 left subtree에는 노드보다 작은 키만 있다. 
2. 노드의 right subtree에는 노드보다 큰 키만 있다. 
3. left, right subtree 모두 이진 탐색 트리이다. 
4. 중복된 키를 허용하지 않는다.  
# 구현 :fire:
## 구조체 정의 
### Tree
- `Node * root` : 트리의 루트를 가리키고 있는 포인터 
### Node
- `Node * leftchild` : 노드의 왼쪽 자식을 가리키는 포인터 
- `Node * rightchild` : 노드의 오른쪽 자식을 가리키는 포인터 
- `int key` : 노드의 키값

## 기능 체크리스트 ✅
### 이진 탐색 트리 생성/삭제 
- [x] `binary_search_tree * create_bst(void)`
    - 트리 생성하기
        - bst 동적 메모리 할당 및 반환
- [ ] 트리 삭제하기(메모리 해제):
### 코어 기능 
- [x] `void bst_insert_node(bst * tree, int key)`
    - 노드 삽입하기
        1. Tree가 비어있는 경우 
            - `key`값을 갖는 노드 생성 후 root가 가리키도록 한다. 
        2. Tree가 비어있지 않은 경우 
            2-1. `key`값이 현재 노드보다 작은 경우는 왼쪽 서브트리로 이동, 만약 현재 노드의 왼쪽 자식이 없다면 새 노드를 왼쪽 자식으로 만들어줌 
            2-2. `key`값이 현재 노드보다 큰 경우에는 오른쪽 서브트리로 이동, 만약 현재 노드의 오른쪽 자식이 없다면 새 노드를 오른쪽 자식으로 만들어줌
            2-3. `key`와 `node->key`가 같은 경우는 이진 탐색트리 특징 4번 **"중복되는 키를 허용하지 않는다"** 에 위배되므로 에러 메시지 출력
- [ ] 노드 삭제하기 
- [x] `int bst_find_max(bst * tree)`
    - 트리의 최대값 찾기 
        - 트리의 오른쪽 자식으로만 이동, 가장 우측의 키 값을 반환
- [x] `int bst_find_min(bst * tree)`
    - 트리의 최대값 찾기 
        - 트리의 왼쪽 자식으로만 이동, 가장 좌측의 키 값을 반환
- [x] `bool bst_find_node(bst *, int key)`
    - 노드 검색하기 
        - 노드 삽입할때의 로직과 동일하게 수행
        - Tree가 비어있는 경우 `false`
        - Tree가 비어있지 않은 경우 
            - `key`값이 현재 노드보다 작은 경우는 왼쪽 서브트리로 이동
            - `key`값이 현재 노드보다 큰 경우는 오른쪽 서브트리로 이동
            - `key`값과 현재 노드의 값이 같은 경우는 `true` 반환 
            - 더 이상 이동할 수 없으면 `false` 반환
### 유틸
- [x] `void bst_print(bst * tree)`
    - 트리 출력하기 
        - tree의 깊이가 깊어질 수록 tab의 수를 늘려가면서 left child와 right child의 값을 출력.
        - `_bst_print(node * curr, int tab_count)`라는 보조 함수를 정의하여 다음과 같이 출력 결과가 나오도록 재귀적으로 구현. 
        
        - **출력 결과 예시**
        ```
        root: 3
            left: 2
                left: 1
            right: 5
                left: 4
                right: 6
        ```
# 기능 테스트 📜
- [x] 트리 생성 & 노드 삽입 & 트리 출력 테스트 
    ```c
    // 빈 트리 출력 테스트 
    bst *tree = create_bst();
    bst_print(tree);
    // 트리 생성 및 출력 테스트 
    int tree_elems[10] = {3, 5, 1, 2, 0, 4, 6, 9, 7, 10};
    for(int i = 0; i < 10; i++){
        bst_insert_node(tree, tree_elems[i]);
    }
    bst_print(tree);
    ```
- [x] 트리 최대값 & 최소값 & 특정값 찾기 테스트 
    ```c
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
    ```
- [ ] 노드 삭제 테스트