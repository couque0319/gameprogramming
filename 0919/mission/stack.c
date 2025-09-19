#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// 스택 노드 구조체 정의 (PDF 내용 기반)
typedef struct StackNode {
    char data;                    // 데이터 필드
    struct StackNode* link;       // 링크 필드 (다음 노드를 가리킴)
} StackNode;

// 스택 구조체 정의
typedef struct {
    StackNode* top;               // 스택의 최상위 노드를 가리키는 포인터
    int count;                    // 스택에 저장된 데이터 개수
} Stack;

// 함수 선언
void initStack(Stack* stack);
int isEmpty(Stack* stack);
void push(Stack* stack, char data);
char pop(Stack* stack);
char peek(Stack* stack);
void printStack(Stack* stack);
void clearStack(Stack* stack);
int getStackSize(Stack* stack);

// 테스트 함수들
void testBasicOperations();
void testStackReverse();
void testParenthesesCheck();
void interactiveTest();
void showMenu();

// 스택 초기화 함수
void initStack(Stack* stack) {
    stack->top = NULL;
    stack->count = 0;
    printf("스택이 초기화되었습니다.\n");
}

// 스택이 비어있는지 확인하는 함수
int isEmpty(Stack* stack) {
    return (stack->top == NULL);
}

// Push 함수 - 스택에 데이터 삽입 (PDF 내용 기반)
void push(Stack* stack, char data) {
    // 1단계: 새 노드를 위한 메모리 동적 할당
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    
    if (newNode == NULL) {
        printf("메모리 할당 실패! Push 연산을 수행할 수 없습니다.\n");
        return;
    }
    
    // 2단계: 새 노드에 데이터 저장
    newNode->data = data;
    
    // 3단계: 새 노드의 링크를 현재 top으로 설정
    newNode->link = stack->top;
    
    // 4단계: top을 새 노드로 업데이트
    stack->top = newNode;
    
    // 5단계: 스택 크기 증가
    stack->count++;
    
    printf("'%c' 데이터가 스택에 Push되었습니다. (현재 크기: %d)\n", data, stack->count);
}

// Pop 함수 - 스택에서 데이터 삭제 및 반환 (PDF 내용 기반)
char pop(Stack* stack) {
    // 1단계: 스택이 비어있는지 확인
    if (isEmpty(stack)) {
        printf("스택이 비어있습니다! Pop 연산을 수행할 수 없습니다.\n");
        return '\0';  // NULL 문자 반환
    }
    
    // 2단계: 삭제할 노드 (현재 top) 저장
    StackNode* nodeToDelete = stack->top;
    
    // 3단계: 반환할 데이터 저장
    char poppedData = nodeToDelete->data;
    
    // 4단계: top을 다음 노드로 업데이트
    stack->top = nodeToDelete->link;
    
    // 5단계: 이전 top 노드의 메모리 해제
    free(nodeToDelete);
    
    // 6단계: 스택 크기 감소
    stack->count--;
    
    printf("'%c' 데이터가 스택에서 Pop되었습니다. (현재 크기: %d)\n", poppedData, stack->count);
    
    return poppedData;
}

// Peek 함수 - 스택의 top 데이터를 삭제하지 않고 반환
char peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("스택이 비어있습니다!\n");
        return '\0';
    }
    
    return stack->top->data;
}

// 스택 전체 출력 함수 (top부터 bottom까지)
void printStack(Stack* stack) {
    if (isEmpty(stack)) {
        printf("스택이 비어있습니다.\n");
        return;
    }
    
    printf("\n=== 현재 스택 상태 (크기: %d) ===\n", stack->count);
    printf("TOP → ");
    
    StackNode* current = stack->top;
    int position = stack->count;
    
    while (current != NULL) {
        printf("[%d:'%c']", position, current->data);
        current = current->link;
        position--;
        
        if (current != NULL) {
            printf(" → ");
        }
    }
    
    printf(" → BOTTOM\n");
    printf("================================\n\n");
}

