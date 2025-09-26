/*
 * 파일명: digital_display.c
 * 설명: 입력된 숫자를 7세그먼트 디스플레이 스타일로 출력하는 프로그램
 * 기능: 0-9 숫자를 ■ 문자를 이용해 디지털 형태로 표시
 */

#include <stdio.h>

void number_check(int k, int i);
void digit_print(int dim[], int line);

// 디지털 숫자 패턴 배열들 (0-9)
int digits[10][20] = {
    // 0
    {1,1,1,1, 1,0,0,1, 1,0,0,1, 1,0,0,1, 1,1,1,1},
    // 1
    {0,0,1,0, 0,0,1,0, 0,0,1,0, 0,0,1,0, 0,0,1,0},
    // 2
    {1,1,1,1, 0,0,0,1, 1,1,1,1, 1,0,0,0, 1,1,1,1},
    // 3
    {1,1,1,1, 0,0,0,1, 1,1,1,1, 0,0,0,1, 1,1,1,1},
    // 4
    {1,0,0,1, 1,0,0,1, 1,1,1,1, 0,0,0,1, 0,0,0,1},
    // 5
    {1,1,1,1, 1,0,0,0, 1,1,1,1, 0,0,0,1, 1,1,1,1},
    // 6
    {1,0,0,0, 1,0,0,0, 1,1,1,1, 1,0,0,1, 1,1,1,1},
    // 7
    {1,1,1,1, 0,0,0,1, 0,0,0,1, 0,0,0,1, 0,0,0,1},
    // 8
    {1,1,1,1, 1,0,0,1, 1,1,1,1, 1,0,0,1, 1,1,1,1},
    // 9
    {1,1,1,1, 1,0,0,1, 1,1,1,1, 0,0,0,1, 0,0,0,1}
};

int main(void)
{
    int num, line;
    printf("=== 디지털 숫자 출력 프로그램 ===\n");
    printf("1 이상의 정수만 입력합니다.\n\n");
    printf("정수 숫자입력 후 Enter> ");
    scanf("%d", &num);
    printf("\n\n");
    
    for(line = 0; line <= 4; line++)
    {
        number_check(num, line);
        printf("\n");
    }
    return 0;
}

void digit_print(int dim[], int line)
{
    int i;
    for(i = line * 4; i <= line * 4 + 3; i++)
        if (dim[i] == 1)
            printf("■");
        else
            printf(" ");
    printf(" ");
}

void number_check(int k, int i)
{
    if (k >= 1)
    {
        number_check(k / 10, i);
        digit_print(digits[k % 10], i);
    }
}