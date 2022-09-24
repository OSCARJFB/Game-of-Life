/*
 *	Author: Oscar Bergström.
 *	Last edited 2022-09-24.
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

#define X 99         
#define Y 54         
#define CELL_SIZE 20 

bool underPopulation(char[X][Y], int, int);
bool overPopulation(char[X][Y], int, int);
bool populate(char[X][Y], int, int);
bool startSimulation(char[X][Y]);
bool endSimulation(char[X][Y]);  
void displayMessage(bool);
void startState(char[X][Y]);
void drawGrid(char[X][Y]);
void endState(char[X][Y]);

int main() 
{
    // Set initial screen size and title. 
    const int width = 1920, heigth = 1080;
    const char* title = "Game of Life";
    
    // Stores grid data. 
    char grid[X][Y];

    // While this true the creation of a start pattern is enabled. 
    bool startUpMode = true; 
    
    // Refresh rate of grid animation. 
    float animation_timer = 0.0f;
    
    // Fullscreen mode and framerate settings. 
    InitWindow(width, heigth, title);
    ToggleFullscreen();
    SetTargetFPS(60); 

    // At the begining set all cells status to dead. 
    for(int i = 0; i < X; ++i) 
    {
        for(int j = 0; j < Y; ++j) 
            grid[i][j] = DEAD;  
    }

    // Loop until close button/ESC button has been pressed.
    while (!WindowShouldClose()) 
    {

        // Draw graphics. 
        BeginDrawing();

            // Clear and set a black background. 
            ClearBackground(BLACK);
           
            displayMessage(startUpMode);

            if(startUpMode == true) 
                startUpMode = startSimulation(grid); 
            else 
                startUpMode = endSimulation(grid);

            if(startUpMode == false) 
	    {
                // When no longer in start up mode: 
                // 1. get start state.
                // 2. draw with an animation animation_timer of 0.4f.
                // 3. draw, get end state and reset animation_timer.
                startState(grid);
                if(animation_timer <= 0.4f) 
		{ 
                    drawGrid(grid);
                    animation_timer += GetFrameTime();
                }
                else 
		{
                    drawGrid(grid);
                    endState(grid);
                    animation_timer = 0; 
                }
            }

        // Stop drawing. 
        EndDrawing();
    }

    CloseWindow();     

    return 0;
}
void startState(char grid[X][Y]) 
{
    // Check each grid before start of a state.
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

void endState(char grid[X][Y]) 
{
    // Check each grid status at the end of a state.
    for (int i = 0; i < X; ++i) 
    {
        for (int j = 0; j < Y; ++j) 
	{
            if (grid[i][j] == ' ')
                    if (populate(grid, i, j) == true) grid[i][j] = BORN;
            if (grid[i][j] == LIVING) 
	    {
                if (underPopulation(grid, i, j) == true) grid[i][j] = DYING;
                if (overPopulation(grid, i, j) == true) grid[i][j] = DYING;
            }
        }
    }

    return; 
}
bool underPopulation(char grid[X][Y], int y, int x) 
{
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

bool overPopulation(char grid[X][Y], int y, int x) 
{
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

bool populate (char grid[X][Y], int y, int x) 
{
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

void drawGrid(char grid[X][Y]) 
{
    int posX = 0, posY = 0; 		              // Square posistion.
    const int width = CELL_SIZE, heigth = CELL_SIZE;  // Square size. 
    
    // Draw squares, with color dependant of game state(DEAD/LIVING). 	
    for(int i = 0; i < X; ++i) 
    {
        for(int j = 0; j < Y; ++j) 
	{
            if(grid[i][j] == LIVING) 
                DrawRectangle(posY, posX, width - 1, heigth - 1, GREEN);
            else 
                DrawRectangleLines(posY, posX, width, heigth, (Color) {30, 40, 55, 66});
                
            posX += CELL_SIZE; // Next x line.
        }
        posY += CELL_SIZE;     // Next y line.
        posX = 0;              // Reset.
    }
    return;
}

void displayMessage(bool startUpMode) 
{

    const char info_message [] = "IN START UP MODE: \n" 
                                 "A LEFT CLICK WILL set cell state to LIVING. \n"
                                 "A RIGHT CLICK will set cell state to DEAD. \n"
                                 "press ENTER to start the simulation. \n\n"
                                 "IN RUN MODE: \n"
                                 "press ENTER to reset and stop the simulation. \n\n"
                                 "IN ANY MODE: \n"
                                 "press ESC to exit. \n";
   
   const char regular_message[] = "Press and hold the i key for info!"; 

    if(IsKeyDown(KEY_I)) { // If i Key is being pressed. 
        DrawText(info_message, 10, 10, 20, GREEN); 
        if(startUpMode == true) 
            DrawText("Current mode: start up", 10, 330, 20, GREEN); 
        else
            DrawText("Current mode: Running", 10, 330, 20, GREEN);  
    }
    else                   // if no key is being pressed. 
        DrawText(regular_message, 10, 10, 20, GREEN); 

    return; 
}

bool startSimulation(char grid[X][Y]) 
{
    // Cell grid data: 
    // X: 1980  Y: 1080
    // A cell is 10px (height,width)

    // Check if left mouse button is down(being clicked) LEFT to create and RIGHT to remove. 
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) 
    {
        
        // Get mouse x and y pos and check values against i and j which correspond to 1980, 1080. 
        Vector2 mousePos = GetMousePosition(); 
        for(int i = 0; i < X * CELL_SIZE; i += CELL_SIZE) 
	{
            if(i > mousePos.x - CELL_SIZE) 
	    {
                for(int j = 0; j < Y * CELL_SIZE; j += CELL_SIZE) 
		{
                    if(j > mousePos.y - CELL_SIZE) 
		    {
                        if(grid[i/CELL_SIZE][j/CELL_SIZE] == DEAD)  // If a "clicked" cell is dead set it to alive. 
                            grid[i/CELL_SIZE][j/CELL_SIZE] = LIVING;  
                        
                        goto done;
                    }
                }
            }
        }
    }
    else if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) 
    {
        // Get mouse x and y pos and check values against i and j which correspond to 1980, 1080. 
        Vector2 mousePos = GetMousePosition(); 
        for(int i = 0; i < X * CELL_SIZE; i += CELL_SIZE) 
	{
            if(i > mousePos.x - CELL_SIZE) 
	    {
                for(int j = 0; j < Y * CELL_SIZE; j += CELL_SIZE) 
		{
                    if(j > mousePos.y - CELL_SIZE) 
		    {
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

bool endSimulation(char grid[X][Y]) 
{
    // Exit call. 
    if(IsKeyPressed(KEY_ENTER)) 
    {
        // Reset grid. 
        for(int i = 0; i < X; ++i) 
	{
            for(int j = 0; j < Y; ++j) 
                grid[i][j] = DEAD;  
        }
        return true;
    }
    else
        return false; 
}

