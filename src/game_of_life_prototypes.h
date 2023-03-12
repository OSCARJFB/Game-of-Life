/*
    Writen by: Oscar Bergström
    https://github.com/OSCARJFB
*/

#ifndef GAME_OF_LIFE_PROTOTYPES_H
#define GAME_OF_LIFE_PROTOTYPES_H
#include "game_of_life_macros.h"

// Setup the screen before initiating the game.
void windowSetup(void);

// Run the game, here we execute the game loop.
void runGame(void);

// Tracks a cells neighbour count, if a cell has less than two neighbours it must die of under population.
bool underPopulation(char[X][Y], int, int);

// Tracks a cells neighbour count, if a cell is connected to more than three neighbours it must die of over population.
bool overPopulation(char[X][Y], int, int);

// Track a cells neighbour count, if a cell has has three live neighbours it will become populated.
bool populate(char[X][Y], int, int);

// Counts cells around a cell.
int countCells(char[X][Y], int, int);

// Allows the user to paint the game board with cells.
bool startSimulation(char[X][Y]);

// Allows the user to end and start a new simulation.
bool endSimulation(char[X][Y]);

// Display text information to the user.
void displayMessage(bool);

// Set the actual values of the next stage.
void nextStage(char[X][Y]);

// Draw the next stage of the simulation.
void drawStage(char[X][Y]);

// Update grid for the comming stage.
void updateToNextStage(char[X][Y]);

#endif // GAME_OF_LIFE_PROTOTYPES_H