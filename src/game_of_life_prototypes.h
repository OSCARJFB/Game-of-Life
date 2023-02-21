/*
    Writen by: Oscar Bergström
    https://github.com/OSCARJFB
*/

#ifndef GAME_OF_LIFE_PROTOTYPES_H
#define GAME_OF_LIFE_PROTOTYPES_H
#include "game_of_life_macros.h"

/// @brief Setup the screen before initiating the game.
void windowSetup(void);

/// @brief Run the game, here we execute the game loop.
void runGame(void);

/// @brief Track cell neighbour count, if a cell has less than two neighbours it must die of under population.
/// @param char[][]
/// @param int
/// @param int
/// @return A bool to determine if the condition was true or not.
bool underPopulation(char[X][Y], int, int);

/// @brief Track cell neighbour count, if a cell is connected to more than three neighbours it must die of over population.
/// @param char[][]
/// @param int
/// @param int
/// @return A bool to determine if the condition was true or not.
bool overPopulation(char[X][Y], int, int);

/// @brief Track cell neighbour count, if a cell has has three live neighbours it will become populated.
/// @param char[][]
/// @param int
/// @param int
/// @return A bool to determine if the condition was true or not.
bool populate(char[X][Y], int, int);

/// @brief Counts cells around a cell.
/// @param char[][]
/// @param int
/// @param int
/// @return A int representing the cell count around a specific cell.
int countCells(char[X][Y], int, int);

/// @brief Allows the user to paint the game board with cells.
/// @param char[][]
/// @return A bool to determine if the paint mode is over.
bool startSimulation(char[X][Y]);

/// @brief Allows the user to end and start a new simulation.
/// @param char[][]
/// @return A bool to determine if simulation mode should end.
bool endSimulation(char[X][Y]);

/// @brief Display text information to the user.
/// @param bool
void displayMessage(bool);

/// @brief Set the actual values of the next stage.
/// @param char[][]
void nextStage(char[X][Y]);

/// @brief Draw the next stage of the simulation.
/// @param char[][]
void drawStage(char[X][Y]);

/// @brief Update grid for the comming stage.
/// @param char[][]
void updateToNextStage(char[X][Y]);

#endif // GAME_OF_LIFE_PROTOTYPES_H