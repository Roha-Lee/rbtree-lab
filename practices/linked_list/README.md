# linkedlist C로 구현해보기 
- RB트리를 만들기 전 C언어에 익숙해지기 위해 만들어 보는 linked list.

# 구조체 정의
## node
- int val: 노드에 저장될 자료 
- struct node *next: 다음 노드를 가리킬 노드 포인터
## linkedlist
- node *head: 연결리스트의 맨 앞을 가리키는 포인터 
- node *tail: 연결리스트의 맨 뒤를 가리키는 포인터 

# 기능 체크리스트 
## 리스트 생성, 삭제
- [ ] `generate_linkedlist()`: 연결리스트 생성
    - 동적 할당하고 각 노드 포인터 NULL로 초기화
- [ ] `delete_linkedlist(linkedlist *p)`: 연결리스트 p 삭제
    - 재귀함수를 이용해서 끝에서 부터 메모리 해제
    - 모든 노드를 제거한 후 연결 리스트 삭제

## 리스트 코어 기능 
- [ ] `prepend(value)`: 앞쪽에 노드 추가 
- [ ] `append(value)`: 뒤쪽에 노드 추가 
- [ ] `pop()`: 뒤쪽에서 노드 제거 
- [ ] `popFirst()`: 앞쪽에서 노드 제거 
- [ ] `head()`: 맨 앞쪽 노드를 반환 
- [ ] `tail()`: 맨 뒤쪽 노드를 반환 
- [ ] `remove(Node)`: Node를 리스트로부터 제거 

## 유틸
- [ ] `print_linked_list(linkedlist *)`: 연결리스트의 데이터 출력
    - 빈 