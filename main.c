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
// Change values below to rezise game board. 
// for example 1920 / 10 yields 192 cells.. in X-axis... and so on. 
#define X 99         // 198 * 20 = 1920.
#define Y 54         // 108 * 20 = 1080.
#define CELL_SIZE 20 // 20*99 = 1920, 20*54 = 1080, this correspond to X and Y. 

bool underPopulation(char[X][Y], int, int);
bool overPopulation(char[X][Y], int, int);
bool populate(char[X][Y], int, int);
bool startSimulation(char[X][Y]);
bool endSimulation(char[X][Y]);  
void displayMessage(bool);
void startState(char[X][Y]);
void drawGrid(char[X][Y]);
void endState(char[X][Y]);

int main() {
    // Set initial screen size and title. 
    const int width = 1920, heigth = 1080;
    const char* title = "Game of Life";
    
    // Stores grid data. 
    char grid[X][Y];

    // Start up mode. 	
    bool startUpMode = true; 
    
    // Animation timer.	
    float timer = 0.0f;

    // Init screen and set fullscreen property. 
    InitWindow(width, heigth, title);
    
    // Fullscreen mode and framerate settings. 
    ToggleFullscreen();
    SetTargetFPS(60); 

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
           
            displayMessage(startUpMode);

            if(startUpMode == true) 
                startUpMode = startSimulation(grid); 
            else 
                startUpMode = endSimulation(grid);


            if(startUpMode == false) {
                // When no longer in start up mode: 
                // 1. get start state.
                // 2. draw with an animation timer of 0.4f.
                // 3. draw and get end state, reset timer.
                startState(grid);
                if(timer <= 0.4f) { 
                    drawGrid(grid);
                    timer += GetFrameTime();
                }
                else {
                    drawGrid(grid);
                    endState(grid);
                    timer = 0; 
                }
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
    int posX = 0, posY = 0; 		                  // Square posistion.
    const int width = CELL_SIZE, heigth = CELL_SIZE;  // Square size. 
    
    // Draw squares, with color dependant of game state(DEAD/LIVING). 	
    for(int i = 0; i < X; ++i) {
        for(int j = 0; j < Y; ++j) {
            if(grid[i][j] == LIVING) 
                DrawRectangleLines(posY, posX, width, heigth, GREEN);
                
            posX += CELL_SIZE; // Next x line.
        }
        posY += CELL_SIZE; // Next y line.
        posX = 0;   // Reset.
    }
    return;
}

void displayMessage(bool startUpMode) {
    
    if(startUpMode == true) // If in start up mode. 
        DrawText("Use left mouse button to create a start pattern.\nPress ENTER to start the simulation or hit the ESC button to exit.", 10, 10, 20, GREEN); 
    else                    // When simulation is running.
        DrawText("Press ENTER to create a new start pattern or hit the ESC button to exit.", 10, 10, 20, GREEN);

    return; 
}

bool startSimulation(char grid[X][Y]) {
    // Cell grid data: 
    // X: 1980  Y: 1080
    // A cell is 10px (height,width)

    // Check if left mouse button is down(being clicked) LEFT to create and RIGHT to remove. 
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        
        // Get mouse x and y pos and check values against i and j which correspond to 1980, 1080. 
        Vector2 mousePos = GetMousePosition(); 
        for(int i = 0; i < X * CELL_SIZE; i += CELL_SIZE) {
            if(i > mousePos.x - CELL_SIZE) {
                for(int j = 0; j < Y * CELL_SIZE; j += CELL_SIZE) {
                    if(j > mousePos.y - CELL_SIZE) {
                        if(grid[i/CELL_SIZE][j/CELL_SIZE] == DEAD)  // If a "clicked" cell is dead set it to alive. 
                            grid[i/CELL_SIZE][j/CELL_SIZE] = LIVING;  
                        
                        goto done;
                    }
                }
            }
        }
    }
    else if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        // Get mouse x and y pos and check values against i and j which correspond to 1980, 1080. 
        Vector2 mousePos = GetMousePosition(); 
        for(int i = 0; i < X * CELL_SIZE; i += CELL_SIZE) {
            if(i > mousePos.x - CELL_SIZE) {
                for(int j = 0; j < Y * CELL_SIZE; j += CELL_SIZE) {
                    if(j > mousePos.y - CELL_SIZE) {
                        if(grid[i/CELL_SIZE][j/CELL_SIZE] == LIVING)  // If a "clicked" cell is alive set it to dead. 
                            grid[i/CELL_SIZE][j/CELL_SIZE] = DEAD;
                        
                        goto done;
                    }
                }
            }
        }
    }

    done: 

    // refresh grid. 
    drawGrid(grid); 

    // Exit call. 
    if(IsKeyPressed(KEY_ENTER)) 
        return false;

    return true; 
}

bool endSimulation(char grid[X][Y]) {
    // Exit call. 
    if(IsKeyPressed(KEY_ENTER)) {
        // Reset grid. 
        for(int i = 0; i < X; ++i) {
            for(int j = 0; j < Y; ++j) 
                grid[i][j] = DEAD;  
        }
        return true;
    }
    else
        return false; 
}

