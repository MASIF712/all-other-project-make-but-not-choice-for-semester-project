#include "battleship.h"

int main() {
    srand(time(NULL));
    Player player, computer;
    int row, col, result;
    int total_ship_cells = 17;
    int choice;

    printf("Welcome to Battleship!\n");
    printf("1. New Game\n2. Load Game\n3. View High Scores\nChoice: ");
    scanf("%d", &choice);

    if (choice == 2) {
        if (!load_game_state(&player, &computer)) {
            printf("No saved game found. Starting new game.\n");
            choice = 1;
        } else {
            printf("Game loaded! Welcome back, %s.\n", player.name);
        }
    } else if (choice == 3) {
        load_high_scores();
        return 0;
    }

    if (choice == 1) {
        printf("Enter your name: ");
        scanf("%s", player.name);
        init_board(player.board);
        init_board(player.tracking_board);
        init_board(computer.board);
        place_ships_randomly(player.board);
        place_ships_randomly(computer.board);
        player.score = 0;
        player.total_hits = 0;
        player.total_misses = 0;
        computer.total_hits = 0;
    }

    while (player.total_hits < total_ship_cells && computer.total_hits < total_ship_cells) {
        printf("\n--- Your Board ---\n");
        display_board(player.board, 0);
        printf("\n--- Tracking Board (Enemy) ---\n");
        display_board(player.tracking_board, 0);

        printf("\nEnter coordinates (row col) or -1 -1 to save and quit: ");
        if (scanf("%d %d", &row, &col) != 2) {
            printf("Invalid input.\n");
            while (getchar() != '\n');
            continue;
        }

        if (row == -1 && col == -1) {
            save_game_state(&player, &computer);
            return 0;
        }

        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
            printf("Out of bounds!\n");
            continue;
        }

        result = process_shot(computer.board, row, col);
        if (result == 1) {
            printf("HIT!\n");
            player.tracking_board[row][col] = HIT;
            player.total_hits++;
            player.score += 10;
        } else if (result == 0) {
            printf("MISS!\n");
            player.tracking_board[row][col] = MISS;
            player.total_misses++;
        } else {
            printf("Already fired there!\n");
            continue;
        }

        if (player.total_hits == total_ship_cells) break;

        // Computer's turn
        int c_row, c_col;
        do {
            c_row = rand() % BOARD_SIZE;
            c_col = rand() % BOARD_SIZE;
            result = process_shot(player.board, c_row, c_col);
        } while (result == -1);

        printf("Computer fired at %d %d: %s\n", c_row, c_col, result == 1 ? "HIT" : "MISS");
        if (result == 1) computer.total_hits++;
    }

    if (player.total_hits == total_ship_cells) {
        printf("\nCONGRATULATIONS! You won!\n");
    } else {
        printf("\nGAME OVER. Computer won.\n");
    }

    save_high_score(&player);
    load_high_scores();

    return 0;
}
