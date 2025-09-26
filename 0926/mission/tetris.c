/*
 * File: tetris_english.c
 * Description: Tetris game that runs in Windows CMD console (English Version)
 * Controls: A/D - Left/Right move, S - Fast drop, W - Rotate, ESC - Quit
 * Compile: gcc tetris_english.c -o tetris_english.exe
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define BOARD_WIDTH 12
#define BOARD_HEIGHT 20
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

// Global variables
int board[BOARD_HEIGHT][BOARD_WIDTH];
int currentPiece[4][4];
int nextPiece[4][4];
int currentX = 4, currentY = 0;
int score = 0;
int level = 1;
int lines = 0;

// Tetris pieces definition (7 types)
int pieces[7][4][4] = {
    // I piece
    {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    },
    // O piece
    {
        {0,0,0,0},
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0}
    },
    // T piece
    {
        {0,0,0,0},
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0}
    },
    // S piece
    {
        {0,0,0,0},
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0}
    },
    // Z piece
    {
        {0,0,0,0},
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0}
    },
    // J piece
    {
        {0,0,0,0},
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0}
    },
    // L piece
    {
        {0,0,0,0},
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0}
    }
};

// Function declarations
void gotoxy(int x, int y);
void hideCursor(void);
void initializeGame(void);
void drawBoard(void);
void drawPiece(int piece[4][4], int x, int y);
void drawNextPiece(void);
void drawScore(void);
int canMovePiece(int piece[4][4], int x, int y);
void placePiece(int piece[4][4], int x, int y);
void rotatePiece(int piece[4][4]);
int clearLines(void);
void generateNewPiece(void);
void gameLoop(void);
void gameOver(void);

int main(void)
{
    srand((unsigned)time(NULL));
    hideCursor();
    
    printf("=== CMD Tetris Game ===\n\n");
    printf("Controls:\n");
    printf("A/D - Left/Right move\n");
    printf("S - Fast drop\n");
    printf("W - Rotate piece\n");
    printf("ESC - Quit game\n\n");
    printf("Press any key to start...");
    getch();
    
    system("cls");
    initializeGame();
    gameLoop();
    
    return 0;
}

void gotoxy(int x, int y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void hideCursor(void)
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void initializeGame(void)
{
    int i, j;
    
    // Initialize board (walls are 1, empty spaces are 0)
    for(i = 0; i < BOARD_HEIGHT; i++) {
        for(j = 0; j < BOARD_WIDTH; j++) {
            if(j == 0 || j == BOARD_WIDTH-1 || i == BOARD_HEIGHT-1) {
                board[i][j] = 1; // Wall
            } else {
                board[i][j] = 0; // Empty space
            }
        }
    }
    
    // Generate first piece
    generateNewPiece();
}

void drawBoard(void)
{
    int i, j;
    
    gotoxy(0, 0);
    
    for(i = 0; i < BOARD_HEIGHT; i++) {
        for(j = 0; j < BOARD_WIDTH; j++) {
            if(board[i][j] == 1) {
                printf("##");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}

void drawPiece(int piece[4][4], int x, int y)
{
    int i, j;
    
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            if(piece[i][j] == 1) {
                gotoxy((x + j) * 2, y + i);
                printf("[]");
            }
        }
    }
}

void drawNextPiece(void)
{
    int i, j;
    
    gotoxy(30, 2);
    printf("Next:");
    
    for(i = 0; i < 4; i++) {
        gotoxy(30, 3 + i);
        for(j = 0; j < 4; j++) {
            if(nextPiece[i][j] == 1) {
                printf("[]");
            } else {
                printf("  ");
            }
        }
    }
}

void drawScore(void)
{
    gotoxy(30, 8);
    printf("Score: %d", score);
    gotoxy(30, 9);
    printf("Level: %d", level);
    gotoxy(30, 10);
    printf("Lines: %d", lines);
    
    gotoxy(30, 12);
    printf("Controls:");
    gotoxy(30, 13);
    printf("A/D - Move");
    gotoxy(30, 14);
    printf("S - Drop");
    gotoxy(30, 15);
    printf("W - Rotate");
    gotoxy(30, 16);
    printf("ESC - Quit");
}

int canMovePiece(int piece[4][4], int x, int y)
{
    int i, j;
    
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            if(piece[i][j] == 1) {
                int newX = x + j;
                int newY = y + i;
                
                // Boundary check
                if(newX < 0 || newX >= BOARD_WIDTH || newY >= BOARD_HEIGHT) {
                    return 0;
                }
                
                // Collision check with board
                if(newY >= 0 && board[newY][newX] == 1) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void placePiece(int piece[4][4], int x, int y)
{
    int i, j;
    
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            if(piece[i][j] == 1) {
                int newX = x + j;
                int newY = y + i;
                if(newY >= 0 && newX >= 0 && newX < BOARD_WIDTH && newY < BOARD_HEIGHT) {
                    board[newY][newX] = 1;
                }
            }
        }
    }
}

void rotatePiece(int piece[4][4])
{
    int temp[4][4];
    int i, j;
    
    // 90 degrees clockwise rotation
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            temp[j][3-i] = piece[i][j];
        }
    }
    
    // Copy rotated piece back to original
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            piece[i][j] = temp[i][j];
        }
    }
}

int clearLines(void)
{
    int i, j, k;
    int linesCleared = 0;
    
    for(i = BOARD_HEIGHT - 2; i >= 0; i--) { // Exclude bottom wall
        int fullLine = 1;
        
        // Check if line is full
        for(j = 1; j < BOARD_WIDTH - 1; j++) { // Exclude side walls
            if(board[i][j] == 0) {
                fullLine = 0;
                break;
            }
        }
        
        // Remove full line and move upper lines down
        if(fullLine) {
            for(k = i; k > 0; k--) {
                for(j = 1; j < BOARD_WIDTH - 1; j++) {
                    board[k][j] = board[k-1][j];
                }
            }
            // Set top line to empty
            for(j = 1; j < BOARD_WIDTH - 1; j++) {
                board[0][j] = 0;
            }
            linesCleared++;
            i++; // Check same line again
        }
    }
    
    return linesCleared;
}

void generateNewPiece(void)
{
    int i, j;
    int pieceType = rand() % 7;
    int nextPieceType = rand() % 7;
    
    // Copy current piece to next piece
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            currentPiece[i][j] = nextPiece[i][j];
        }
    }
    
    // Generate new next piece
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            nextPiece[i][j] = pieces[nextPieceType][i][j];
        }
    }
    
    // First piece case
    static int firstPiece = 1;
    if(firstPiece) {
        for(i = 0; i < 4; i++) {
            for(j = 0; j < 4; j++) {
                currentPiece[i][j] = pieces[pieceType][i][j];
            }
        }
        firstPiece = 0;
    }
    
    currentX = 4;
    currentY = 0;
}

void gameLoop(void)
{
    clock_t lastTime = clock();
    int dropTime = 500; // 500ms
    
    while(1) {
        // Draw screen
        drawBoard();
        drawPiece(currentPiece, currentX, currentY);
        drawNextPiece();
        drawScore();
        
        // Handle keyboard input
        if(kbhit()) {
            char key = getch();
            int tempPiece[4][4];
            int i, j;
            
            switch(key) {
                case 'a': case 'A': // Move left
                    if(canMovePiece(currentPiece, currentX - 1, currentY)) {
                        currentX--;
                    }
                    break;
                    
                case 'd': case 'D': // Move right
                    if(canMovePiece(currentPiece, currentX + 1, currentY)) {
                        currentX++;
                    }
                    break;
                    
                case 's': case 'S': // Fast drop
                    if(canMovePiece(currentPiece, currentX, currentY + 1)) {
                        currentY++;
                        score++;
                    }
                    break;
                    
                case 'w': case 'W': // Rotate
                    // Store rotated shape in temporary piece
                    for(i = 0; i < 4; i++) {
                        for(j = 0; j < 4; j++) {
                            tempPiece[i][j] = currentPiece[i][j];
                        }
                    }
                    rotatePiece(tempPiece);
                    
                    // Check if rotation is possible
                    if(canMovePiece(tempPiece, currentX, currentY)) {
                        for(i = 0; i < 4; i++) {
                            for(j = 0; j < 4; j++) {
                                currentPiece[i][j] = tempPiece[i][j];
                            }
                        }
                    }
                    break;
                    
                case 27: // ESC key
                    gotoxy(0, BOARD_HEIGHT + 1);
                    printf("Game terminated.\n");
                    return;
            }
        }
        
        // Handle automatic drop
        clock_t currentTime = clock();
        if(currentTime - lastTime > dropTime) {
            if(canMovePiece(currentPiece, currentX, currentY + 1)) {
                currentY++;
            } else {
                // Piece reached bottom
                placePiece(currentPiece, currentX, currentY);
                
                // Check for line clears
                int clearedLines = clearLines();
                if(clearedLines > 0) {
                    lines += clearedLines;
                    score += clearedLines * 100 * level;
                    level = lines / 10 + 1;
                    dropTime = 500 - (level - 1) * 50; // Faster as level increases
                    if(dropTime < 100) dropTime = 100;
                }
                
                // Generate new piece
                generateNewPiece();
                
                // Check game over
                if(!canMovePiece(currentPiece, currentX, currentY)) {
                    gameOver();
                    return;
                }
            }
            lastTime = currentTime;
        }
        
        Sleep(50); // Control CPU usage
    }
}

void gameOver(void)
{
    gotoxy(0, BOARD_HEIGHT + 1);
    printf("=== GAME OVER ===\n");
    printf("Final Score: %d\n", score);
    printf("Level: %d\n", level);
    printf("Lines: %d\n", lines);
    printf("Press any key to exit...");
    getch();
}