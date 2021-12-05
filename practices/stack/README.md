# stack C로 구현해보기 🔥
- C언어에 익숙해지기 위해 만들어 보는 stack 
- linked list를 이용해서 stack 구현해보기 
# 구조체 정의
## node
- `int val`: 노드에 저장될 자료 
- `struct node *next`: 다음 노드를 가리킬 노드 포인터
## linkedlist
- `node *head`: 연결리스트의 맨 앞을 가리키는 포인터 
- `node *tail`: 연결리스트의 맨 뒤를 가리키는 포인터 
## stack
- `linkedlist *data`: 데이터가 저장되는 스택

# 기능 체크리스트 ✅
## 스택 생성, 삭제
- [x] `stack * create_stack()`: 스택을 생성
    - 스택 동적할당 & 멤버인 연결 리스트 동적할당
- [x] `void delete_stack(stack * st)`: 스택을 만드는데 사용한 메모리를 해제
    - 스택이 비어있지 않은 경우 전부 pop을 해서 메모리 해제 시켜준 후 스택의 메모리 해제 

## 스택 코어 기능 
- [x] `bool stack_is_empty(stack *)`: 스택이 비어있는지 확인 
    - 스택 내부에 연결 리스트가 있으므로 연결 리스트의 head가 있는지 확인하여 값 반환 
- [x] `void stack_push(stack *, int)` : 스택에 원소를 추가
    - 연결 리스트의 `append(linkedlist*, int)`를 이용하여 구현 
- [x] `void stack_pop(stack *)` : 스택에서 원소를 꺼냄
    - 처음에는 꺼낸 후 노드를 반환하려고 했는데, 이전에 연결리스트를 구현할 때 `remove_node(node *)`를 이용하여 `pop(linkedlise *)`를 구현한 것을 발견하였다.
    -  `remove_node(node *)`는 특정 노드를 메모리 해제까지 수행하여 삭제하는 함수로 이를 사용하기 위해 `stack_pop`에서는 제거한 노드를 반환하지 않도록 결정하였다. 
- [x] `node* stack_top(stack *)` : 최상단의 원소를 반환
    - 연결 리스트의 멤버인 tail을 반환하도록 구현하였다. 

## 유틸
- [x] `void stack_print(stack * st)` : 스택을 최하단부터 최상단까지 차례로 출력하는 함수
    - 연결 리스트를 순회하는 것으로 구현
