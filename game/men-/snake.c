#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Cross-platform headers: use POSIX APIs on Unix, WinAPI on Windows
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#endif

#define WIDTH 40
#define HEIGHT 20

typedef struct {
    int x, y;
} Point;

Point snake[WIDTH * HEIGHT];
int snake_len;
Point food;
int dir_x, dir_y;
bool game_over;
int score;

void init_game() {
    snake_len = 3;
    snake[0] = (Point){WIDTH / 2, HEIGHT / 2};
    snake[1] = (Point){WIDTH / 2 - 1, HEIGHT / 2};
    snake[2] = (Point){WIDTH / 2 - 2, HEIGHT / 2};
    
    dir_x = 1;
    dir_y = 0;
    
    score = 0;
    game_over = false;
    
    srand(time(NULL));
    food = (Point){rand() % WIDTH, rand() % HEIGHT};
}

void draw() {
    printf("\033[H"); // Move cursor to top-left
    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    for (int y = 0; y < HEIGHT; y++) {
        printf("#");
        for (int x = 0; x < WIDTH; x++) {
            bool is_snake = false;
            for (int i = 0; i < snake_len; i++) {
                if (snake[i].x == x && snake[i].y == y) {
                    printf(i == 0 ? "O" : "o");
                    is_snake = true;
                    break;
                }
            }
            if (!is_snake) {
                if (food.x == x && food.y == y) printf("@");
                else printf(" ");
            }
        }
        printf("#\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\nScore: %d\n", score);
}

// kbhit implementation for POSIX; on Windows use _kbhit()
#ifndef _WIN32
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}
#endif

void input() {
#ifdef _WIN32
    if (_kbhit()) {
        int c = _getch();
#else
    if (kbhit()) {
        int c = getchar();
#endif
        switch (c) {
            case 'w': case 'W': if (dir_y != 1) { dir_x = 0; dir_y = -1; } break;
            case 's': case 'S': if (dir_y != -1) { dir_x = 0; dir_y = 1; } break;
            case 'a': case 'A': if (dir_x != 1) { dir_x = -1; dir_y = 0; } break;
            case 'd': case 'D': if (dir_x != -1) { dir_x = 1; dir_y = 0; } break;
            case 'q': case 'Q': game_over = true; break;
        }
    }
}

void logic() {
    Point next_head = {snake[0].x + dir_x, snake[0].y + dir_y};

    if (next_head.x < 0 || next_head.x >= WIDTH || next_head.y < 0 || next_head.y >= HEIGHT) {
        game_over = true;
        return;
    }

    for (int i = 0; i < snake_len; i++) {
        if (snake[i].x == next_head.x && snake[i].y == next_head.y) {
            game_over = true;
            return;
        }
    }

    if (next_head.x == food.x && next_head.y == food.y) {
        score += 10;
        snake_len++;
        food = (Point){rand() % WIDTH, rand() % HEIGHT};
    }

    for (int i = snake_len - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }
    snake[0] = next_head;
}

int main() {
    init_game();
    printf("\033[2J"); // Clear screen
    while (!game_over) {
        draw();
        input();
        logic();
        // cross-platform sleep in milliseconds
    #ifdef _WIN32
        Sleep(100);
    #else
        usleep(100000); // 100ms delay
    #endif
    }
    printf("Game Over! Final Score: %d\n", score);
    return 0;
}
