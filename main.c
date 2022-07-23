/*
	Created by Oscar Bergström.
	Last edited 2022-07-23.
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

// This correspond to a grid of 1920x1080. 
#define X 198 // 198 * 10 = 1920
#define Y 108 // 108 * 10 = 1080

bool underPopulation(char[X][Y], int, int);
bool overPopulation(char[X][Y], int, int);
bool populate(char[X][Y], int, int);
void drawGrid(char[X][Y]);
void setStartStage(char[X][Y]);
void glider(char[X][Y]);
void blinker(char[X][Y]);
void pattern_one(char[X][Y]);
void pattern_two(char[X][Y]);

int main() {
    // Set initial screen size and title. 
    const int width = 1920, heigth = 1080;
    const char* title = "Game of Life";

    
    // Init screen and set fullscreen property. 
    InitWindow(width, heigth, title);
    
    ToggleFullscreen();

    SetTargetFPS(5);      

    char grid[X][Y];

    setStartStage(grid);

    // Loop until close button/ESC button has been pressed.
    while (!WindowShouldClose()) {
        // Draw graphics. 
        BeginDrawing();
        
        // Clear and set a black background. 
        ClearBackground(BLACK);


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
                if (grid[i][j] == ' ')
                        if (populate(grid, i, j) == true) grid[i][j] = BORN;
                if (grid[i][j] == LIVING) {
                    if (underPopulation(grid, i, j) == true) grid[i][j] = DYING;
                    if (overPopulation(grid, i, j) == true) grid[i][j] = DYING;
                }
            }
        }

        drawGrid(grid);
        
        // Stop drawing. 
        EndDrawing();
    }

    CloseWindow();     

    return 0;
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

void setStartStage(char grid[X][Y]) {
    int num_gliders = 0, num_blinkers = 0;
    int state = 0; 

    // Set state of all cells to dead.
    for (int i = 0; i < X; i++)
        for (int n = 0; n < Y; n++) grid[i][n] = DEAD;

    srand(time(NULL));
    state = rand() % 3 + 1; 

    if(state == 1) {
        num_gliders = rand() % 10 + 1;  // Amount of gliders.
        num_blinkers = rand() % 10 + 1; // Amount of blinkers.
        
        for(int i = 0; i < num_gliders; ++i)
            glider(grid);

        for(int i = 0; i < num_blinkers; ++i)
            blinker(grid);
    }
    else if(state == 2) {
        pattern_one(grid);
    }
    else if(state == 3) {
        pattern_two(grid);
    }

    return;
}

void glider(char grid[X][Y]) {
    // This will create a simple glider, at a random location. 
    int x = rand() % 180+ 10;
    int y = rand() % 90 + 10;

    grid[x][y] = LIVING;
    grid[x + 1][y] = LIVING;
    grid[x + 2][y] = LIVING;
    grid[x + 2][y - 1] = LIVING;
    grid[x + 1][y - 2] = LIVING;

    return;
}
void blinker(char grid[X][Y]) {
    // This will create a simple blinker, at a random location. 
    int x = rand() % 180+ 10;
    int y = rand() % 90 + 10;

    grid[x][y] = LIVING;
    grid[x + 1][y] = LIVING;
    grid[x + 2][y] = LIVING;

    return;
}

void pattern_one(char grid[X][Y]) {
    grid[100][50] = LIVING;
    grid[101][50] = LIVING;
    grid[102][50] = LIVING;
    grid[103][50] = LIVING;
    grid[104][50] = LIVING;
    grid[105][50] = LIVING;
    grid[106][50] = LIVING;
    grid[107][50] = LIVING;

    // 1 dead cell

    grid[109][50] = LIVING;
    grid[110][50] = LIVING;
    grid[111][50] = LIVING;
    grid[112][50] = LIVING;
    grid[113][50] = LIVING;

    // 3 dead cells
    
    grid[116][50] = LIVING;
    grid[117][50] = LIVING;
    grid[118][50] = LIVING;

    // 6 dead cells. 

    grid[123][50] = LIVING;
    grid[124][50] = LIVING;
    grid[125][50] = LIVING;
    grid[126][50] = LIVING;
    grid[127][50] = LIVING;
    grid[128][50] = LIVING;
    grid[129][50] = LIVING;

    // 1 dead cell. 

    grid[131][50] = LIVING;
    grid[132][50] = LIVING;
    grid[133][50] = LIVING;
    grid[134][50] = LIVING;
    grid[135][50] = LIVING;

    return;
}
void pattern_two(char grid[X][Y]) {
    grid[100][50] = LIVING;
    grid[101][50] = LIVING;
    grid[102][50] = LIVING;
    grid[104][50] = LIVING; 
    
    // Next line.

    grid[100][51] = LIVING;

    // Next line.

    grid[103][52] = LIVING; 
    grid[104][52] = LIVING; 

    // Next line.

    grid[101][53] = LIVING;
    grid[102][53] = LIVING;
    grid[104][53] = LIVING;

    // Next line.

    grid[100][54] = LIVING;
    grid[102][54] = LIVING;
    grid[104][54] = LIVING;

    return; 
}