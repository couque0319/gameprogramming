#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <thread>
#include <atomic>

#define INNING 9

std::atomic<bool> music_running(true);

//============================
// 콘솔 색상 및 출력 관련
//============================
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void draw_line() {
    printf("-------------------------------------------------------------\n");
}

//============================
// 🎵 배경음악 루프 (빠른 템포)
//============================
void playKBOMelody() {
    int melody[][2] = {
        {523,120}, {659,120}, {784,130}, {880,120},
        {988,120}, {880,120}, {784,100}, {659,100},
        {784,130}, {659,110}, {523,250}, {0,100},
        {784,100}, {880,100}, {988,130}, {1046,130},
        {988,120}, {880,100}, {784,100}, {659,100},
        {523,150}, {0,150},
    };

    while (music_running) {
        for (auto &note : melody) {
            if (!music_running) return;
            if (note[0] == 0)
                Sleep(note[1]);
            else
                Beep(note[0], note[1]);
        }
    }
}

//============================
// 🎬 인트로
//============================
void intro_screen() {
    system("cls");
    setColor(11);
    printf("\n");
    printf("██████╗  █████╗ ███████╗██████╗  █████╗ ██╗    ██╗\n");
    printf("██╔══██╗██╔══██╗██╔════╝██╔══██╗██╔══██╗██║    ██║\n");
    printf("██████╔╝███████║███████╗██████╔╝███████║██║ █╗ ██║\n");
    printf("██╔═══╝ ██╔══██║╚════██║██╔══██╗██╔══██║██║███╗██║\n");
    printf("██║     ██║  ██║███████║██║  ██║██║  ██║╚███╔███╔╝\n");
    printf("╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚══╝╚══╝ \n");
    printf("\n");
    setColor(14);
    printf("             ⚾ BASEBALL DASHBOARD 2.0 ⚾\n");
    printf("          ▶ PRESS ENTER TO START ◀\n\n");
    setColor(7);
}

void waitForEnter() {
    fflush(stdin);
    getchar();
}

//============================
// 기본 정보 입력 및 출력
//============================
void input_team(char team[2][20]) {
    printf("1팀 이름 입력 : ");
    scanf("%s", team[0]);
    printf("2팀 이름 입력 : ");
    scanf("%s", team[1]);
}

// 스코어보드를 항상 깔끔하게 다시 그리는 함수
void display_scoreboard(char team[2][20], int inning_score[2][INNING], int r[], int h[], int e[], int b[]) {
    system("cls");
    draw_line();
    printf("회차 |");
    for (int i = 1; i <= INNING; i++) printf(" %2d", i);
    printf(" |  R  H  E  B\n");
    draw_line();

    for (int t = 0; t < 2; t++) {
        printf("%-7s|", team[t]);
        for (int i = 0; i < INNING; i++) {
            if (inning_score[t][i] >= 0)
                printf(" %2d", inning_score[t][i]);
            else
                printf("  -");
        }
        printf(" | %2d %2d %2d %2d\n", r[t], h[t], e[t], b[t]);
    }
    draw_line();
}

//============================
// 경기 점수 입력 or 시뮬레이션
//============================
void input_inning_score(char team[2][20], int inning_score[2][INNING], int r[], int h[], int e[], int b[], int auto_mode) {
    int rr, hh, ee, bb;

    for (int i = 0; i < INNING; i++) {
        for (int t = 0; t < 2; t++) {
            if (auto_mode == 2) {
                rr = rand() % 5;
                hh = rand() % 4;
                ee = rand() % 2;
                bb = rand() % 3;
            } else {
                printf("\n[%s - %d회차]\n", team[t], i + 1);
                printf("점수 : "); scanf("%d", &rr);
                printf("안타 : "); scanf("%d", &hh);
                printf("실책 : "); scanf("%d", &ee);
                printf("포볼 : "); scanf("%d", &bb);
            }

            inning_score[t][i] = rr;
            r[t] += rr;
            h[t] += hh;
            e[t] += ee;
            b[t] += bb;

            // 스코어보드 갱신
            display_scoreboard(team, inning_score, r, h, e, b);
            Sleep(300);
        }
    }
}

//============================
// 결과 및 파일 저장
//============================
void print_result(char team[2][20], int r[]) {
    draw_line();
    if (r[0] > r[1]) { setColor(10); printf("%s 승리!\n", team[0]); }
    else if (r[1] > r[0]) { setColor(12); printf("%s 승리!\n", team[1]); }
    else { setColor(14); printf("무승부!\n"); }
    setColor(7);
    draw_line();
}

void save_result(char team[2][20], int r[], int h[], int e[], int b[]) {
    FILE *fp = fopen("score.txt", "w");
    fprintf(fp, "[Game Result]\n");
    fprintf(fp, "%-10s R:%2d  H:%2d  E:%2d  B:%2d\n", team[0], r[0], h[0], e[0], b[0]);
    fprintf(fp, "%-10s R:%2d  H:%2d  E:%2d  B:%2d\n", team[1], r[1], h[1], e[1], b[1]);
    if (r[0] > r[1]) fprintf(fp, "Winner: %s\n", team[0]);
    else if (r[1] > r[0]) fprintf(fp, "Winner: %s\n", team[1]);
    else fprintf(fp, "Result: Draw\n");
    fclose(fp);
}

//============================
// 메인
//============================
int main(void) {
    char team[2][20];
    int r[2] = {0}, h[2] = {0}, e[2] = {0}, b[2] = {0};
    int inning_score[2][INNING];
    int auto_mode;

    for (int t = 0; t < 2; t++)
        for (int i = 0; i < INNING; i++)
            inning_score[t][i] = -1; // 초기화

    srand((unsigned)time(NULL));

    // 🎬 인트로 + 음악 루프
    std::thread music_thread(playKBOMelody);
    intro_screen();
    waitForEnter();
    music_running = false;
    music_thread.join();

    system("cls");
    printf("⚾ 야구 스코어보드 2.0 ⚾\n\n");
    input_team(team);

    printf("\n1. 수동 입력 모드\n2. 랜덤 시뮬레이션 모드\n\n선택 (1/2): ");
    scanf("%d", &auto_mode);
    system("cls");

    display_scoreboard(team, inning_score, r, h, e, b);
    input_inning_score(team, inning_score, r, h, e, b, auto_mode);
    print_result(team, r);
    save_result(team, r, h, e, b);

    printf("\n결과가 'score.txt' 파일로 저장되었습니다.\n");
    return 0;
}
