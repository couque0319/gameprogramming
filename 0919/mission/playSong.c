#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <math.h>

// 음계 정의 (12평균율)
#define DO 0
#define RE 2  
#define MI 4
#define FA 5
#define SOL 7
#define LA 9
#define SI 11
#define DO_HIGH 12

// 음표 길이 정의 (밀리초)
#define WHOLE_NOTE 2000     // 온음표
#define HALF_NOTE 1000      // 2분음표
#define QUARTER_NOTE 500    // 4분음표
#define EIGHTH_NOTE 250     // 8분음표
#define SIXTEENTH_NOTE 125  // 16분음표

// 기본 옥타브 4의 도(C) 주파수
#define BASE_FREQUENCY 261.626

// 음계 인덱스 배열 (반음 제외)
int index_array[] = {DO, RE, MI, FA, SOL, LA, SI, DO_HIGH};

// 동요 구조체
typedef struct {
    int note;        // 음계 (0~7: 도~높은도)
    int octave;      // 옥타브 (1~8)
    int duration;    // 음표 길이 (밀리초)
} Note;

// 함수 선언
int calc_frequency(int octave, int note_index);
void play_note(int frequency, int duration);
void play_song(Note song[], int length, char* title);
void show_piano_keys();
void manual_play();
void show_menu();

// 주파수 계산 함수 (PDF 내용 기반)
int calc_frequency(int octave, int note_index) {
    // 옥타브 1의 도(C) = 32.7032 Hz
    double base_c1 = 32.7032;
    
    // 12평균율: 각 반음당 2^(1/12) ≈ 1.0594630943592953 배
    double ratio = pow(2.0, 1.0/12.0);
    
    // 요청한 옥타브의 도(C) 주파수 계산
    double octave_base = base_c1 * pow(2.0, octave - 1);
    
    // 해당 음계의 주파수 계산
    double frequency = octave_base * pow(ratio, index_array[note_index]);
    
    return (int)(frequency + 0.5);  // 반올림
}

// 음 재생 함수
void play_note(int frequency, int duration) {
    if (frequency > 0) {
        Beep(frequency, duration);
    } else {
        Sleep(duration);  // 쉼표
    }
}

// 노래 재생 함수
void play_song(Note song[], int length, char* title) {
    printf("\n♪♫ %s 연주 중... ♫♪\n", title);
    printf("연주를 중단하려면 아무 키나 누르세요.\n\n");
    
    for (int i = 0; i < length; i++) {
        // 키 입력 체크 (중단 기능)
        if (kbhit()) {
            getch();
            printf("\n연주가 중단되었습니다.\n");
            return;
        }
        
        // 음계 이름 표시
        char* note_names[] = {"도", "레", "미", "파", "솔", "라", "시", "높은도"};
        
        if (song[i].note >= 0) {
            printf("♪ %s(%d옥타브) ", note_names[song[i].note], song[i].octave);
            int freq = calc_frequency(song[i].octave, song[i].note);
            play_note(freq, song[i].duration);
        } else {
            printf("♪ 쉼표 ");
            play_note(0, song[i].duration);
        }
        
        // 줄바꿈 (4음마다)
        if ((i + 1) % 4 == 0) printf("\n");
    }
    
    printf("\n\n연주가 완료되었습니다! 👏\n");
}

// 피아노 건반 표시
void show_piano_keys() {
    printf("\n=== 가상 피아노 건반 ===\n");
    printf("숫자 키를 눌러 연주하세요 (ESC: 종료)\n\n");
    printf("1:도  2:레  3:미  4:파  5:솔  6:라  7:시  8:높은도\n");
    printf("│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │\n");
    printf("└───┴───┴───┴───┴───┴───┴───┴───┘\n\n");
}

