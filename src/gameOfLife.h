/*
	Writen by: Oscar Bergström
	https://github.com/OSCARJFB

	MIT License
	Copyright (c) 2023 Oscar Bergström
*/

#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

void windowSetup(void);
void runGame(void);

enum cellStates
{
    // Marks a cells state as being born in the next stage.
    BORN = 'o',
    
    // Mark a cells state as being alive.
    LIVING = 'O',

    // Marks a cells state as being dead in the next stage.
    DYING = 'x',
    
    // Mark a cells state as dead.
    DEAD = ' ',
};

// Represents the actual grid size of a cell. 
#define CELL_SIZE 20

// Grid size x-axis.
#define X 90

// Grid size y-axis. 
#define Y 90

// Background color used for square lines.
#define BACKGROUND_COLOR (Color){30, 40, 55, 66}


#endif 