// 스택 전체 삭제 함수
void clearStack(Stack* stack) {
    while (!isEmpty(stack)) {
        pop(stack);
    }
    printf("스택이 완전히 비워졌습니다.\n");
}

// 스택 크기 반환 함수
int getStackSize(Stack* stack) {
    return stack->count;
}

// 기본 연산 테스트 함수
void testBasicOperations() {
    printf("\n=== 기본 스택 연산 테스트 ===\n");
    
    Stack testStack;
    initStack(&testStack);
    
    // Push 테스트
    printf("\n1. Push 연산 테스트:\n");
    push(&testStack, 'A');
    push(&testStack, 'B');
    push(&testStack, 'C');
    push(&testStack, 'D');
    
    printStack(&testStack);
    
    // Peek 테스트
    printf("2. Peek 연산 테스트:\n");
    printf("Top 데이터: '%c'\n", peek(&testStack));
    printStack(&testStack);
    
    // Pop 테스트
    printf("3. Pop 연산 테스트:\n");
    char popped1 = pop(&testStack);
    char popped2 = pop(&testStack);
    
    printStack(&testStack);
    
    // 남은 데이터 모두 Pop
    printf("4. 남은 데이터 모두 Pop:\n");
    while (!isEmpty(&testStack)) {
        pop(&testStack);
    }
    
    // 빈 스택에서 Pop 시도
    printf("5. 빈 스택에서 Pop 시도:\n");
    pop(&testStack);
    
    clearStack(&testStack);
}

// 문자열 뒒집기 테스트 (스택의 LIFO 특성 활용)
void testStackReverse() {
    printf("\n=== 문자열 뒤집기 테스트 ===\n");
    
    Stack reverseStack;
    initStack(&reverseStack);
    
    char input[] = "HELLO";
    printf("원본 문자열: %s\n", input);
    
    // 문자열의 각 문자를 스택에 Push
    printf("\nPush 과정:\n");
    for (int i = 0; input[i] != '\0'; i++) {
        push(&reverseStack, input[i]);
    }
    
    printStack(&reverseStack);
    
    // 스택에서 Pop하여 뒤집힌 문자열 생성
    printf("Pop하여 뒤집힌 문자열 생성:\n");
    char reversed[100];
    int index = 0;
    
    while (!isEmpty(&reverseStack)) {
        reversed[index++] = pop(&reverseStack);
    }
    reversed[index] = '\0';
    
    printf("뒤집힌 문자열: %s\n", reversed);
    
    clearStack(&reverseStack);
}

// 괄호 짝 맞추기 테스트
void testParenthesesCheck() {
    printf("\n=== 괄호 짝 맞추기 테스트 ===\n");
    
    Stack parenStack;
    char testCases[][50] = {
        "(())",
        "((()))",
        "()())",
        "((())",
        "()()()",
        ")("
    };
    
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    for (int t = 0; t < numTests; t++) {
        initStack(&parenStack);
        char* expr = testCases[t];
        int isValid = 1;
        
        printf("\n테스트 %d: \"%s\"\n", t+1, expr);
        
        for (int i = 0; expr[i] != '\0' && isValid; i++) {
            if (expr[i] == '(') {
                push(&parenStack, expr[i]);
                printf("'(' 발견 - Push\n");
            }
            else if (expr[i] == ')') {
                if (isEmpty(&parenStack)) {
                    printf("')' 발견 - 매칭되는 '('가 없음!\n");
                    isValid = 0;
                } else {
                    pop(&parenStack);
                    printf("')' 발견 - 매칭되는 '(' Pop\n");
                }
            }
        }
        
        if (isValid && isEmpty(&parenStack)) {
            printf("결과: 올바른 괄호 표현식 ✓\n");
        } else {
            printf("결과: 잘못된 괄호 표현식 ✗\n");
        }
        
        clearStack(&parenStack);
    }
}

