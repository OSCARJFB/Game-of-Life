/*
	Created by Oscar Bergström.
	Last edited 2022-07-21.
*/

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "raylib.h"

// Definition of life death .. and unofficial midstates. 
#define BORN 'o'
#define LIVING 'O'
#define DYING 'x'
#define DEAD ' '
#define D_KEY 100

// This correspond to a grid of 1920x1080. 
#define X 198 // 198 * 10 = 1920
#define Y 108 // 108 * 10 = 1080

bool solitude(char[X][Y], int, int);
bool overpopulated(char[X][Y], int, int);
bool populate(char[X][Y], int, int);
void startUpMode(char[X][Y]);
void drawGrid(char[X][Y]);

int main() {
    // Set initial screen size and title. 
    const int width = 1920, heigth = 1080;
    const char* title = "Game of Life";

    
    // Init screen and set fullscreen property. 
    InitWindow(width, heigth, title);
    
    ToggleFullscreen();

    SetTargetFPS(60);      

    char grid[X][Y];

    // Set state of all cells to dead.
    for (int i = 0; i < X; i++)
        for (int n = 0; n < Y; n++) grid[i][n] = DEAD;

    // Loop until close button/ESC button has been pressed.
    while (!WindowShouldClose()) {
        // Draw graphics. 
        BeginDrawing();
        
        // Clear and set a black background. 
        ClearBackground(BLACK);

        //startUpMode(grid); 
        grid[100][51] = LIVING;
        grid[101][51] = LIVING;
        grid[102][53] = LIVING;
        grid[100][55] = LIVING;
        grid[100][56] = LIVING;
        grid[100][57] = LIVING;

        // Run and check each grid before end of each state!
        for (int i = 0; i < X; ++i)
            for (int j = 0; j < Y; ++j) {
                if (grid[i][j] == BORN) grid[i][j] = LIVING;
                if (grid[i][j] == DYING) grid[i][j] = DEAD;
                
                // Kill all that approache the end of the universe. 
                if (i == 0 ||i == X - 1) grid[i][j] = DEAD;
                if (j == 0 || j == Y - 1) grid[i][j] = DEAD;
            }

        drawGrid(grid);

        for (int i = 0; i < X; ++i) {
            for (int j = 0; j < Y; ++j) {
                if (grid[i][j] == LIVING) {
                    if (solitude(grid, i, j) == true) grid[i][j] = DYING;
                    if (overpopulated(grid, i, j) == true) grid[i][j] = DYING;
                }
                if (grid[i][j] == ' ')
                        if (populate(grid, i, j) == true) grid[i][j] = BORN;
            }
        }
        
        // Stop drawing. 
        EndDrawing();
    }

    CloseWindow();     

    return 0;
}
bool solitude(char grid[X][Y], int y, int x) {
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

bool overpopulated(char grid[X][Y], int y, int x) {
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

bool populate (char grid[X][Y], int y, int x) {
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

void drawGrid(char grid[X][Y]) {
    int posX = 0, posY = 0; 		// Square posistion.
    const int width = 10, heigth = 10;  // Square size. 
    
    // Draw squares, with color dependant of game state(DEAD/LIVING). 	
    for(int i = 0; i < X; ++i) {
        for(int j = 0; j < Y; ++j) {
            if(grid[i][j] == LIVING)
                DrawRectangle(posY, posX, width, heigth, GREEN);
            else if(grid[i][j] == DEAD) 
                DrawRectangle(posY, posX, width, heigth, BLACK);
            
            posX += 10; // Next x line.
        }
        posY += 10; // Next y line.
        posX = 0;   // Reset.
    }
    return;
}

// This function is not in use yet!
void startUpMode(char grid[X][Y]) {
    int posX = 0, posY = 0;
    const int width = 10, heigth = 10; 

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

        for(int i = 0; i < X; ++i) {
            for(int j = 0; j < Y; ++j) {
                if(GetMouseX() > posX && GetMouseX() <= GetMouseX() + 10 &&
                    GetMouseY() > posX && GetMouseY() <= GetMouseY() + 10 ) {
                        DrawRectangle(posY, posX, width, heigth, GREEN);
                        drawGrid(grid);
                    }
    
                posX += 10;
            }
            posY += 10; // Next y line.
            posX = 0;   // Reset.
        }

    }
}


