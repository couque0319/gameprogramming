
# 게임 프로그래밍 C언어 🎮

## 📖 주요 학습 내용

### 1. 콘솔 제어 기초
- **커서 위치 제어**: `gotoxy()` 함수로 원하는 위치에 출력
- **화면 지우기**: `system("cls")` 명령 활용
- **키 입력 처리**: `getch()`, `getche()`, `getchar()` 차이점

### 2. 키보드 입력 처리
- **ASCII 코드 vs 스캔 코드** 구분
- **방향키 입력** 처리 (상: 72, 하: 80, 좌: 75, 우: 77)
- **확장키 코드** 처리 방법

### 3. 그래픽 요소
- **사각형 그리기**: 확장 완성형 문자 활용 (─, │, ┌, ┘)
- **동적 크기 조절** 가능한 도형
- **텍스트 모드** 그래픽 구현

### 4. 사용자 인터페이스
- **단일 메뉴** 시스템
- **다단계 메뉴** 구조 (메인 → 서브 메뉴)
- **메뉴 네비게이션** 구현

### 5. 게임 로직
- **난수 생성**: 주사위, 로또 번호 생성
- **중복 없는 난수**: 로또 번호 생성 알고리즘
- **범위별 난수**: 특정 구간 내 난수 생성

### 6. 고급 기법
- **가변 인수**: `va_list`, `va_start`, `va_arg`, `va_end`
- **동적 함수**: 인수 개수가 가변적인 함수 구현

## 💡 핵심 함수 예제

### 커서 이동
```c
void gotoxy(int x, int y) {
    COORD Pos = {x - 1, y - 1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
```

### 방향키 처리
```c
void move_arrow_key(char key, int *x, int *y, int x_max, int y_max) {
    switch(key) {
        case 72: (*y)--; if(*y < 1) *y = 1; break;        // 위
        case 80: (*y)++; if(*y > y_max) *y = y_max; break; // 아래
        case 75: (*x)--; if(*x < 1) *x = 1; break;        // 왼쪽
        case 77: (*x)++; if(*x > x_max) *x = x_max; break; // 오른쪽
    }
}
```

### 범위별 난수
```c
// 주사위 (1~6)
int dice = rand() % 6 + 1;

// 로또 (1~45)
int lotto = rand() % 45 + 1;
```

