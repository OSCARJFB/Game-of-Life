/*
    Writen by: Oscar Bergström
    https://github.com/OSCARJFB
*/

#ifndef GAME_OF_LIFE_MACROS_H
#define GAME_OF_LIFE_MACROS_H

/// @brief Marks a cells state as being born in the next stage. 
#define BORN 'o'

/// @brief Mark a cells state as being alive. 
#define LIVING 'O'

/// @brief Marks a cells state as being dead in the next stage. 
#define DYING 'x'

/// @brief Mark a cells state as dead. 
#define DEAD ' '

/// @brief Represents the actual grid size of a cell. 
#define CELL_SIZE 20

/// @brief Grid size x-axis.
#define X 90

/// @brief Grid size y-axis. 
#define Y 90

#endif // GA_OF_LIFE_MACROS_H