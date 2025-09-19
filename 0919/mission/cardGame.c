#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

struct trump {
    int order;
    char shape[4];  // UTF-8 문자 (3바이트) + NULL 문자
    int number;     // 항상 1~13 저장
};

void make_card(struct trump m_card[]) {
    char shape[4][4] = {"♠", "♦", "♥", "♣"};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            int idx = i * 13 + j;
            m_card[idx].order = i;
            strcpy(m_card[idx].shape, shape[i]);
            m_card[idx].number = j + 1;
        }
    }
}

void display_card(struct trump m_card[]) {
    for (int i = 0; i < 52; i++) {
        printf("%s", m_card[i].shape);
        switch (m_card[i].number) {
            case 1:
                printf("A  ");
                break;
            case 11:
                printf("J  ");
                break;
            case 12:
                printf("Q  ");
                break;
            case 13:
                printf("K  ");
                break;
            default:
                printf("%-2d ", m_card[i].number);
        }

        if ((i + 1) % 13 == 0)
            printf("\n");
    }
}

void shuffle_card(struct trump m_card[]) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 52; i++) {
        int rnd = rand() % 52;
        struct trump temp = m_card[i];
        m_card[i] = m_card[rnd];
        m_card[rnd] = temp;
    }
}

int main(void) {
    SetConsoleOutputCP(CP_UTF8);  // 중요
    struct trump card[52];
    make_card(card);
    shuffle_card(card);
    display_card(card);
    return 0;
}
