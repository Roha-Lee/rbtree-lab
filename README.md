# Red Black Tree 개발 노트 :book:
:link:[과제 설명으로 바로가기](#red-black-tree-구현)

![RB tree](https://upload.wikimedia.org/wikipedia/commons/thumb/6/66/Red-black_tree_example.svg/500px-Red-black_tree_example.svg.png)

## Red Black tree 개요
- 이진 검색트리의 일종
- 각 노드당 색깔을 나타내는 한비트의 추가 메모리공간을 갖음 
- 근사적으로 균형을 이룬 트리가 된다.
  - :bulb: 균형을 이룬 트리란 한쪽으로 치우치지 않는 트리를 말한다. 
- 트리의 각 노드는 color, key, left, right, p의 필드를 갖는다. 
- 한 노드의 자식 또는 부모가 존재하지 않으면 그에 대응되는 노드의 포인터 필드는 NIL값으로 채워진다.
- NIL은 리프노드들에 대한 포인터들이고 키를 가지는 정상적인 노드들은 트리의 내부 노드로 간주된다. 

## Red Black tree 특징
1. 모든 노드는 적색이거나 흑색이다 
2. 루트는 흑색이다
3. 모든 리프(NIL)은 흑색이다
4. 노드가 적색이면 그 노드의 자식은 모두 흑색이다
5. 각 노드로부터 그 노드의 자손인 리프로 가는 경로들은 모두 같은 수의 흑색 노드를 포함한다

## 구현 하기 전 공부 
### 개요 
- `T.nil`은 리프노드를 내부 노드와 동일하게 다루기 위해 사용 
- `black height(x)`란 한 노드 x에서 리프까지의 경로에 있는 모든 흑색 노드의 개수
### rotation
- insert와 delete를 위해 rotation을 사용하며 rotation은 이진 탐색트리의 특성을 보존하는 연산이다. 
### insertion 
- 삽입할 노드는 이진 탐색 트리와 유사하게 위치를 찾아 빨강으로 칠한후 삽입한다. 
- 삽입한 후에 RB tree에 위배된 부분이 있다면 RB_INSERT_FIXUP을 호출해서 RB tree의 특성을 맞춰준다. 
### insertion fixup
- 반복문을 통해 위로 올라가면서 RB tree에 위배된 부분을 수정해 나간다. 
- while 반복 시작 시 유지되는 것
  a. `new_node`는 빨강
  b. `new_node->parent`가 루트인 경우 `new_node->parent`는 검정이다. 
    - 따라서 `new_node->parent`가 빨강인 경우 항상 `new_node->parent->parent`가 존재한다. 
  c. RB tree의 특징을 위반하는 경우 특징2 또는 특징 4 둘 중 하나만을 위반한다. 또한 특징 4를 위반하는 경우는 `new_node`와 `new_node->parent`가 모두 빨강인 경우이다.
- 6가지 경우로 나누어서 구현한다. 
  - 3가지 경우는 `new_node->parent`가 `new_node->parent->parent`의 왼쪽노드인 경우, 나머지 3가지 경우는 `new_node->parent`가 `new_node->parent->parent`의 오른쪽 노드인 경우이다.
  - 경우 1) `new_node`의 삼촌(부모의 부모의 다른 자식)이 빨강인 경우
    - 해법) 
    - `new_node->parent`와 그 삼촌을 검정으로 칠한다. 
    - `new_node->parent->parent`를 빨강으로 칠한다. 
    - `new_node = new_node->parent->parent` 로 두고 다음 반복을 수행한다.
  - 경우 2) new_node의 삼촌 y가 검정이고 new_node가 부모의 오른쪽 자식인 경우 
  - 경우 3) new_node의 삼촌 y가 검정이고 new_node가 부모의 왼쪽 자식인 경우 
    - 해법) 
    - 경우 2에서 `new_node = new_node->parent;`를 한 후 `left_rotate(t, new_node);`를 하면 경우 3으로 변환이 가능하다. 
    - 경우 3의 경우 `new_node->parent`를 검정으로, `new_node->parent->parent`를 빨강으로 칠한 다음 `right_rotate(t, new_node->parent->parent);`를 수행하면 된다.
    - TODO) 그림 있으면 좋을거 같다. 


## 구현 
### 구조체 정의 
#### node_t
- color: 노드의 색 정보(RBTREE_RED / RBTREE_BLACK)
- key: key값
- parent, left, right: 부모, 왼쪽 자식, 오른쪽 자식을 가리키는 포인터 

#### rbtree
- root: 트리의 루트노드를 가리키는 포인터 
- nil: 리프노드와 루트노드를 표현하기 위한 보조 값

### 생성/삭제 
- [x] `rbtree *new_rbtree(void)` 
  - RB트리 생성 
  - rbtree 메모리 할당 
  - rbtree 멤버 초기화 
    - root를 NULL로 만들어주기 
    - nil에 메모리 할당한 후 BLACK으로 설정, 나머지는 NULL
- [x] `void delete_rbtree(rbtree *t)` 
  - RB트리 생성에 사용했던 메모리 회수
  - `node_t * _delete(node_t * curr)` 보조 함수를 이용하여 재귀적으로 노드 삭제 
    - 리프노드부터 순차적으로 삭제(왼쪽 오른쪽 자식이 모두 `Tree.nil`인 경우 노드 반환)
    - 재귀적으로 다음 노드를 호출하면서 `free(_delete(curr->left));`, `free(_delete(curr->right));`와 같이 다음 갈 곳이 있는 노드를 방문하여 먼저 삭제 하고 이후에 반환된 노드를 해제한다. 
