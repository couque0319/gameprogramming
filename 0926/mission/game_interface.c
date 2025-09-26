/*
 * 파일명: game_interface.c
 * 설명: 게임에서 사용되는 인터페이스 요소들(슬라이드바, 도형 이동/회전)을 통합한 프로그램
 * 기능: 1) 수평/수직 슬라이드바 제어 2) 도형의 실시간 이동 및 회전
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// 공통 함수
void gotoxy(int x, int y);
void draw_rectangle(int c, int r);

// 슬라이드바 관련 함수
void run_slidebar(void);
void draw_horizontal_slide(int x, int y, int length, char *s);
void draw_vertical_slide(int x, int y, int length, char *s);
void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b);

// 도형 이동/회전 관련 함수
void run_shape_control(void);
void rotation_right(int m[][3]);
void move_shape(int m[][3]);
void print_shape(int m[][3]);
void move_control(int m[][3]);
void print_direction(void);

int x = 35, y = 12;
int inx = 0, iny = 0;

int main(void)
{
    int choice;
    
    printf("=== 게임 인터페이스 제어 통합 프로그램 ===\n");
    printf("1. 슬라이드바 제어\n");
    printf("2. 도형 이동/회전 제어\n");
    printf("선택하세요 (1-2): ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            run_slidebar();
            break;
        case 2:
            run_shape_control();
            break;
        default:
            printf("잘못된 선택입니다.\n");
    }
    
    return 0;
}

void run_slidebar(void)
{
    char *slide = "■", key;
    int slide_x = 1, slide_y = 1;
    int h_slide_length, v_slide_length;
    
    printf("슬라이드바 표시\n\n");
    printf("수평 슬라이드바의 길이(최대 70)를 입력하고 Enter> ");
    scanf("%d", &h_slide_length);
    printf("수직 슬라이드바의 길이(최대 19)를 입력하고 Enter> ");
    scanf("%d", &v_slide_length);
    
    system("cls");
    do
    {
        draw_vertical_slide(1, slide_y, v_slide_length, slide);
        draw_horizontal_slide(slide_x, v_slide_length + 3, h_slide_length, slide);
        key = getch();
        move_arrow_key(key, &slide_x, &slide_y, h_slide_length, v_slide_length);
    } while(key != 27);
}

void run_shape_control(void)
{
    int shape1[3][3] = {0,1,0,
                        0,1,0,
                        1,1,1};
    printf("도형 이동/회전 제어를 시작합니다.\n");
    printf("화살표: 이동, 스페이스: 회전, ESC: 종료\n");
    printf("아무 키나 누르세요...");
    getch();
    move_control(shape1);
}

// 공통 함수들
void gotoxy(int x, int y)
{
    COORD Pos = {x - 1, y - 1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void draw_rectangle(int c, int r)
{
    int i, j;
    unsigned char a = 0xa6;
    unsigned char b[7];
    for(i = 1; i < 7; i++)
        b[i] = 0xa0 + i;
    
    printf("%c%c", a, b[3]);
    for(i = 0; i < c; i++)
        printf("%c%c", a, b[1]);
    printf("%c%c", a, b[4]);
    printf("\n");
    
    for(i = 0; i < r; i++)
    {
        printf("%c%c", a, b[2]);
        for(j = 0; j < c; j++)
            printf("  ");
        printf("%c%c", a, b[2]);
        printf("\n");
    }
    
    printf("%c%c", a, b[6]);
    for(i = 0; i < c; i++)
        printf("%c%c", a, b[1]);
    printf("%c%c", a, b[5]);
    printf("\n");
}

// 슬라이드바 관련 함수들
void draw_horizontal_slide(int x, int y, int length, char *s)
{
    int real_length = length / 2;
    gotoxy(1, y);
    draw_rectangle(real_length + 1, 1);
    gotoxy(x + 2, y + 1);
    printf("%s", s);
    gotoxy(real_length * 2 + 2, y - 1);
    printf("%2d", x);
}

void draw_vertical_slide(int x, int y, int length, char *s)
{
    gotoxy(x, 1);
    draw_rectangle(1, length);
    gotoxy(x + 2, y + 1);
    printf("%s", s);
    gotoxy(x + 6, length + 1);
    printf("%2d", y);
}

void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b)
{
    switch(key)
    {
        case 72: // 위쪽(상) 방향의 화살표 키 입력
            *y1 = *y1 - 1;
            if (*y1 < 1) *y1 = 1;
            break;
        case 75: // 왼쪽(좌) 방향의 화살표 키 입력
            *x1 = *x1 - 1;
            if (*x1 < 1) *x1 = 1;
            break;
        case 77: // 오른쪽(우) 방향의 화살표 키 입력
            *x1 = *x1 + 1;
            if (*x1 > x_b) *x1 = x_b;
            break;
        case 80: // 아래쪽(하) 방향의 화살표 키 입력
            *y1 = *y1 + 1;
            if (*y1 > y_b) *y1 = y_b;
            break;
    }
}

// 도형 이동/회전 관련 함수들
void rotation_right(int m[][3])
{
    int i, j;
    int temp[3][3];
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            temp[j][2 - i] = m[i][j];
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            m[i][j] = temp[i][j];
}

void print_direction(void)
{
    gotoxy(25, 1);
    printf("화살표:이동, 스페이스 키:회전, ESC:종료");
}

void move_control(int m[][3])
{
    char key;
    do
    {
        while(!kbhit())
        {
            system("cls");
            move_shape(m);
        }
        key = getch();
        switch(key)
        {
            case 32: // 스페이스(space) 키 - 회전
                rotation_right(m);
                move_shape(m);
                break;
            case 72: // 위쪽(상) 방향의 화살표 키 입력
                inx = 0; iny = -1;
                move_shape(m);
                break;
            case 75: // 왼쪽(좌) 방향의 화살표 키 입력
                inx = -1; iny = 0;
                move_shape(m);
                break;
            case 77: // 오른쪽(우) 방향의 화살표 키 입력
                inx = 1; iny = 0;
                move_shape(m);
                break;
            case 80: // 아래쪽(하) 방향의 화살표 키 입력
                inx = 0; iny = 1;
                move_shape(m);
                break;
        }
    } while(key != 27); // ESC 키로 종료
    printf("\n");
}

void print_shape(int m[][3])
{
    int i, j;
    for(i = 0; i < 3; i++)
    {
        gotoxy(x, y + i);
        for(j = 0; j < 3; j++)
            if (m[i][j] == 1)
                printf("□");
            else
                printf("  ");
        printf("\n");
    }
}

void move_shape(int m[][3])
{
    do
    {
        system("cls");
        print_shape(m);
        print_direction();
        x = x + inx;
        y = y + iny;
        if (y > 23) y = 23;
        else if (y < 2) y = 2;
        if (x > 75) x = 75;
        else if (x < 1) x = 1;
        Sleep(100);
    } while(!kbhit());
}