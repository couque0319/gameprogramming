#include <stdio.h>
#include <windows.h> // Windows API 사용

void draw_square(int size);

int main(void)
{
    SetConsoleOutputCP(CP_UTF8); // 콘솔 출력 인코딩을 UTF-8로 설정

    int n;
    printf("정사각형 그리기\n\n");
    printf("정사각형의 길이(최대 37)를\n");
    printf("입력하고 Enter> ");
    scanf("%d", &n);
    
    if (n < 1 || n > 37) {
        printf("유효한 크기를 입력하세요 (1~37)\n");
        return 1;
    }

    draw_square(n);
    return 0;
}

void draw_square(int size)
{
    int i, j;

    // 상단
    printf("┌");
    for (i = 0; i < size; i++)
        printf("─");
    printf("┐\n");

    // 중간
    for (i = 0; i < size; i++) {
        printf("│");
        for (j = 0; j < size; j++)
            printf(" ");
        printf("│\n");
    }

    // 하단
    printf("└");
    for (i = 0; i < size; i++)
        printf("─");
    printf("┘\n");
}
