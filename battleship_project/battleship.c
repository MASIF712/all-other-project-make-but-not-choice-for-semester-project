#include "battleship.h"

void init_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = WATER;
        }
    }
}

void display_board(char board[BOARD_SIZE][BOARD_SIZE], int hide_ships) {
    printf("   ");
    for (int i = 0; i < BOARD_SIZE; i++) printf("%d ", i);
    printf("\n");

    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%2d ", i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            char cell = board[i][j];
            if (hide_ships && cell == SHIP) {
                printf("%c ", WATER);
            } else {
                printf("%c ", cell);
            }
        }
        printf("\n");
    }
}

void place_ships_randomly(char board[BOARD_SIZE][BOARD_SIZE]) {
    int ship_sizes[] = {5, 4, 3, 3, 2};
    for (int i = 0; i < SHIP_COUNT; i++) {
        int placed = 0;
        while (!placed) {
            int row = rand() % BOARD_SIZE;
            int col = rand() % BOARD_SIZE;
            int dir = rand() % 2; // 0 for horizontal, 1 for vertical

            int can_place = 1;
            if (dir == 0) {
                if (col + ship_sizes[i] > BOARD_SIZE) can_place = 0;
                else {
                    for (int j = 0; j < ship_sizes[i]; j++) {
                        if (board[row][col + j] != WATER) {
                            can_place = 0;
                            break;
                        }
                    }
                }
                if (can_place) {
                    for (int j = 0; j < ship_sizes[i]; j++) board[row][col + j] = SHIP;
                    placed = 1;
                }
            } else {
                if (row + ship_sizes[i] > BOARD_SIZE) can_place = 0;
                else {
                    for (int j = 0; j < ship_sizes[i]; j++) {
                        if (board[row + j][col] != WATER) {
                            can_place = 0;
                            break;
                        }
                    }
                }
                if (can_place) {
                    for (int j = 0; j < ship_sizes[i]; j++) board[row + j][col] = SHIP;
                    placed = 1;
                }
            }
        }
    }
}

int process_shot(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    if (board[row][col] == SHIP) {
        board[row][col] = HIT;
        return 1;
    } else if (board[row][col] == WATER) {
        board[row][col] = MISS;
        return 0;
    }
    return -1; // Already shot
}

void save_high_score(Player *player) {
    FILE *file = fopen("high_scores.txt", "a");
    if (file == NULL) {
        perror("Error opening high scores file");
        return;
    }
    fprintf(file, "%s %d %d %d\n", player->name, player->score, player->total_hits, player->total_misses);
    fclose(file);
}

void load_high_scores() {
    FILE *file = fopen("high_scores.txt", "r");
    if (file == NULL) {
        printf("No high scores yet.\n");
        return;
    }
    char name[MAX_NAME_LENGTH];
    int score, hits, misses;
    printf("\n--- High Scores ---\n");
    printf("%-20s %-10s %-10s %-10s\n", "Name", "Score", "Hits", "Misses");
    while (fscanf(file, "%s %d %d %d", name, &score, &hits, &misses) != EOF) {
        printf("%-20s %-10d %-10d %-10d\n", name, score, hits, misses);
    }
    fclose(file);
}

void save_game_state(Player *p, Player *c) {
    FILE *file = fopen("game_state.bin", "wb");
    if (file == NULL) {
        perror("Error saving game state");
        return;
    }
    fwrite(p, sizeof(Player), 1, file);
    fwrite(c, sizeof(Player), 1, file);
    fclose(file);
    printf("Game state saved successfully.\n");
}

int load_game_state(Player *p, Player *c) {
    FILE *file = fopen("game_state.bin", "rb");
    if (file == NULL) {
        return 0;
    }
    fread(p, sizeof(Player), 1, file);
    fread(c, sizeof(Player), 1, file);
    fclose(file);
    return 1;
}