// 수동 연주 모드
void manual_play() {
    char key;
    int octave = 4;  // 기본 옥타브 4
    
    show_piano_keys();
    printf("현재 옥타브: %d (위/아래 화살표로 변경 가능)\n\n", octave);
    
    while (1) {
        key = getch();
        
        if (key == 27) {  // ESC 키
            printf("수동 연주를 종료합니다.\n");
            break;
        }
        
        // 숫자 키 처리
        if (key >= '1' && key <= '8') {
            int note_index = key - '1';  // 0~7로 변환
            char* note_names[] = {"도", "레", "미", "파", "솔", "라", "시", "높은도"};
            
            printf("♪ %s(%d옥타브) ", note_names[note_index], octave);
            
            int frequency = calc_frequency(octave, note_index);
            play_note(frequency, QUARTER_NOTE);
        }
        
        // 옥타브 변경 (화살표 키는 특수 키이므로 간단하게 +/- 사용)
        else if (key == '+' || key == '=') {
            if (octave < 8) {
                octave++;
                printf("옥타브 증가: %d\n", octave);
            }
        }
        else if (key == '-') {
            if (octave > 1) {
                octave--;
                printf("옥타브 감소: %d\n", octave);
            }
        }
    }
}

// 메뉴 표시
void show_menu() {
    printf("\n=== 🎵 음계 동요 플레이어 🎵 ===\n");
    printf("1. 도레미송 연주\n");
    printf("2. 비행기 연주\n"); 
    printf("3. 학교종 연주\n");
    printf("4. 나비야 연주\n");
    printf("5. 수동 연주 모드\n");
    printf("6. 음계 주파수 표 보기\n");
    printf("0. 종료\n");
    printf("선택: ");
}

