#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define RED "\xb1[31m"
#define RESET "\xb1[35m"
#define WIDTH 33
#define HEIGHT 44

int snakeX[150], snakeY[150];
int snakeLength = 3;
int fruitX, fruitY;
int score = 0;
int gameover = 0;
int dirX = 1, dirY = 0;
int nextDirX = 1, nextDirY = 0;
int level = 1;

void setup() {
    snakeX[0] = 7;
    snakeY[0] = 5;
    snakeX[1] = 6;
    snakeY[1] = 5;
    snakeX[2] = 5;
    snakeY[2] = 5;
    
    do {
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
    } while ((fruitX == snakeX[0] && fruitY == snakeY[0]) ||
             (fruitX == snakeX[1] && fruitY == snakeY[1]) ||
             (fruitX == snakeX[2] && fruitY == snakeY[2]));
}

    // Move cursor to top-left to redraw in-place (prevents terminal scrolling)
    void initConsole(void) {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hOut, &cursorInfo);
        cursorInfo.bVisible = FALSE; // hide cursor
        SetConsoleCursorInfo(hOut, &cursorInfo);
    }

    void restoreConsole(void) {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hOut, &cursorInfo);
        cursorInfo.bVisible = TRUE; // show cursor
        SetConsoleCursorInfo(hOut, &cursorInfo);
    }

    static inline void resetCursor(void) {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD topLeft = {0, 0};
        SetConsoleCursorPosition(hOut, topLeft);
    }

void draw() {
    // Move cursor to top-left and overwrite the same region each frame
    resetCursor();

    // Print fixed-size frame with no extra leading/trailing blank lines
    printf("   +");
    for (int x = 0; x < WIDTH; x++) printf("-");
    printf("+\n");

    for (int y = 0; y < HEIGHT; y++) {
        printf("   |");
        for (int x = 0; x < WIDTH; x++) {
            int isSnake = 0;
            for (int i = 0; i < snakeLength; i++) {
                if (snakeX[i] == x && snakeY[i] == y) {
                    printf("*");
                    isSnake = 1;
                    break;
                }
            }
            if (!isSnake) {
                if (fruitX == x && fruitY == y) {
                    printf("+");
                } else {
                    printf(" ");
                }
            }
        }
        printf("|\n");
    }

    printf("   +");
    for (int x = 0; x < WIDTH; x++) printf("-");
    printf("+\n");

    // Status line always occupies the same position after the frame
    printf("   Score: %d   Level: %d\n", score, level);
    fflush(stdout);
}

void input() {
    if (_kbhit()) {
        int key = _getch();
        switch (key) {
            case 72: // Arrow Up
            case 'w':
            case 'W':
                if (dirY == 0) {
                    nextDirX = 0;
                    nextDirY = -1;
                }
                break;
            case 80: // Arrow Down
            case 's':
            case 'S':
                if (dirY == 0) {
                    nextDirX = 0;
                    nextDirY = 1;
                }
                break;
            case 75: // Arrow Left
            case 'a':
            case 'A':
                if (dirX == 0) {
                    nextDirX = -1;
                    nextDirY = 0;
                }
                break;
            case 77: // Arrow Right
            case 'd':
            case 'D':
                if (dirX == 0) {
                    nextDirX = 1;
                    nextDirY = 0;
                }
                break;
            case 27:
            case 'x':
            case 'X':
                gameover = 1;
                break;
        }
    }
}

void update() {
    dirX = nextDirX;
    dirY = nextDirY;
    
    for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }
    
    snakeX[0] += dirX;
    snakeY[0] += dirY;
    
    // Wrap around (original Nokia style)
    if (snakeX[0] < 0) snakeX[0] = WIDTH - 1;
    if (snakeX[0] >= WIDTH) snakeX[0] = 0;
    if (snakeY[0] < 0) snakeY[0] = HEIGHT - 1;
    if (snakeY[0] >= HEIGHT) snakeY[0] = 0;
    
    // Check collision with self
    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            Beep(400, 100);
            Sleep(50);
            Beep(300, 100);
            Sleep(50);
            Beep(200, 100);
            gameover = 1;
            return;
        }
    }
    
    // Check collision with fruit
    if (snakeX[0] == fruitX && snakeY[0] == fruitY) {
        Beep(800, 80);
        Sleep(30);
        Beep(1000, 80);
        
        score += 10;
        snakeLength++;
        
        // Level up every 5 fruits
        if (score % 50 == 0) {
            level++;
        }
        
        // Spawn new fruit
        int validPosition = 0;
        while (!validPosition) {
            fruitX = rand() % WIDTH;
            fruitY = rand() % HEIGHT;
            validPosition = 1;
            
            for (int i = 0; i < snakeLength; i++) {
                if (fruitX == snakeX[i] && fruitY == snakeY[i]) {
                    validPosition = 0;
                    break;
                }
            }
        }
    }
}

int main(void) {
    srand((unsigned int)time(NULL));
    setup();
    
    system("cls");
    printf("\n\n");
    printf(RED"       N O K I A   S N A K E\n"RESET);
    printf("\n");
    printf("    +---+\n");
    printf(RED"    |     SCORE  HISCOR\n"RESET);
    printf("    |     0000    0000\n");
    printf("    +---+\n");
    printf("\n");
    printf("   INSTRUCTIONS:\n");
    printf("   - Use arrow keys or WASD to move\n");
    printf("   - Eat the fruit (+) to grow\n");
    printf("   - Don't hit yourself!\n");
    printf("   - Press X to quit\n");
    printf("\n");
    printf("   Press any key to start...");
    fflush(stdout);
    _getch();
    
    int gameSpeed = 150;
    
    while (!gameover) {
        draw();
        input();
        update();
        Sleep(gameSpeed - (level * 5 > 100 ? 100 : level * 5));
    }
    
    system("cls");
    printf("\n\n");
    printf(RED"       GAME OVER\n"RESET);
    printf("\n");
    printf("       SCORE: %d\n", score);
    printf("       LEVEL: %d\n", level);
    printf("\n");
    printf("   Press any key to exit...");
    fflush(stdout);
    _getch();
    system("cls");
    
    return 0;
}