// 대화형 테스트 함수
void interactiveTest() {
    printf("\n=== 대화형 스택 테스트 ===\n");
    printf("키보드를 누를 때마다 스택에 데이터를 추가합니다.\n");
    printf("ESC 키를 누르면 입력을 종료하고 역순으로 출력합니다.\n\n");
    
    Stack interactiveStack;
    initStack(&interactiveStack);
    
    char key;
    printf("키를 입력하세요 (ESC로 종료): ");
    
    while (1) {
        key = getch();  // 키 입력 받기
        
        if (key == 27) {  // ESC 키 (ASCII 27)
            break;
        }
        
        // 특수 키나 제어 문자가 아닌 경우만 처리
        if (key >= 32 && key <= 126) {
            printf("%c", key);  // 입력한 키 출력
            push(&interactiveStack, key);
        }
    }
    
    printf("\n\n입력이 완료되었습니다!\n");
    printStack(&interactiveStack);
    
    printf("스택에서 데이터를 Pop하여 역순으로 출력:\n");
    printf("출력: ");
    
    while (!isEmpty(&interactiveStack)) {
        printf("%c", pop(&interactiveStack));
    }
    
    printf("\n");
    clearStack(&interactiveStack);
}

// 메뉴 출력 함수
void showMenu() {
    printf("\n=== 🗄️ 스택 자료구조 테스트 프로그램 🗄️ ===\n");
    printf("1. 기본 스택 연산 테스트 (Push, Pop, Peek)\n");
    printf("2. 문자열 뒤집기 테스트\n");
    printf("3. 괄호 짝 맞추기 테스트\n");
    printf("4. 대화형 스택 테스트\n");
    printf("5. 스택 구조 설명 보기\n");
    printf("0. 종료\n");
    printf("선택: ");
}

// 스택 구조 설명 함수
void showStackExplanation() {
    printf("\n=== 📚 스택 (Stack) 자료구조 설명 ===\n\n");
    
    printf("🔹 스택이란?\n");
    printf("   - 데이터의 추가와 삭제가 한쪽 끝(TOP)에서만 일어나는 자료구조\n");
    printf("   - LIFO (Last In First Out) 구조: 나중에 들어간 것이 먼저 나옴\n");
    printf("   - 예시: 책 더미, 접시 더미, 새 수건 더미\n\n");
    
    printf("🔹 주요 연산:\n");
    printf("   - Push: 스택의 TOP에 데이터 추가\n");
    printf("   - Pop:  스택의 TOP에서 데이터 제거 및 반환\n");
    printf("   - Peek: TOP의 데이터를 제거하지 않고 확인\n");
    printf("   - isEmpty: 스택이 비어있는지 확인\n\n");
    
    printf("🔹 구현 방식:\n");
    printf("   - 동적 메모리 할당 사용 (malloc, free)\n");
    printf("   - 연결 리스트 방식으로 노드 연결\n");
    printf("   - 각 노드: 데이터 필드 + 링크 필드\n\n");
    
    printf("🔹 활용 예시:\n");
    printf("   - 함수 호출 스택\n");
    printf("   - 괄호 짝 맞추기\n");
    printf("   - 문자열 뒤집기\n");
    printf("   - Undo/Redo 기능\n");
    printf("   - 게임에서의 상태 저장\n\n");
    
    printf("🔹 시간 복잡도:\n");
    printf("   - Push: O(1)\n");
    printf("   - Pop:  O(1)\n");
    printf("   - Peek: O(1)\n\n");
}

// 메인 함수
int main() {
    int choice;
    
    printf("🗄️ 스택(Stack) 자료구조 구현 및 테스트 프로그램 🗄️\n");
    printf("PDF 문서의 스택 이론을 바탕으로 구현된 프로그램입니다.\n");
    
    while (1) {
        showMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                testBasicOperations();
                break;
                
            case 2:
                testStackReverse();
                break;
                
            case 3:
                testParenthesesCheck();
                break;
                
            case 4:
                interactiveTest();
                break;
                
            case 5:
                showStackExplanation();
                break;
                
            case 0:
                printf("프로그램을 종료합니다. 📚 감사합니다!\n");
                return 0;
                
            default:
                printf("잘못된 선택입니다. 다시 선택해주세요.\n");
                break;
        }
        
        printf("\n계속하려면 아무 키나 누르세요...");
        getch();
    }
    
    return 0;
}