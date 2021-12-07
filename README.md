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

## Red Black tree 시간 복잡도 
- 삽입: O(logN)
- 삭제: O(logN)

## 구현 하기 전 공부 
### 개요 
- `T.nil`은 리프노드를 내부 노드와 동일하게 다루기 위해 사용 
  - **트리 안에서만 사용해야 한다**
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
  ![경우 1](https://user-images.githubusercontent.com/82917798/145071973-84ed1c67-50ee-4523-b52a-d3358ce88091.jpeg)
    - 해법) 
    - `new_node->parent`와 그 삼촌을 검정으로 칠한다. 
    - `new_node->parent->parent`를 빨강으로 칠한다. 
    - `new_node = new_node->parent->parent` 로 두고 다음 반복을 수행한다.
  - 경우 2) `new_node`의 삼촌 `y`가 검정이고 `new_node`가 부모의 오른쪽 자식인 경우 
  - 경우 3) `new_node`의 삼촌 `y`가 검정이고 `new_node`가 부모의 왼쪽 자식인 경우 
  ![경우 2 & 3](https://user-images.githubusercontent.com/82917798/145072076-a243ad70-6102-4b44-8b96-728451981828.jpeg)
    - 해법) 
    - 경우 2에서 `new_node = new_node->parent;`를 한 후 `left_rotate(t, new_node);`를 하면 경우 3으로 변환이 가능하다. 
    - 경우 3의 경우 `new_node->parent`를 검정으로, `new_node->parent->parent`를 빨강으로 칠한 다음 `right_rotate(t, new_node->parent->parent);`를 수행하면 된다.
    

### Transplant
- `Transplant(T, u, v)`는 `u->parent`의 자식노드를 `u`대신 `v`로 바꾸어 주는 기능을 수행한다. 
- 이 때, `u`는 삭제되는 것이 아니라 `u->parent`로부터 접근이 불가능하게 된 것 뿐이다. 

### Deletion
- 옮기거나 삭제되는 노드의 원래 색을 기억해 두었다가 **검정**인 경우만 deletion fixup을 통해 트리를 고쳐준다. 
  - 빨강인 경우는 옮겨도 RB 트리의 특성을 위반하지 않기 때문에 트리를 고칠 필요가 없다. 
  - 검정인 경우는 옮기거나 이동할 경우 경로상의 검정 노드의 개수가 변하게 되므로 트리 특성을 위반하게 된다. 
    - deletion fixup을 통해 수정한다. 
- Deletion의 경우 크게 세 가지로 나누어서 구현한다. 
  - 삭제하려는 노드의 왼쪽 자식만 있는 경우
  - 삭제하려는 노드의 오른쪽 자식만 있는 경우
  - 삭제하려는 노드의 왼쪽, 오른쪽 자식이 모두 있는 경우 
- 자식이 없는 경우는 한쪽 자식만 있는 경우를 구현했다면 자식 대신 nil노드가 참여하면서 자동으로 처리된다. 
- 삭제하려는 노드의 왼쪽 자식만 있는 경우는 왼쪽 자식을 삭제하려는 노드자리로 옮기면 된다. 
- 삭제하려는 노드의 오른쪽 자식만 있는 경우는 오른쪽 자식을 삭제하려는 노드자리로 옮기면 된다. 
- 삭제하려는 노드의 왼쪽과 오른쪽 자식이 모두 있는 경우는 다시 두 가지 경우로 나누어서 구현한다. 
  - 삭제하려는 노드의 오른쪽 자식의 왼쪽 자식이 없는 경우
  - 삭제하려는 노드의 오른쪽 자식의 왼쪽 자식이 있는 경우
    - 삭제하려는 노드의 직후 원소(다음으로 가장 큰 원소)를 찾아서 오른쪽 자식을 직후 원소 자리로 옮겨준다.(transplant)
    - 직후원소를 삭제하려는 노드 자리로 옮겨준다.(transplant)
    - 직후원소의 색을 삭제하려는 노드 색으로 바꿔준다.  

