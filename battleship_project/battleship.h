#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BOARD_SIZE 10
#define SHIP_COUNT 5
#define MAX_NAME_LENGTH 50

// Cell states
#define WATER '~'
#define SHIP 'S'
#define HIT 'X'
#define MISS 'O'

// Ship structure
typedef struct {
    char name[20];
    int size;
    int hits;
} Ship;

// Player structure
typedef struct {
    char name[MAX_NAME_LENGTH];
    char board[BOARD_SIZE][BOARD_SIZE];
    char tracking_board[BOARD_SIZE][BOARD_SIZE];
    int score;
    int total_hits;
    int total_misses;
} Player;

// Function prototypes
void init_board(char board[BOARD_SIZE][BOARD_SIZE]);
void display_board(char board[BOARD_SIZE][BOARD_SIZE], int hide_ships);
void place_ships_randomly(char board[BOARD_SIZE][BOARD_SIZE]);
int process_shot(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);
void save_high_score(Player *player);
void load_high_scores();
void save_game_state(Player *p, Player *c);
int load_game_state(Player *p, Player *c);

#endif
