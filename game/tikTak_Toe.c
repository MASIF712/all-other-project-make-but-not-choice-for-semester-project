// Tic Tac Toe in C. V1.0 by James 26/05/2019

// This is my first bigger C project. It was actually a lot easier than a I
// thought it would be! It's not great, but it works perfectly decently.

// I started working on it sometime around 4 in the morning, and I'm done before
// 7 in the morning. So I didn't spend much time on it.

// Also, I can't really claim I did the check function myself, though. The first time
// I ever made tic tac toe (in C#), I ended up writing looping functions which could
// check any size tic tac toe board, but I saw this current easier hard-coded solution
// that just checks the cases of a 3x3 board in someone else's implementation of
// the game. So I'm not sure I can take credit for it.

// I think I thought about hard-coding it the first time I made tic-tac-toe, but I
// thought there would be too many cases, it seems that there wasn't too many, though.

// Also, I reasise I probably could've used 2d arrays, but I wanted to try it without,
// since if you hadn't heard of a 2d array, you probably wouldn't be using them.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 3

// Draws the board along with rows/cols, numbered.
void draw_board(char board[])
{
	system("clear");
	printf("# 1 2 3\n");

	// Rows
	for (int i = 0, n = 0; i < SIZE; i++)
	{
		// Columns
		printf("%d ", i + 1);
		for (int j = 0; j < SIZE; j++)
		{
			printf("%c ", board[n]);
			n++;
		}
		printf("\n");
	}
}

// Initializes board to '-' characters.
void init_board(char board[])
{
	for (int i = 0; i <  SIZE * SIZE; i++)
	{
		board[i] = '-';
	}
}

// Returns true if the piece was successfully placed,
// false if the position was invalid or already taken.
bool place(char board[], char player)
{
	char posinput[64];

	printf("%c, pick your position (xy, rc): ", player);
	scanf("%s", posinput); // <-- I realise that this is potentially bad, but realistically, 
						   // the user would have to be trying to break something, and
	                       // this is just a little program I made for practice.

	int row = (posinput[0] - '0') - 1;
	int col = (posinput[1] - '0') - 1;

	int pos = col + row * SIZE;

	if (pos >= 0 && pos < SIZE * SIZE)
	{
		if (board[pos] == 'x' || board[pos] == 'o')
			return false;

		board[pos] = player;
		return true;
	}

	return false;
}

// Returns true if there are three of the same chars in a row.
// b = board, p = player. Shortened for readability.
bool check(char b[], char p) 
{
	// Check rows
	if (b[0] == p && b[1] == p && b[2] == p)
		return true;
	if (b[3] == p && b[4] == p && b[5] == p)
		return true;
	if (b[6] == p && b[7] == p && b[8] == p)
		return true;


	// Check columns
	if (b[0] == p && b[3] == p && b[6] == p)
		return true;
	if (b[1] == p && b[4] == p && b[7] == p)
		return true;
	if (b[2] == p && b[5] == p && b[8] == p)
		return true;


	// Check diagonals
	if (b[0] == p && b[4] == p && b[8] == p)
		return true;
	if (b[2] == p && b[4] == p && b[6] == p)
		return true;

	// If no one won, return false
	return false;
}

int main(void)
{
	char board[SIZE * SIZE];
	char player = 'x';
	init_board(board);

	while (true)
	{
		draw_board(board);
		
		if (place(board, player))
		{
			if (check(board, player))
				break;

			if (player == 'x')
				player = 'o';
			else
				player = 'x';
		}
	}

	draw_board(board);
	printf("-----------------------------\n");
	printf("Player %c wins!!!\n", player);
	printf("-----------------------------\n");
}