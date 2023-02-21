/*
    Writen by: Oscar Bergström
    https://github.com/OSCARJFB
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <raylib.h>
#include "game_of_life_prototypes.h"
#include "game_of_life_macros.h"

int main(void)
{
    windowSetup();
    runGame();

    return EXIT_SUCCESS;
}

void windowSetup(void)
{
    const int width = GetScreenWidth(), heigth = GetScreenHeight();
    const char *title = "Game of Life";

    InitWindow(width, heigth, title);
    ToggleFullscreen();
    SetTargetFPS(60);
}

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
        startUpMode = startUpMode == true ? startSimulation(grid) : endSimulation(grid);

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

void nextStage(char grid[X][Y])
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

void updateToNextStage(char grid[X][Y])
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

bool underPopulation(char grid[X][Y], int y, int x)
{
    // If a cell has less than two neighbours, the cell must die.
    int counted_cells = countCells(grid, y, x);
    return counted_cells < 2 ? true : false;
}

bool overPopulation(char grid[X][Y], int y, int x)
{
    // Any live cell connected to more than three other live cells it will die of overpopulation.
    int counted_cells = countCells(grid, y, x);
    return counted_cells > 3 ? true : false;
}

bool populate(char grid[X][Y], int y, int x)
{
    // If a dead cell has three live neighbors it becomes populated.
    int counted_cells = countCells(grid, y, x);
    return counted_cells == 3 ? true : false;
}

int countCells(char grid[X][Y], int y, int x)
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

void drawStage(char grid[X][Y])
{
    int posX = 0, posY = 0;
    const int width = CELL_SIZE, heigth = CELL_SIZE;

    // Draw squares, with color depending on the  game state(DEAD/LIVING).
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
                DrawRectangleLines(posY, posX, width, heigth, (Color){30, 40, 55, 66});
            }

            posX += CELL_SIZE;
        }

        posY += CELL_SIZE;
        posX = 0;
    }
}

void displayMessage(bool startUpMode)
{

    const char *info_message = "IN START UP MODE: \n"
                               "A LEFT CLICK wILL set cell state to LIVING. \n"
                               "A RIGHT CLICK will set cell state to DEAD. \n"
                               "press ENTER to start the simulation. \n\n"
                               "IN RUNNING MODE: \n"
                               "press ENTER to reset and stop the simulation. \n\n"
                               "IN ANY MODE: \n"
                               "press ESC to exit. \n";

    const char regular_message[] = "For help, press and hold the SPACE key!";

    // Shows / hides help message.
    if (IsKeyDown(KEY_SPACE))
    {

        DrawText(info_message, 10, 10, 20, GREEN);

        if (startUpMode == true)
        {
            DrawText("Currently: START UP MODE", 10, 330, 20, GREEN);
        }
        else
        {
            DrawText("Currently: RUNNING MODE", 10, 330, 20, GREEN);
        }
    }
    else
    {
        DrawText(regular_message, 10, 10, 20, GREEN);
    }

    return;
}

bool startSimulation(char grid[X][Y])
{
    // Check if left mouse button is down (being clicked) LEFT to create and RIGHT to remove.
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

    return IsKeyPressed(KEY_ENTER) == true ? false : true; 
}

bool endSimulation(char grid[X][Y])
{
    if (IsKeyPressed(KEY_ENTER))
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
