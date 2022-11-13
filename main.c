/*
 *	Created by Oscar Bergström.
 *	Last edited 2022-11-13.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "raylib.h"

// Cell states.
#define BORN 'o'
#define LIVING 'O'
#define DYING 'x'
#define DEAD ' '

#define CELL_SIZE 20
#define X 90      
#define Y 90     

void windowSetup();
void runGame();
bool underPopulation(char[X][Y], int, int);
bool overPopulation(char[X][Y], int, int);
bool populate(char[X][Y], int, int);
bool startSimulation(char[X][Y]);
bool endSimulation(char[X][Y]);  
void displayMessage(bool);
void newStage(char[X][Y]);
void drawStage(char[X][Y]);
void endStage(char[X][Y]);

int main() {
    windowSetup();
    runGame();

    return 0;
}

void windowSetup()
{
    // Init screen and set window to fullscreen property. 
    const int width = GetScreenWidth(), heigth = GetScreenHeight();
    const char* title = "Game of Life";

    InitWindow(width, heigth, title);
    ToggleFullscreen();
    SetTargetFPS(60); 
}

void runGame()
{
    bool startUpMode = true; 
    float animation_timer = 0.0f;

    char grid[X][Y];

    // At the begining set all cells status to dead. 
    for(int i = 0; i < X; ++i) 
    {
        for(int j = 0; j < Y; ++j) 
        {
            grid[i][j] = DEAD;
        }
    }

    // Loop until close button/ESC button has been pressed.
    while (!WindowShouldClose()) 
    {


        BeginDrawing();

            ClearBackground(BLACK);
            
            displayMessage(startUpMode);

            startUpMode = startUpMode == true ? startSimulation(grid) : endSimulation(grid);

            if(!startUpMode) 
            {
                newStage(grid);
                
                if(animation_timer <= 0.4f) 
                { 
                    drawStage(grid);
                    animation_timer += GetFrameTime();
                }
                else {
                    endStage(grid);
                    animation_timer = 0; 
                }
            }

        EndDrawing();
    }

    CloseWindow();     
}

void newStage(char grid[X][Y]) 
{
    // Check each grid before start of a new state.
    for (int i = 0; i < X; ++i) 
    {
        for (int j = 0; j < Y; ++j) 
        {
            if (grid[i][j] == BORN) grid[i][j] = LIVING;
            if (grid[i][j] == DYING) grid[i][j] = DEAD;
            
            // Kill all live cells that approache the end of the universe. 
            if (i == 0 ||i == X - 1) grid[i][j] = DEAD;
            if (j == 0 || j == Y - 1) grid[i][j] = DEAD;
        }
    }

    return; 
}

void endStage(char grid[X][Y]) 
{
    // Check and update the status of each cell at the end of a state.
    for (int i = 0; i < X; ++i) 
    {
        for (int j = 0; j < Y; ++j) 
        {
            if (grid[i][j] == ' ')
            {
                if (populate(grid, i, j)) grid[i][j] = BORN;
            }
            if (grid[i][j] == LIVING) 
            {
                if (underPopulation(grid, i, j)) 
                {
                    grid[i][j] = DYING;
                }

                if (overPopulation(grid, i, j)) 
                {
                    grid[i][j] = DYING;
                }
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

void drawStage(char grid[X][Y]) {
    int posX = 0, posY = 0; 		                  // Square posistion.
    const int width = CELL_SIZE, heigth = CELL_SIZE;  // Square size. 
    
    // Draw squares, with color dependant of game state(DEAD/LIVING). 	
    for(int i = 0; i < X; ++i) {
        for(int j = 0; j < Y; ++j) {
            if(grid[i][j] == LIVING) 
                //DrawRectangleLines(posY, posX, width, heigth, GREEN);
                DrawRectangle(posY, posX, width - 1, heigth - 1, GREEN);
            else 
                DrawRectangleLines(posY, posX, width, heigth, (Color) {30, 40, 55, 66});


                
            posX += CELL_SIZE; // Next x line.
        }
        posY += CELL_SIZE; // Next y line.
        posX = 0;   // Reset.
    }
    return;
}

void displayMessage(bool startUpMode) {

    const char info_message [] = "IN START UP MODE: \n" 
                                 "A LEFT CLICK WILL set cell state to LIVING. \n"
                                 "A RIGHT CLICK will set cell state to DEAD. \n"
                                 "press ENTER to start the simulation. \n\n"
                                 "IN RUN MODE: \n"
                                 "press ENTER to reset and stop the simulation. \n\n"
                                 "IN ANY MODE: \n"
                                 "press ESC to exit. \n";
   
   const char regular_message[] = "Press and hold the i key for info!"; 

    // Show / hide help message. 
    if(IsKeyDown(KEY_I)) { 
        
        DrawText(info_message, 10, 10, 20, GREEN); 
        
        if(startUpMode == true) 
        {
            DrawText("Current mode: start up", 10, 330, 20, GREEN); 
        }
        else
        {
            DrawText("Current mode: Running", 10, 330, 20, GREEN);  
        }
    }
    else 
        DrawText(regular_message, 10, 10, 20, GREEN); 

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
    drawStage(grid); 

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

