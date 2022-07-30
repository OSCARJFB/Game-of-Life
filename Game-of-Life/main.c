/*
 *	Created by Oscar Bergström.
 *	Last edited 2022-07-29.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "raylib.h"

// Definition of life death .. and unofficial midstates. 
#define BORN 'o'
#define LIVING 'O'
#define DYING 'x'
#define DEAD ' '

// Game grid, should be = 1920x1080. 
#define X 198 // 198 * 10 = 1920
#define Y 108 // 108 * 10 = 1080

bool underPopulation(char[X][Y], int, int);
bool overPopulation(char[X][Y], int, int);
bool populate(char[X][Y], int, int);
bool cell_mouseClick(char[X][Y]); 
void startState(char[X][Y]);
void drawGrid(char[X][Y]);
void endState(char[X][Y]);

int main() {
    // Set initial screen size and title. 
    const int width = 1920, heigth = 1080;
    const char* title = "Game of Life";
    
    // Stores grid data. 
    char grid[X][Y];

    bool startUpMode = true; 

    // Init screen and set fullscreen property. 
    InitWindow(width, heigth, title);
    
    // Fullscreen mode and framerate settings. 
    ToggleFullscreen();
    SetTargetFPS(5); 

    // At the begining set all cells status to dead. 
    for(int i = 0; i < X; ++i) {
        for(int j = 0; j < Y; ++j) 
            grid[i][j] = DEAD;  
    }

    // Loop until close button/ESC button has been pressed.
    while (!WindowShouldClose()) {

        // Draw graphics. 
        BeginDrawing();

            // Clear and set a black background. 
            ClearBackground(BLACK);
            
            if(startUpMode == true) {
                startUpMode = cell_mouseClick(grid); 
            }

            // Start -> draw -> end.
            if(startUpMode == false) {
                startState(grid);
                drawGrid(grid);
                endState(grid);
            } 

        // Stop drawing. 
        EndDrawing();
    }

    CloseWindow();     

    return 0;
}
void startState(char grid[X][Y]) {
    // Check each grid before start of a state.
    for (int i = 0; i < X; ++i) {
        for (int j = 0; j < Y; ++j) {
            if (grid[i][j] == BORN) grid[i][j] = LIVING;
            if (grid[i][j] == DYING) grid[i][j] = DEAD;
            
            // Kill all live cells that approache the end of the universe. 
            if (i == 0 ||i == X - 1) grid[i][j] = DEAD;
            if (j == 0 || j == Y - 1) grid[i][j] = DEAD;
        }
    }

    return; 
}

void endState(char grid[X][Y]) {
    // Check each grid status at the end of a state.
    for (int i = 0; i < X; ++i) {
        for (int j = 0; j < Y; ++j) {
            if (grid[i][j] == ' ')
                    if (populate(grid, i, j) == true) grid[i][j] = BORN;
            if (grid[i][j] == LIVING) {
                if (underPopulation(grid, i, j) == true) grid[i][j] = DYING;
                if (overPopulation(grid, i, j) == true) grid[i][j] = DYING;
            }
        }
    }

    return; 
}
bool underPopulation(char grid[X][Y], int y, int x) {
	// Any live cell connected to fewer than two neighbouring live cells will die of underpopulation.
	int counter = 0; 

	if (grid[y - 1][x] == LIVING || grid[y - 1][x] == DYING) counter++;
	if (grid[y - 1][x + 1] == LIVING || grid[y - 1][x + 1] == DYING) counter++;
	if (grid[y][x + 1] == LIVING || grid[y][x + 1] == DYING) counter++;
	if (grid[y + 1][x + 1] == LIVING || grid[y + 1][x + 1] == DYING) counter++;
	if (grid[y + 1][x] == LIVING || grid[y + 1][x] == DYING) counter++;
	if (grid[y + 1][x - 1] == LIVING || grid[y + 1][x - 1] == DYING) counter++;
	if (grid[y][x - 1] == LIVING || grid[y][x - 1] == DYING) counter++;
	if (grid[y - 1][x - 1] == LIVING || grid[y - 1][x - 1] == DYING) counter++;

	if (counter < 2) return true;
	else return false;
}

bool overPopulation(char grid[X][Y], int y, int x) {
	// Any live cell connected to more than three other live cells die of overpopulation. 
	int counter = 0; 

	if (grid[y - 1][x] == LIVING || grid[y - 1][x] == DYING) counter++;
	if (grid[y - 1][x + 1] == LIVING || grid[y - 1][x + 1] == DYING) counter++;
	if (grid[y][x + 1] == LIVING || grid[y][x + 1] == DYING) counter++;
	if (grid[y + 1][x + 1] == LIVING || grid[y + 1][x + 1] == DYING) counter++;
	if (grid[y + 1][x] == LIVING || grid[y + 1][x] == DYING) counter++;
	if (grid[y + 1][x - 1] == LIVING || grid[y + 1][x - 1] == DYING) counter++;
	if (grid[y][x - 1] == LIVING || grid[y][x - 1] == DYING) counter++;
	if (grid[y - 1][x - 1] == LIVING || grid[y - 1][x - 1] == DYING) counter++;

	if (counter > 3) return true;
	else return false;
}

bool populate (char grid[X][Y], int y, int x) {
	// If a dead cell has three live neighbors it becomes populated.
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
    int posX = 0, posY = 0; 		    // Square posistion.
    const int width = 10, heigth = 10;  // Square size. 
    
    // Draw squares, with color dependant of game state(DEAD/LIVING). 	
    for(int i = 0; i < X; ++i) {
        for(int j = 0; j < Y; ++j) {
            if(grid[i][j] == LIVING) 
                DrawRectangleLines(posY, posX, width, heigth, GREEN);
                
            posX += 10; // Next x line.
        }
        posY += 10; // Next y line.
        posX = 0;   // Reset.
    }
    return;
}

bool cell_mouseClick(char grid[X][Y]) {
    // Cell grid data: 
    // X: 1980  Y: 1080
    // A cell is 10px (height,width)

    // Check if left mouse button is down(being clicked). 
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        
        // Get mouse x and y pos and check values against i and j which correspond to 1980, 1080. 
        Vector2 mousePos = GetMousePosition(); 
        for(int i = 0; i < X * 10; i += 10) {
            if(i > mousePos.x - 10) {
                for(int j = 0; j < Y * 10; j += 10) {
                    if(j > mousePos.y - 10) {
                        grid[i/10][j/10] = LIVING; 
                        goto done;
                    }
                }
            }
        }
    }

    done: 

    // refresh grid. 
    drawGrid(grid); 

    // Exit call selection. 
    if(IsKeyPressed(KEY_ENTER)) 
        return false;

    return true; 
}

