/*
Created by Oscar Bergström.
Last edited 0222-03-07.
*/

#include <iostream>
#include <time.h>

#define BORN 'o'
#define LIVING 'O'
#define DYING 'x'
#define DEAD ' '
#define BOARD_Y 50
#define BOARD_X 100

void printGrid(char[BOARD_Y][BOARD_X]);
bool solitude(char[BOARD_Y][BOARD_X], int, int);
bool overpopulated(char[BOARD_Y][BOARD_X], int, int);
bool populate(char[BOARD_Y][BOARD_X], int, int);

int main() { 
	char grid[BOARD_Y][BOARD_X];
	bool is_running = true;

	// Set state of all cells to dead.
	for (int i = 0; i < BOARD_Y; i++)
		for (int n = 0; n < BOARD_X; n++) grid[i][n] = DEAD;

	srand(time(NULL));
	int x, y;
	for (int i = 0; i < 200; i++) {
		x = rand() % 90 + 10;
		y = rand() % 40 + 10;
		grid[y][x] = LIVING;
	}


	// Run and check each grid before end of each state!
	while(is_running) {
		for (int i = 0; i < BOARD_Y; i++)
			for (int n = 0; n < BOARD_X; n++) {
				if (grid[i][n] == BORN) grid[i][n] = LIVING;
				if (grid[i][n] == DYING) grid[i][n] = DEAD;
				
				// Kill all that approache the end of the universe. 
				if (i == 0 ||i == BOARD_Y - 1) grid[i][n] = DEAD;
				if (n == 0 || n == BOARD_X - 1) grid[i][n] = DEAD;
			}
		printGrid(grid);

		for (int i = 0; i < BOARD_Y; i++) {
			for (int n = 0; n < BOARD_X; n++) {
				if (grid[i][n] == LIVING) {
					if (solitude(grid, i, n) == true) grid[i][n] = DYING;
					if (overpopulated(grid, i, n) == true) grid[i][n] = DYING;
				}
				if (grid[i][n] == ' ')
						if (populate(grid, i, n) == true) grid[i][n] = BORN;
			}
		}
	}
	
	return 0; 
}
void printGrid(char grid[BOARD_Y][BOARD_X]) {
	for (int i = 0; i < BOARD_Y; i++)
		for (int n = 0; n < BOARD_X; n++) {
			printf("%c", grid[i][n]);
			if(n == BOARD_X - 1) printf("\n");
		}

	system("cls");

	return;
}

bool solitude(char grid[BOARD_Y][BOARD_X], int y, int x) {
	// If no neighbor is connected to a cell it will die of solituded.
	int counter = 0; 

	if (grid[y - 1][x] != DEAD && grid[y - 1][x] != BORN) counter++;
	if (grid[y - 1][x + 1] != DEAD && grid[y - 1][x + 1] != BORN) counter++;
	if (grid[y][x + 1] != DEAD && grid[y][x + 1] != BORN) counter++;
	if (grid[y + 1][x + 1] != DEAD && grid[y + 1][x + 1] != BORN) counter++;
	if (grid[y + 1][x] != DEAD && grid[y + 1][x] != BORN) counter++;
	if (grid[y + 1][x - 1] != DEAD && grid[y + 1][x - 1] != BORN) counter++;
	if (grid[y][x - 1] != DEAD && grid[y][x - 1] != BORN) counter++;
	if (grid[y - 1][x - 1] != DEAD && grid[y + 1][x - 1] != BORN) counter++;
	
	if (counter == 0 || counter == 1) return true;
	else return false;
}

bool overpopulated(char grid[BOARD_Y][BOARD_X], int y, int x) {
	// If a cell is connected to four or more neighbors it will die from overpopulation. 
	int counter = 0; 

	if (grid[y - 1][x] == LIVING || grid[y - 1][x] == DYING) counter++;
	if (grid[y - 1][x + 1] == LIVING || grid[y - 1][x + 1] == DYING) counter++;
	if (grid[y][x + 1] == LIVING || grid[y][x + 1] == DYING) counter++;
	if (grid[y + 1][x + 1] == LIVING || grid[y + 1][x + 1] == DYING) counter++;
	if (grid[y + 1][x] == LIVING || grid[y + 1][x] == DYING) counter++;
	if (grid[y + 1][x - 1] == LIVING || grid[y + 1][x - 1] == DYING) counter++;
	if (grid[y][x - 1] == LIVING || grid[y][x - 1] == DYING) counter++;
	if (grid[y - 1][x - 1] == LIVING || grid[y - 1][x - 1] == DYING) counter++;

	if (counter >= 4) return true;
	else return false;
}

bool populate (char grid[BOARD_Y][BOARD_X], int y, int x) {
	// If a cell has three neighbors it becomes populated.
	int counter = 0;

	if (grid[y - 1][x] == LIVING || grid[y - 1][x] == DYING) counter++;
	if (grid[y - 1][x + 1] == LIVING || grid[y - 1][x + 1] == DYING) counter++;
	if (grid[y][x + 1] == LIVING || grid[y][x + 1] == DYING) counter++;
	if (grid[y + 1][x + 1] == LIVING || grid[y + 1][x + 1] == DYING) counter++;
	if (grid[y + 1][x] == LIVING || grid[y + 1][x] == DYING) counter++;
	if (grid[y + 1][x - 1] == LIVING || grid[y + 1][x - 1] == DYING) counter++;
	if (grid[y][x - 1] == LIVING || grid[y][x - 1] == DYING) counter++;
	if (grid[y - 1][x - 1] == LIVING || grid[y - 1][x - 1] == DYING) counter++;

	if (counter == 3) return true;
	else return false;
}