// 음계 주파수 표 출력
void show_frequency_table() {
    printf("\n=== 음계별 주파수 표 (옥타브 1~5) ===\n");
    printf("음계    ");
    for (int oct = 1; oct <= 5; oct++) {
        printf("옥타브%d  ", oct);
    }
    printf("\n");
    printf("────────────────────────────────────────\n");
    
    char* note_names[] = {"도  ", "레  ", "미  ", "파  ", "솔  ", "라  ", "시  ", "높은도"};
    
    for (int note = 0; note < 8; note++) {
        printf("%s  ", note_names[note]);
        for (int oct = 1; oct <= 5; oct++) {
            int freq = calc_frequency(oct, note);
            printf("%4dHz   ", freq);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int choice;
    
    printf("🎼 음계를 이용한 동요 플레이어 🎼\n");
    printf("Windows Beep 함수를 사용하여 동요를 연주합니다.\n");
    
    // 도레미송 (간단한 음계 연습)
    Note doremi[] = {
        {DO, 4, QUARTER_NOTE}, {RE, 4, QUARTER_NOTE}, {MI, 4, QUARTER_NOTE}, {DO, 4, QUARTER_NOTE},
        {DO, 4, QUARTER_NOTE}, {RE, 4, QUARTER_NOTE}, {MI, 4, QUARTER_NOTE}, {DO, 4, QUARTER_NOTE},
        {MI, 4, QUARTER_NOTE}, {FA, 4, QUARTER_NOTE}, {SOL, 4, HALF_NOTE},
        {MI, 4, QUARTER_NOTE}, {FA, 4, QUARTER_NOTE}, {SOL, 4, HALF_NOTE},
        {SOL, 4, EIGHTH_NOTE}, {LA, 4, EIGHTH_NOTE}, {SOL, 4, EIGHTH_NOTE}, {FA, 4, EIGHTH_NOTE},
        {MI, 4, QUARTER_NOTE}, {DO, 4, QUARTER_NOTE},
        {SOL, 4, EIGHTH_NOTE}, {LA, 4, EIGHTH_NOTE}, {SOL, 4, EIGHTH_NOTE}, {FA, 4, EIGHTH_NOTE},
        {MI, 4, QUARTER_NOTE}, {DO, 4, QUARTER_NOTE}
    };
    
    // 비행기 동요
    Note airplane[] = {
        {SOL, 4, QUARTER_NOTE}, {SOL, 4, QUARTER_NOTE}, {LA, 4, QUARTER_NOTE}, {LA, 4, QUARTER_NOTE},
        {SOL, 4, QUARTER_NOTE}, {SOL, 4, QUARTER_NOTE}, {MI, 4, HALF_NOTE},
        {FA, 4, QUARTER_NOTE}, {FA, 4, QUARTER_NOTE}, {MI, 4, QUARTER_NOTE}, {MI, 4, QUARTER_NOTE},
        {RE, 4, HALF_NOTE}, {-1, 0, QUARTER_NOTE},  // 쉼표
        {SOL, 4, QUARTER_NOTE}, {SOL, 4, QUARTER_NOTE}, {LA, 4, QUARTER_NOTE}, {LA, 4, QUARTER_NOTE},
        {SOL, 4, QUARTER_NOTE}, {SOL, 4, QUARTER_NOTE}, {MI, 4, HALF_NOTE},
        {FA, 4, QUARTER_NOTE}, {FA, 4, QUARTER_NOTE}, {MI, 4, QUARTER_NOTE}, {MI, 4, QUARTER_NOTE},
        {DO, 4, HALF_NOTE}
    };
    
    // 학교종 동요
    Note school_bell[] = {
        {SOL, 4, QUARTER_NOTE}, {SOL, 4, QUARTER_NOTE}, {LA, 4, QUARTER_NOTE}, {LA, 4, QUARTER_NOTE},
        {SOL, 4, QUARTER_NOTE}, {SOL, 4, QUARTER_NOTE}, {MI, 4, HALF_NOTE},
        {SOL, 4, QUARTER_NOTE}, {SOL, 4, QUARTER_NOTE}, {MI, 4, QUARTER_NOTE}, {MI, 4, QUARTER_NOTE},
        {DO, 4, WHOLE_NOTE}
    };
    
    // 나비야 동요
    Note butterfly[] = {
        {DO, 5, QUARTER_NOTE}, {SOL, 4, QUARTER_NOTE}, {SOL, 4, QUARTER_NOTE}, {LA, 4, QUARTER_NOTE},
        {SOL, 4, QUARTER_NOTE}, {FA, 4, QUARTER_NOTE}, {MI, 4, QUARTER_NOTE}, {RE, 4, QUARTER_NOTE},
        {DO, 4, QUARTER_NOTE}, {RE, 4, QUARTER_NOTE}, {MI, 4, QUARTER_NOTE}, {FA, 4, QUARTER_NOTE},
        {SOL, 4, HALF_NOTE}, {-1, 0, QUARTER_NOTE},
        {DO, 5, QUARTER_NOTE}, {SOL, 4, QUARTER_NOTE}, {SOL, 4, QUARTER_NOTE}, {LA, 4, QUARTER_NOTE},
        {SOL, 4, QUARTER_NOTE}, {FA, 4, QUARTER_NOTE}, {MI, 4, QUARTER_NOTE}, {RE, 4, QUARTER_NOTE},
        {DO, 4, WHOLE_NOTE}
    };
    
    while (1) {
        show_menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                play_song(doremi, sizeof(doremi)/sizeof(Note), "도레미송");
                break;
                
            case 2:
                play_song(airplane, sizeof(airplane)/sizeof(Note), "비행기");
                break;
                
            case 3:
                play_song(school_bell, sizeof(school_bell)/sizeof(Note), "학교종");
                break;
                
            case 4:
                play_song(butterfly, sizeof(butterfly)/sizeof(Note), "나비야");
                break;
                
            case 5:
                manual_play();
                break;
                
            case 6:
                show_frequency_table();
                break;
                
            case 0:
                printf("프로그램을 종료합니다. 🎵 안녕히 가세요! 🎵\n");
                return 0;
                
            default:
                printf("잘못된 선택입니다. 다시 선택해주세요.\n");
                break;
        }
    }
    
    return 0;
}