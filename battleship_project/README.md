# Console-Based Battleship in C

This project is a console-based implementation of the classic Battleship game, designed to demonstrate core C programming concepts.

## Key Features & Concepts Demonstrated

### 1. 2D Arrays
The game board is represented using a 10x10 2D array (`char board[BOARD_SIZE][BOARD_SIZE]`). This is used for both the player's own board (to track ship placement and enemy hits) and a tracking board (to record the player's shots against the enemy).

### 2. Structures
A `Player` structure is used to encapsulate all data related to a player, including their name, boards, score, and statistics.
```c
typedef struct {
    char name[MAX_NAME_LENGTH];
    char board[BOARD_SIZE][BOARD_SIZE];
    char tracking_board[BOARD_SIZE][BOARD_SIZE];
    int score;
    int total_hits;
    int total_misses;
} Player;
```

### 3. File Handling
The game includes two types of file operations:
- **High Scores:** Player statistics are appended to a text file (`high_scores.txt`) at the end of each game.
- **Game State:** The current state of the game can be saved to a binary file (`game_state.bin`) and reloaded later, allowing players to resume their progress.

### 4. Pointers
Pointers are used extensively to pass large structures (like `Player`) to functions by reference. This avoids unnecessary copying of data and allows functions to modify the original player data directly.
```c
void save_high_score(Player *player);
void save_game_state(Player *p, Player *c);
```

## How to Compile and Run

1. **Compile:**
   ```bash
   gcc -o battleship main.c battleship.c -I.
   ```

2. **Run:**
   ```bash
   ./battleship
   ```

## Gameplay Instructions
- Choose to start a new game, load a saved game, or view high scores.
- During your turn, enter coordinates in the format `row col` (e.g., `3 4`).
- Enter `-1 -1` at any time to save your current game and exit.
- The game ends when either you or the computer sinks all enemy ships.
