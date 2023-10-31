/*
	Writen by: Oscar Bergström
	https://github.com/OSCARJFB

	MIT License
	Copyright (c) 2023 Oscar Bergström
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <raylib.h>
#include <stdint.h>
#include "gameOfLife.h"

static inline bool underPopulation(char[X][Y], int, int);
static inline bool overPopulation(char[X][Y], int, int);
static inline bool populate(char[X][Y], int, int);
static bool startSimulation(char[X][Y]);
static bool endSimulation(char[X][Y]);
static void displayMessage(bool);
static void nextStage(char[X][Y]);
static void drawStage(char[X][Y]);
static void updateToNextStage(char[X][Y]);
static int countCells(char[X][Y], int, int);

/**
 * Raylib windows setup. 
 */
void windowSetup(void)
{
    const int width = GetScreenWidth(), heigth = GetScreenHeight();
    InitWindow(width, heigth, "Game of Life");
    ToggleFullscreen();
    SetTargetFPS(60);
}

/**
 * This is the main game loop. 
 */
void runGame(void)
{
    bool startUpMode = true;
    float timer = 0.0f;
    const float timer_limit = 0.4f;

    char grid[X][Y];

    // At the begining set all cells base status to dead.
    for (int i = 0; i < X; ++i)
    {
        for (int j = 0; j < Y; ++j)
        {
            grid[i][j] = DEAD;
        }
    }

    while (!WindowShouldClose())
    {

        BeginDrawing();

        ClearBackground(BLACK);

        displayMessage(startUpMode);
        startUpMode = startUpMode ? startSimulation(grid) : endSimulation(grid);

        if (!startUpMode)
        {
            nextStage(grid);

            if (timer <= timer_limit)
            {
                drawStage(grid);
                timer += GetFrameTime();
            }
            else
            {
                updateToNextStage(grid);
                timer = 0;
            }
        }

        EndDrawing();
    }

    CloseWindow();
}

/**
 * Set the next stage.
 */
static void nextStage(char grid[X][Y])
{
    // Check each grid before start of a new state.
    for (int i = 0; i < X; ++i)
    {
        for (int j = 0; j < Y; ++j)
        {
            if (grid[i][j] == BORN)
            {
                grid[i][j] = LIVING;
            }
            if (grid[i][j] == DYING)
            {
                grid[i][j] = DEAD;
            }

            // Kill all live cells that approache the end of the universe.
            if (i == 0 || i == X - 1)
            {
                grid[i][j] = DEAD;
            }
            if (j == 0 || j == Y - 1)
            {
                grid[i][j] = DEAD;
            }
        }
    }

    return;
}

/** 
 * Update statuses to next stage. 
 */