### Deletion fixup
- `Deletion(T, x)`는 x의 색이 빨강인지 검정인지에 따라 나누어서 처리한다. 
- Deletion의 경우 이동하거나 삭제된 노드가 검정일 경우에만 들어온다. 즉 x라는 노드에 여분의 검정을 하나 전달해 준 상태라고 생각할 수 있다. 
- `x`의 색이 빨강인 경우는 빨강 + 여분의 검정을 들고 있으므로 검정으로 칠해주고 끝내면 된다. 
- `x`의 색이 검정인 경우는 검정 + 여분의 검정을 들고 있다. 이는 8가지 경우로 나누어서 교정해야 한다. 
- **:bulb: 항상 루프의 시작위치에서 x는 검정을 2개 들고 있다.** 
  - 크게는 `x`가 왼쪽 자식인 경우와 오른쪽 자식인 경우로 나누어서 각각의 경우에 대하여 4가지 경우가 존재한다. 한 경우는 다른 경우에 대하여 대칭이므로 한쪽 경우에 대해서만 생각해보자. 
  - 경우 1) `x`의 형제 `w`가 빨강인 경우 
  ![경우1](https://user-images.githubusercontent.com/82917798/145069741-6e0497f2-5d18-4acc-87a9-631c8b91a4ea.jpeg)
    - 해법) 경우 1은 변환을 통해 경우 2~4로 바꾸어 줄 수 있다. 
    - `x->parent`와 `w`의 색을 바꾸고 `left_rotation(T, x->parent)`을 수행하면 RB트리의 특성은 바뀌지 않은 채로 트리의 모양이 바뀐다. 바뀐 트리는 경우 2~4에 해당한다. 
  - 경우 2) `x`의 형제 `w`가 검정이고 `w`의 두 자식이 모두 흑색인 경우 
  ![경우 2](https://user-images.githubusercontent.com/82917798/145069953-27d8618a-f800-4229-ac3c-4ea5407124bd.jpeg)
    - `x`는 검정 2개를 들고 있고 `w`는 검정 1개를 들고 있다. `x`와 `w`가 부모에게 검정을 1개씩 전달하여도 RB트리의 특성이 바뀌지 않는다. 
    - 부모가 빨강이었던 경우는 자식들에게 검정을 받아서 검정으로 바꾸고 함수를 종료한다. 
    - 부모가 검정이었던 경우는 2개의 검정을 들고 다음 루프를 실행하기 위해 `x = x->parent`로 바꾸고 다음 루프를 실행한다. 
  - 경우 3) `x`의 형제 `w`가 검정이고 `w`의 왼쪽 자식은 빨강, 오른쪽 자식은 검정인 경우 
  ![경우 3](https://user-images.githubusercontent.com/82917798/145070231-cf232155-30f3-4c79-ab0d-07cdc639e9be.jpeg)
    - 경우 1과 비슷하게 RB특성을 유지한채로 회전과 색 변경을 통해 트리의 모양을 바꿔준다. 바꾸고 나면 경우 4가 된다. 
    - `w`와 `w->left`의 색을 바꾸고 `right_rotation(T, w)`을 수행하면 RB 트리의 특성을 유지한채로 경우 4로 모양을 바꿀 수 있다. 
  - 경우 4) `x`의 형제 `w`는 검정이고 `w`의 오른쪽 자식은 빨강인 경우 
  ![경우 4](https://user-images.githubusercontent.com/82917798/145070465-4642b98b-01fe-4f9a-88db-a0995d429749.jpeg)
    - 노드색 변경과 회전을 통해 RB트리 특성 위반 없이 트리를 변형할 수 있다. 
    - 변형하게 되면 x에서 여분의 검정을 제거할 수 있다. 
      - `w->color = x->parent->color`
      - `x->parent->color = BLACK`
      - `w->right->color = BLACK`
      - `left_rotate(T, x->parent)`
    - `x = T->root`로 변경해서 마지막에 루트를 처리할 수 있도록 바꿔준다 

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
#### 새로운 RED BLACK TREE 생성
- [x] `rbtree *new_rbtree(void)` 
  - RB트리 생성 
  - rbtree 메모리 할당 
  - rbtree 멤버 초기화 
    - root를 NULL로 만들어주기 
    - nil에 메모리 할당한 후 BLACK으로 설정, 나머지는 NULL

#### RED BLACK TREE에 사용한 메모리 모두 해제
- [x] `void delete_rbtree(rbtree *t)` 
  - RB트리 생성에 사용했던 메모리 회수
  - `node_t * _delete(node_t * curr)` 보조 함수를 이용하여 재귀적으로 노드 삭제 
    - 리프노드부터 순차적으로 삭제(왼쪽 오른쪽 자식이 모두 `Tree.nil`인 경우 노드 반환)
    - 재귀적으로 다음 노드를 호출하면서 `free(_delete(curr->left));`, `free(_delete(curr->right));`와 같이 다음 갈 곳이 있는 노드를 방문하여 먼저 삭제 하고 이후에 반환된 노드를 해제한다. 

### 코어 기능 
#### 키 값을 갖는 새로운 노드 삽입 
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

#### 특정 키값을 갖는 노드 찾기 
- [x] `node_t *rbtree_find(const rbtree *t, const key_t key)`
  - 빈 트리인 경우 `NULL`을 반환
  - 쿼리의 키값과 현재 노드의 키값을 비교하여 쿼리의 키값이 큰 경우 우측 자식으로 이동, 작은 경우 좌측 자식으로 이동하면서 같은 값이 나올때까지 이동한다. 
  - 도중에 같은 값이 나오면 그 노드를 반환하고 값을 찾지 못하고 `tree->nil`을 만나면 `NULL(tree->nil)`을 반환한다. 

#### rbtree의 최대값 찾기 
- [x] `node_t *rbtree_max(const rbtree *t)`
  - 빈 트리인 경우 `NULL`을 반환
    - `tree->nil`이 더 적절하지 않을까:question:
      - **질문에 대한 답변:bulb:**
        - tree->nil의 경우 구현의 편의를 위해 트리 내부에서 사용하는 것으로 인터페이스에는 등장하면 안된다. 따라서 NULL을 반환하는 것이 맞다. 
  - 빈 트리가 아닌경우 `tree->root`부터 시작하여 가장 오른쪽에 있는 노드를 반환한다.  

#### rbtree의 최소값 찾기 
- [x] `node_t *rbtree_min(const rbtree *t)`
  - 빈 트리인 경우 `NULL`을 반환
  - 빈 트리가 아닌경우 `tree->root`부터 시작하여 가장 왼쪽에 있는 노드를 반환한다.  

#### rbtree를 array로 변환하기 
- [x] `int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)`
  - RB tree의 내용을 key 순서대로 주어진 arr로 변환하기
  - key 순서대로 얻기 위해서는 rbtree를 중위순회하여 순서대로 값을 넣으면 된다. 
  - 인자로 주어진 n이 tree의 노드 수보다 큰 경우는 없다고 가정한다. 
    - n이 tree의 노드 수 보다 큰 경우에는 `min(n, number_of_tree_node)`로 동적 할당을 하게 만들면 좋을 것 같다. :bulb:
  - 먼저 트리가 비어있는 경우는 아무것도 하지 않고 함수를 종료한다. 
  - 트리가 비어있지 않은 경우는 다음과 같이 수행한다. 
    - 현재 배열로 들어간 노드 수를 카운트 하는 변수를 만들고 이를 포인터로 전달하여 값을 계속 바꾸면서 n보다 작은 동안에만 중위 순회하며 배열에 넣어주고 아닌 경우는 바로 return하여 중위 순회를 종료시킨다. 

#### 노드 삭제하기 
- [x] `int rbtree_erase(rbtree *t, node_t *p)`
  - 특정 노드를 삭제하는 함수이다. 
  - 특정 노드를 삭제를 구현하기 위해서 `_transplant`, `_delete_fixup`를 추가로 구현하였다. 
  - Deletion과 transplant와 fixup의 경우 위의 구현 하기 전 공부한 내용과 동일하기 때문에 링크로 대체한다. 
  :link:[링크](#deletion)
  - [x] `void _transplant(rbtree *t, node_t *u, node_t *v)`  
    - (u를 제거하기 전에) u의 부모와 v를 연결해 주기 위한 함수 구현 완료 
  - [x] `void _delete_fixup(rbtree * t, node_t *x)`
    - [앞서 살펴본](#deletion-fixup) 8가지 케이스를 고려하여 RB 트리의 특성을 원상복구 시켜주는 함수 구현 완료. 
- 구현하며 알게 된 점
  - 아래 코드에서 `y->parent == p`일때 `x->parent = y`를 하는 부분이 CLRS의 의사코드에 적혀있었는데 이 부분이 잘 이해되지 않았는데, 구현하면서 이 부분이 왜 필요한지 알게 되었다. 
  - 아래 그림에서 2번 노드를 지우는 경우 직후 원소는 3이고 fixup함수에 x가 들어가게 된다. 일반적인 경우 x의 부모를 y로 만들어주지 않아도 알아서 부모-자식 관계가 성립이 되지만 nil인 경우에는 설정을 해줘야 한다. 따라서 이 부분의 코드가 필요했다. 
  ![내가 그린 그림1](https://user-images.githubusercontent.com/82917798/145068730-5b17b058-3473-4315-bcc6-aa0ce6ec6389.png)
```c
else {
    y = p->right;
    while(y->left != t->nil){
        y = y->left;
    }
    y_original = y->color;
    x = y->right;
    if(y->parent == p) {
        x->parent = y;
    }
    else {
        y->right = p->left;
        y->right->parent = y;
    }
    _transplant(t, p, y);
    y->left = p->left;
    y->left->parent = y;
    y->color = p->color;
}
```

## 테스트 
- [x] (자체제작) 트리 회전 테스트 통과
  - 회전관련한 테스트 케이스는 주어지지 않아서 따로 구현하였다. 
  - `test_rotate.c`파일에 테스트 케이스와 트리 출력 코드를 작성한 후 회전을 제대로 구현했는지 테스트 
  - 확인한 케이스는 위의 회전 구현에서 고려한 세가지 케이스이고 각각의 경우에 대하여 `left_rotation`, `right_rotation`을 테스트 하여 결과 출력하였다. 
- [x] 생성 삭제 테스트 통과 
  - `test-rbtree.c`파일의 `test_init`부분 통과 
- [x] 원소 1개 삽입하는 테스트 통과 
  - `test-rbtree.c`파일의 `test_insert_single`부분 통과 
- [x] (자체제작) insert test 통과
  - `test_rbtree_insert.c`파일에서 3가지 테스트 케이스에 대하여 결과가 일치하는지 확인하였다. 
- [x] `test-rbtree.c` 테스트 전부 통과

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

