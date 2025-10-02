
# 게임 프로그래밍 C03 정리

## 1. 숫자의 변환과 표현

### 자리 수 분리
- 입력된 숫자를 자리 단위로 분리해 출력하는 방법
- 방법 1: 문자열로 처리 → `strlen()` 사용
- 방법 2: 정수로 처리 → `log10()`, `pow()` 활용

```c
// 높은 단위부터 출력
for(i=0;i<length;i++)
    printf("%c\n", number[i]);

// 낮은 단위부터 출력
for(i=length;i>=0;i--)
    printf("%c\n", number[i]);
```

```c
// 정수 처리 방식
void serial_number(long number) {
    int num, i, length=(int)(log10(number)+1);
    for(i=length;i>=1;i--) {
        num = number / (long)pow(10, i-1);
        printf("%ld\n", num);
        number -= num * (long)pow(10, i-1);
    }
}
```

```c
// 낮은 단위부터 출력
void reverse_number(long number) {
    while(number > 0) {
        printf("%ld\n", number % 10);
        number /= 10;
    }
}
```

---

## 2. 재귀적 호출
- 입력된 숫자를 재귀적으로 분리하여 출력

```c
// 높은 단위부터 출력
void serial_number(long number) {
    if(number > 0) {
        serial_number(number/10);
        printf("%ld\n", number%10);
    }
}
```

```c
// 낮은 단위부터 출력
void reverse_number(long number) {
    printf("%ld\n", number%10);
    if(number/10 > 0)
        reverse_number(number/10);
}
```

---

## 3. 디지털 숫자 출력
- 0~9까지 숫자를 2차원 배열로 정의 (1=■, 0=공백)
- 각 자리의 숫자를 재귀적으로 출력

```c
void digit_print(int dim[], int line) {
    for(int i=line*4; i<=line*4+3; i++) {
        if(dim[i]==1) printf("■");
        else printf("  ");
    }
}
```

```c
void number_check(int k, int i) {
    if(k>=1) {
        number_check(k/10, i);
        switch(k%10) {
            case 0: digit_print(zero, i); break;
            case 1: digit_print(one, i); break;
            ...
        }
    }
}
```

---

## 4. 수평/수직 슬라이드 바
- `draw_rectangle` 함수로 슬라이드 바를 그림
- 방향키 입력 처리: `move_arrow_key()`
- 특수기호 `■`로 현재 위치를 표시

```c
void draw_horizontal_slide(int x, int y, int length, char *s) {
    int real_length = length/2;
    gotoxy(1, y);
    draw_rectangle(real_length+1, 1);
    gotoxy(x+2, y+1);
    printf("%s", s);
}
```

```c
void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b) {
    switch(key) {
        case 72: *y1 = (*y1>1)? *y1-1:1; break; // 위
        case 75: *x1 = (*x1>1)? *x1-1:1; break; // 왼쪽
        case 77: *x1 = (*x1<x_b)? *x1+1:x_b; break; // 오른쪽
        case 80: *y1 = (*y1<y_b)? *y1+1:y_b; break; // 아래
    }
}
```

---

## 5. 도형 이동 및 회전
- 방향키로 상하좌우 이동
- 스페이스 키로 90도 회전

### 회전 처리
```c
void rotation_right(int m[][3]) {
    int temp[3][3];
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            temp[j][2-i] = m[i][j];
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            m[i][j] = temp[i][j];
}
```

### 도형 출력
```c
void print_shape(int m[][3]) {
    for(int i=0;i<3;i++) {
        gotoxy(x,y+i);
        for(int j=0;j<3;j++)
            if(m[i][j]==1) printf("□");
            else printf("  ");
    }
}
```