static void updateToNextStage(char grid[X][Y])
{
    for (int i = 0; i < X; ++i)
    {
        for (int j = 0; j < Y; ++j)
        {
            if (grid[i][j] == ' ')
            {
                if (populate(grid, i, j))
                {
                    grid[i][j] = BORN;
                }
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

/**
 * Check state for under population.
 */
static inline bool underPopulation(char grid[X][Y], int y, int x)
{
    // If a cell has less than two neighbours, the cell must die.
    int counted_cells = countCells(grid, y, x);
    return counted_cells < 2 ? true : false;
}

/**
 * Check state for over population.
 */
static inline bool overPopulation(char grid[X][Y], int y, int x)
{
    // Any live cell connected to more than three other live cells it will die of overpopulation.
    int counted_cells = countCells(grid, y, x);
    return counted_cells > 3 ? true : false;
}

/**
 * Check if to populate.
 */
static inline bool populate(char grid[X][Y], int y, int x)
{
    // If a dead cell has three live neighbors it becomes populated.
    int counted_cells = countCells(grid, y, x);
    return counted_cells == 3 ? true : false;
}

/**
 * Cell check. 
 */
static int countCells(char grid[X][Y], int y, int x)
{
    int counter = 0;

    if (grid[y - 1][x] == LIVING || grid[y - 1][x] == DYING)
    {
        ++counter;
    }
    if (grid[y - 1][x + 1] == LIVING || grid[y - 1][x + 1] == DYING)
    {
        ++counter;
    }
    if (grid[y][x + 1] == LIVING || grid[y][x + 1] == DYING)
    {
        ++counter;
    }
    if (grid[y + 1][x + 1] == LIVING || grid[y + 1][x + 1] == DYING)
    {
        ++counter;
    }
    if (grid[y + 1][x] == LIVING || grid[y + 1][x] == DYING)
    {
        ++counter;
    }
    if (grid[y + 1][x - 1] == LIVING || grid[y + 1][x - 1] == DYING)
    {
        ++counter;
    }
    if (grid[y][x - 1] == LIVING || grid[y][x - 1] == DYING)
    {
        ++counter;
    }
    if (grid[y - 1][x - 1] == LIVING || grid[y - 1][x - 1] == DYING)
    {
        ++counter;
    }

    return counter;
}


/**
 * Draw each new state. 
 */
static void drawStage(char grid[X][Y])
{
    int posX = 0, posY = 0;
    const int width = CELL_SIZE, heigth = CELL_SIZE;

    // Draw squares, with color dependant on the games current state(DEAD/LIVING).
    for (int i = 0; i < X; ++i)
    {
        for (int j = 0; j < Y; ++j)
        {
            if (grid[i][j] == LIVING)
            {
                DrawRectangle(posY, posX, width - 1, heigth - 1, GREEN);
            }
            else
            {
                DrawRectangleLines(posY, posX, width, heigth, BACKGROUND_COLOR);
            }

            posX += CELL_SIZE;
        }

        posY += CELL_SIZE;
        posX = 0;
    }
}

/**
 * Display instruction message. 
 */
static void displayMessage(bool startUpMode)
{

    const char *info_message = "IN START UP MODE: \n"
                               "A LEFT CLICK will create a new cell. \n"
                               "A RIGHT CLICK will remove a cell. \n"
                               "Press ENTER/SPACE to start the simulation. \n\n"
                               "IN RUNNING MODE: \n"
                               "Press ENTER/SPACE to reset/stop the simulation. \n\n"
                               "IN ANY MODE: \n"
                               "Press ESC to exit. \n";

    const char *regular_message = "Help! press and hold F5";

    // Shows / hides help message.
    if (IsKeyDown(KEY_F5))
    {
        DrawText(info_message, 10, 10, 20, GREEN);

        if (startUpMode == true)
        {
            DrawText("Current mode: START UP MODE", 10, 330, 20, GREEN);
        }
        else
        {
            DrawText("Current mode: RUNNING MODE", 10, 330, 20, GREEN);
        }
    }
    else
    {
        DrawText(regular_message, 10, 10, 20, GREEN);
    }

    return;
}

/**
 * Allows for painting the board to start the simulation. 
 */
static bool startSimulation(char grid[X][Y])
{
    // Check if left mouse button is down (being clicked), LEFT to create and RIGHT to remove.
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 mousePos = GetMousePosition();
        for (int i = 0; i < X * CELL_SIZE; i += CELL_SIZE)
        {
            if (i > mousePos.x - CELL_SIZE)
            {
                for (int j = 0; j < Y * CELL_SIZE; j += CELL_SIZE)
                {
                    if (j > mousePos.y - CELL_SIZE)
                    {
                        if (grid[i / CELL_SIZE][j / CELL_SIZE] == DEAD)
                        {
                            grid[i / CELL_SIZE][j / CELL_SIZE] = LIVING;
                        }

                        goto done;
                    }
                }
            }
        }
    }
    else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        // Get mouse x and y pos and check values against i and j.
        Vector2 mousePos = GetMousePosition();
        for (int i = 0; i < X * CELL_SIZE; i += CELL_SIZE)
        {
            if (i > mousePos.x - CELL_SIZE)
            {
                for (int j = 0; j < Y * CELL_SIZE; j += CELL_SIZE)
                {
                    if (j > mousePos.y - CELL_SIZE)
                    {
                        if (grid[i / CELL_SIZE][j / CELL_SIZE] == LIVING)
                        {
                            grid[i / CELL_SIZE][j / CELL_SIZE] = DEAD;
                        }

                        goto done;
                    }
                }
            }
        }
    }

done:

    drawStage(grid);

    return IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) ? false : true; 
}

/**
 * End the simulation and reset the board. 
 */
bool endSimulation(char grid[X][Y])
{
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
    {
        for (int i = 0; i < X; ++i)
        {
            for (int j = 0; j < Y; ++j)
            {
                grid[i][j] = DEAD;
            }
        }

        return true;
    }
    else
    {
        return false;
    }
}