### 코어 기능 
- [x] `node_t *rbtree_insert(rbtree *t, const key_t key)`
  - insert를 구현하기 위해 아래와 같은 3가지 보조함수 `_right_rotation`, `_left_rotation`, `_rb_insert_fixup`을 구현하였다. 
  - 이진 탐색 트리와 동일한 로직으로 key값을 노드와 비교하면서 삽입될 위치를 찾는다. 
  - 삽입될 위치에 노드를 넣어준다.(빨강으로 넣어준다.)
  - `_rb_insert_fixup`을 통해 RB 트리 규칙을 지키도록 노드들을 조정해준다. 
  - [x] `void _right_rotation(rbtree * tree, node_t * x)`
  - [x] `void _left_rotation(rbtree * tree, node_t * x)`
    - 트리 회전 기능 구현 
    - CLRS를 참고하여 구현하였다. 
    - 책의 가정과 동일하게 회전하려는 노드의 오른쪽 자식이 있다고 가정하였고 루트의 부모는 `Tree.nil`이라고 가정하였다. 
    - 세 가지 경우로 나누어서 구현하였고 두 노드의 parent, left, right와 부모 자식과의 관계를 순서에 맞게 잘 연결해주어 구현하였다. 
      - 회전하려는 노드가 루트인 경우
      - 회전하려는 노드가 부모의 왼쪽 자식인 경우 
      - 회전하려는 노드가 부모의 오른쪽 자식인 경우
  - [x] `void _rb_insert_fixup(rbtree *t, node_t *curr)`
    - 삽입할 노드를 무조건 빨강으로 만들어서 넣어주기 때문에 RB 트리의 규칙을 깰 수 있는 가능성이 있다. 이를 바로잡아주기 위한 보조 함수 
    - [CLRS를 참고한 구현 방식 링크](#insertion-fixup)
    
## 테스트 
- [x] 트리 회전 테스트 통과
  - 회전관련한 테스트 케이스는 주어지지 않아서 따로 구현하였다. 
  - `test_rotate.c`파일에 테스트 케이스와 트리 출력 코드를 작성한 후 회전을 제대로 구현했는지 테스트 
  - 확인한 케이스는 위의 회전 구현에서 고려한 세가지 케이스이고 각각의 경우에 대하여 `left_rotation`, `right_rotation`을 테스트 하여 결과 출력하였다. 
- [x] 생성 삭제 테스트 통과 
  - `test-rbtree.c`파일의 `test_init`부분 통과 
- [x] 원소 1개 삽입하는 테스트 통과 
  - `test-rbtree.c`파일의 `test_insert_single`부분 통과 

# Red-Black Tree 구현

Balanced search tree로 많이 쓰이는 Red-black tree (이하 RB tree)를 C 언어로 구현해 보는 과제입니다.
구현하는 추상 자료형(abstract data type)은 ordered set, multiset 입니다.

## 구현 범위
다음 기능들을 수행할 수 있도록 RB tree를 구현합니다.

- tree = `new_tree()`: RB tree 구조체 생성 - 구현되어 있음
- `delete_tree(tree)`: RB tree 구조체가 차지했던 메모리 반환

- `tree_insert(tree, key)`: key 추가
- ptr = `tree_find(tree, key)`
    - RB tree내에 해당 key가 있는지 탐색하여 있으면 해당 node pointer 반환
    - 없으면 NIL 반환
- `tree_erase(tree, ptr)`: ptr로 지정된 node 삭제 및 메모리 반환
- ptr = `tree_min(tree)`: RB tree 중 최소 값을 가진 node pointer 반환
- ptr = `tree_max(tree)`: 최대값을 가진 node pointer 반환

- `tree_to_array(tree, array, n)`
  - RB tree의 내용을 *key 순서대로* 주어진 array로 변환
  - array의 크기는 n으로 주어지며 tree의 크기가 n 보다 큰 경우에는 순서대로 n개 까지만 변환

## 구현 규칙
- `src/rbtree.c` 이외에는 수정하지 않고 test를 통과해야 합니다.

## 과제의 의도 (Motivation)

- 복잡한 자료구조(data structure)를 구현해 봄으로써 자신감 상승
- C 언어, 특히 포인터(pointer)와 malloc, free 등의 system call에 익숙해짐.
- 동적 메모리 할당(dynamic memory allocation)을 직접 사용해 봄으로써 동적 메모리 할당의 필요성 체감 및 data segment에 대한 이해도 상승
- 고급 언어에서 기본으로 제공되는 자료구조가 세부적으로는 어떻게 구현되어 있는지 경험함으로써 고급 언어 사용시에도 효율성 고려

## 참고문헌
- [위키백과: 레드-블랙 트리](https://ko.wikipedia.org/wiki/%EB%A0%88%EB%93%9C-%EB%B8%94%EB%9E%99_%ED%8A%B8%EB%A6%AC)
([영어](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree))
- CLRS book (Introduction to Algorithms) 13장 레드 블랙 트리
- [Wikipedia:균형 이진 트리의 구현 방법들](https://en.wikipedia.org/wiki/Self-balancing_binary_search_tree#Implementations)

