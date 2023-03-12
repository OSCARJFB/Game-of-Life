/*
    Writen by: Oscar Bergström
    https://github.com/OSCARJFB
*/

#ifndef GAME_OF_LIFE_ENUMS_H
#define GAME_OF_LIFE_ENUMS_H

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

#endif // GAME_OF_LIFE_ENUMS_H