/*
 * 파일명: number_processor.c
 * 설명: 숫자를 다양한 방식(문자열, 정수, 재귀)으로 처리하여 자릿수별로 출력하는 통합 프로그램
 * 기능: 높은/낮은 단위 순서로 출력, 문자열/정수/재귀 처리 방식 선택 가능
 */

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <math.h>

void string_high_to_low(void);
void string_low_to_high(void);
void number_high_to_low(long number);
void number_low_to_high(long number);
void recursive_high_to_low(long number);
void recursive_low_to_high(long number);

int main(void)
{
    int choice;
    long number = 12345698;
    
    printf("=== 숫자 처리 통합 프로그램 ===\n");
    printf("1. 문자열 처리 (높은 단위부터)\n");
    printf("2. 문자열 처리 (낮은 단위부터)\n");
    printf("3. 정수 처리 (높은 단위부터)\n");
    printf("4. 정수 처리 (낮은 단위부터)\n");
    printf("5. 재귀 처리 (높은 단위부터)\n");
    printf("6. 재귀 처리 (낮은 단위부터)\n");
    printf("선택하세요 (1-6): ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            string_high_to_low();
            break;
        case 2:
            string_low_to_high();
            break;
        case 3:
            printf("입력 숫자: %ld\n", number);
            number_high_to_low(number);
            break;
        case 4:
            printf("입력 숫자: %ld\n", number);
            number_low_to_high(number);
            break;
        case 5:
            printf("입력 숫자: %ld\n", number);
            recursive_high_to_low(number);
            break;
        case 6:
            printf("입력 숫자: %ld\n", number);
            recursive_low_to_high(number);
            break;
        default:
            printf("잘못된 선택입니다.\n");
    }
    
    printf("Press any key to continue...");
    getch();
    return 0;
}

void string_high_to_low(void)
{
    char number[20];
    int length, i;
    printf("금액을 입력하고 Enter>");
    scanf("%s", number);
    length = strlen(number);
    printf("높은 단위부터 출력:\n");
    for(i = 0; i < length; i++)
        printf("%c\n", number[i]);
}

void string_low_to_high(void)
{
    char number[20];
    int length, i;
    printf("금액을 입력하고 Enter>");
    scanf("%s", number);
    length = strlen(number);
    printf("낮은 단위부터 출력:\n");
    for(i = length - 1; i >= 0; i--)
        printf("%c\n", number[i]);
}

void number_high_to_low(long number)
{
    int num;
    int i, length = 0;
    length = (int)(log10(number) + 1);
    printf("높은 단위부터 출력:\n");
    for(i = length; i >= 1; i--)
    {
        num = number / (long)pow(10, i - 1);
        printf("%d\n", num);
        number = number - num * (long)pow(10, i - 1);
    }
}

void number_low_to_high(long number)
{
    printf("낮은 단위부터 출력:\n");
    while(number > 0)
    {
        printf("%ld\n", number % 10);
        number /= 10;
    }
}

void recursive_high_to_low(long number)
{
    if (number > 0)
    {
        recursive_high_to_low(number / 10);
        printf("%ld\n", number % 10);
    }
}

void recursive_low_to_high(long number)
{
    if (number > 0)
    {
        printf("%ld\n", number % 10);
        recursive_low_to_high(number / 10);
    }
}